//
// EntitiesManager.cpp.cpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Fri Jun 2 21:47:59 2017 Hugo Willaume
// Last update Sun Jun 18 22:11:54 2017 Hugo Willaume
//

#include "IaManager.hpp"
#include "EntitiesManager.hpp"
#include "PlayerManager.hpp"

game::EntitiesManager::EntitiesManager()
{

}

game::EntitiesManager::~EntitiesManager()
{
  delete mapManager;
}

void game::EntitiesManager::launch(SceneManager *sceneManager)
{
  scnMgr = sceneManager;
  mapManager = new MapManager(*sceneManager->sceneMgr);
}

void game::EntitiesManager::phys_act(Ogre::Real time)
{
  std::vector<int> vec;

  for (auto it : players)
    {
      if (!it->isDead())
	{
	  it->check_env();
	  it->turn_translate();
	}
    }
  bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [=](BombManager *it)
		      {return (it->update(time));}), bombs.end());
}

void game::EntitiesManager::animate(Ogre::Real time)
{
  for (auto it : players)
    it->animate(time);
  for (auto it : bombs)
    it->animate(time);
}

void game::EntitiesManager::spawn_player(unsigned int x, unsigned int y, const std::string &meshName)
{
  players.push_back(new game::PlayerManager(mapManager->map_pos_to_vector(x, y),
					    Ogre::Vector3::ZERO, *this, meshName));
}

void game::EntitiesManager::spawn_AI(unsigned int x, unsigned int y, const std::string &meshName)
{
  players.push_back(new game::IaManager(mapManager->map_pos_to_vector(x, y),
					Ogre::Vector3::ZERO, *this, meshName));
}

void game::EntitiesManager::unload()
{
  for (int i = 0; i < bombs.size(); i++)
    delete (bombs[i]);
  bombs.clear();
  for (int i = 0; i < players.size(); i++)
    delete (players[i]);
  players.clear();
}

bool game::EntitiesManager::collides(IMovableEntity *player)
{
  Ogre::Vector2 newpos = mapManager->vector_to_map_pos(player->getVirPos());
  Ogre::Vector3 normalized = mapManager->map_pos_to_vector(newpos.x, newpos.y);
  game::Tile type;

  if (player->getOrientation() == Ogre::Vector3::UNIT_X && player->getPos().x >= normalized.x + 25)
    type = mapManager->get_map().get()->getTile(newpos.x + 1, newpos.y)->getType();
  else if (player->getOrientation() == Ogre::Vector3::NEGATIVE_UNIT_X && player->getPos().x <= normalized.x - 25)
    type = mapManager->get_map().get()->getTile(newpos.x - 1, newpos.y)->getType();
  else if (player->getOrientation() == Ogre::Vector3::UNIT_Z && player->getPos().z >= normalized.z + 25)
      type = mapManager->get_map().get()->getTile(newpos.x, newpos.y + 1)->getType();
  else if (player->getOrientation() == Ogre::Vector3::NEGATIVE_UNIT_Z && player->getPos().z <= normalized.z - 25)
    type = mapManager->get_map().get()->getTile(newpos.x, newpos.y - 1)->getType();
  else
    return false;
  return (type == Indestructible || type == Destructible || type == Bomb);
}