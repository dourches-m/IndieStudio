//
// BombManager.cpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Thu Jun 1 16:26:54 2017 Hugo Willaume
// Last update Sun Jun 18 22:11:54 2017 Hugo Willaume
//

#include <thread>
#include "BombManager.hpp"

game::BombManager::BombManager(AMovableEntity &player,
			       SceneManager &sceneManager,
			       unsigned int alive_time,
			       unsigned int explode_time)
	: _player(player),
	  _pos(player.getPos()),
	  _alive_time(alive_time),
	  _explode_time(explode_time)
{
  Ogre::Vector2 pos;

  pos = _player.getEntities().mapManager->vector_to_map_pos(player.getPos());

  _bomb_node = sceneManager.sceneMgr->getRootSceneNode()->createChildSceneNode();
  _bomb_node->setPosition
	  (_player.getEntities()
		   .mapManager->map_pos_to_vector(pos.x, pos.y));
  _bomb_node->setScale(Ogre::Vector3(70, 70, 70));
  _bomb_entity = sceneManager.sceneMgr->createEntity("bomb.mesh");
  _bomb_node->attachObject(_bomb_entity);
 }

game::BombManager::~BombManager()
{
  std::cerr << "CLEAR BOMB" << std::endl;
  _bomb_node->detachObject(_bomb_entity);
  _player.getEntities().scnMgr->sceneMgr->destroyEntity(_bomb_entity);
  _player.getEntities().scnMgr->sceneMgr->destroySceneNode(_bomb_node);
}

int		game::BombManager::setBonus(int x, int y)
{
  int	bonus;

  if ((std::rand() % 100) < 40)
    {
      bonus = std::rand() % 3;
      switch (bonus)
	{
	  case 0:
	    _player.getEntities().mapManager->modTile(BonusFlamme, x, y);
	  break;
	  case 1:
	    _player.getEntities().mapManager->modTile(BonusBomb, x, y);
	  break;
	  case 2:
	    _player.getEntities().mapManager->modTile(BonusBasket, x, y);
	  break;
	  default:
	    break;
	}
      return (0);
    }
  return (1);
}

bool		game::BombManager::changeXtileBase(game::Map *map, int i)
{
  Ogre::Vector2 pos;

  pos = _player.getEntities().mapManager->vector_to_map_pos(_pos);
  if (map->getTile(pos.x + i, pos.y)->getType() != game::Explosion)
    return false;
  else
    _player.getEntities().mapManager->modTile(game::Base, pos.x + i, pos.y);
  return (true);
}

bool		game::BombManager::changeXtileExplosion(game::Map *map, int i)
{
  Ogre::Vector2 pos;

  pos = _player.getEntities().mapManager->vector_to_map_pos(_pos);
  if (map->getTile(pos.x + i, pos.y)->getType() == game::Indestructible)
    return false;
  else if (map->getTile(pos.x + i, pos.y)->getType() == game::Destructible)
    {
      if (setBonus(pos.x + i, pos.y) == 1)
	_player.getEntities().mapManager->modTile(game::Explosion, pos.x + i, pos.y);
      return false;
    }
  else
    _player.getEntities().mapManager->modTile(game::Explosion, pos.x + i, pos.y);
  return (true);
}

bool		game::BombManager::changeYtileBase(game::Map *map, int i)
{
  Ogre::Vector2 pos;

  pos = _player.getEntities().mapManager->vector_to_map_pos(_pos);
  if (map->getTile(pos.x, pos.y + i)->getType() != game::Explosion)
    return false;
  else
    _player.getEntities().mapManager->modTile(game::Base, pos.x, pos.y + i);
  return (true);
}

bool		game::BombManager::changeYtileExplosion(game::Map *map, int i)
{
  Ogre::Vector2 pos;

  pos = _player.getEntities().mapManager->vector_to_map_pos(_pos);
  if (map->getTile(pos.x, pos.y + i)->getType() == game::Indestructible)
    return false;
  else if (map->getTile(pos.x, pos.y + i)->getType() == game::Destructible)
    {
      if (setBonus(pos.x, pos.y + i) == 1)
	_player.getEntities().mapManager->modTile(game::Explosion, pos.x, pos.y + i);
      return false;
    }
  else
    _player.getEntities().mapManager->modTile(game::Explosion, pos.x, pos.y + i);
  return true;
}

void		game::BombManager::changeTileExplosion(game::Map *map)
{
  for (int i = 1; i != _player.getPower(); i++)
    if (changeXtileExplosion(map, i) == false)
      break;
  for (int i = 1; i != _player.getPower(); i++)
    if (changeXtileExplosion(map, -i) == false)
      break;
  for (int i = 1; i != _player.getPower(); i++)
    if (changeYtileExplosion(map, i) == false)
      break;
  for (int i = 0; i != _player.getPower(); i++)
    if (changeYtileExplosion(map, -i) == false)
      break;
}

void		game::BombManager::changeTileBase(game::Map *map)
{
  for (int i = 1; i != _player.getPower(); i++)
    if (changeXtileBase(map, i) == false)
      break;
  for (int i = 1; i != _player.getPower(); i++)
    if (changeXtileBase(map, -i) == false)
      break;
  for (int i = 1; i != _player.getPower(); i++)
    if (changeYtileBase(map, i) == false)
      break;
  for (int i = 0; i != _player.getPower(); i++)
    if (changeYtileBase(map, -i) == false)
      break;
}

void		game::BombManager::checkExplode(game::Map *map)
{
  Ogre::Vector2 pos;

  pos = _player.getEntities().mapManager->vector_to_map_pos(_pos);
  if (map->getTile(pos.x, pos.y)->getType() == game::Explosion)
    _alive_time = -1;
}

void		game::BombManager::checkPlayers()
{
  Ogre::Vector2 pos;
  for (auto it : _player.getEntities().players)
  {
    pos = _player.getEntities().mapManager->vector_to_map_pos(it->getPos());
    if (_player.getEntities().mapManager->get_map().get()->getTile(pos.x, pos.y)->getType() == game::Explosion)
      it->lostLife(1);
  }
}

bool		game::BombManager::update(Ogre::Real time)
{
  if (_alive_time <= 0 && _explode_time == 1)
    {
      _bomb_node->detachObject(_bomb_entity);
      changeTileExplosion(_player.getEntities().mapManager->get_map().get());
    }
  if (_alive_time <= 0)
    {
      _explode_time -= time;
      checkPlayers();
    }
  else
    {
      _alive_time -= time;
      checkExplode(_player.getEntities().mapManager->get_map().get());
    }
  if (_alive_time <= 0 && _explode_time <= 0)
    {
      changeTileBase(_player.getEntities().mapManager->get_map().get());
      _player._nbBombs--;
      return (true);
    }
  return (false);
}

Ogre::Vector3 game::BombManager::getPos() const
{
  return (_pos);
}

void game::BombManager::animate(Ogre::Real time)
{
  if (_alive_time == (0))
    _anim->addTime(time);
}

game::AMovableEntity const &game::BombManager::getPlayer() const
{
  return (_player);
}