//
// IaManager.cpp for IndieStudio in /home/dourches/Epitech
//
// Made by Martin Dourches
// Login   <martin.dourches@epitech.eu>
//
// Started on  mar. juin 13 15:51:13 2017 Martin Dourches
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//

#include <TileBomb.hpp>
#include <PlayerManager.hpp>
#include "IaManager.hpp"

game::IaManager::IaManager(Ogre::Vector3 pos, Ogre::Vector3 dir,
			   EntitiesManager &entities, const std::string &mesh_name,
			   unsigned int lives, unsigned int bombs,
			   int score, unsigned int bomb_power,
			   bool shoot, unsigned int speed) :
	AMovableEntity(pos, dir, entities, mesh_name, lives, bombs, score, bomb_power, shoot, speed),
	hook(-1, -1, -1)
{
}

game::IaManager::~IaManager()
{
  if (_node)
    {
      if (_entity)
	delete (_entity);
      _node->detachAllObjects();
      delete(_node);
    }
}

void	game::IaManager::setHook(game::Map const &map)
{
  int x;
  int z;

  x = (std::rand() % map.getXMax()) + 1;
  z = (std::rand() % map.getYMax()) + 1;
  hook = Ogre::Vector3(x, 0, z);
}

int	game::IaManager::isDanger(Ogre::Vector3 pos, int x, int y, int
power, game::Map const &map)
{
  for (int z = 0; z != power; z++)
    {
      if (map.getTile(x + z, y)->getType() != game::Indestructible &&
	      map.getTile(x + z, y)->getType() != game::Destructible)
	if (pos == Ogre::Vector3(x + z, 0, y))
	  return (1);
    }
  for (int z = 0; z != -power; z--)
    {
      if (map.getTile(x + z, y)->getType() != game::Indestructible &&
	      map.getTile(x + z, y)->getType() != game::Destructible)
	if (pos == Ogre::Vector3(x + z, 0, y))
	  return (1);
    }
  for (int z = 0; z != power; z++)
    {
      if (map.getTile(x, y + z)->getType() != game::Destructible
	      && map.getTile(x, y + z)->getType() != game::Indestructible)
	if (pos == Ogre::Vector3(x, 0, y + z))
	  return (1);
    }
  for (int z = 0; z != -power; z--)
    {
      if (map.getTile(x + z, y)->getType() != game::Indestructible &&
	      map.getTile(x + z, y)->getType() != game::Destructible)
	if (pos == Ogre::Vector3(x, 0, y + z))
	  return (1);
    }
  return (0);
}

int	game::IaManager::checkBomb(game::Map const &map)
{
  for (std::vector<BombManager *>::iterator it
	  = _entities.bombs.begin(); it != _entities.bombs.end(); ++it)
    {
      if (isDanger((*it)->getPos(), static_cast<int>((*it)->getPos().x),
		   static_cast<int>((*it)->getPos().y), (*it)->getPlayer().getPower(), map) == 1)
	return (1);
    }
  return (0);
}

int	game::IaManager::checkViable(game::Map const &map)
{
  if (map.getTile(static_cast<int>(hook.x),
		  static_cast<int>(hook.z))->getType() != game::Indestructible
      && map.getTile(static_cast<int>(hook.x),
		     static_cast<int>(hook.z))->getType() != game::Destructible)
    return (0);
  else
    return (1);
}

void game::IaManager::safeZone(game::Map const &map)
{
  int	x;
  int	y;
  Ogre::Vector3 tmp;

  x = 0;
  y = 0;
  tmp = hook;
  while (tmp == hook || (x != map.getXMax() && y != map.getYMax()))
    {
      if (checkBomb(map) == 0)
	hook = Ogre::Vector3(x + _pos.x, _pos.y, y + _pos.z);
      else if (checkBomb(map) == 0)
	hook = Ogre::Vector3(_pos.x - x, _pos.y, y + _pos.z);
      else if (checkBomb(map) == 0)
	hook = Ogre::Vector3(x + _pos.x, _pos.y, _pos.z - y);
      else if (checkBomb(map) == 0)
	hook = Ogre::Vector3(_pos.x - x, _pos.y, _pos.z - y);
      if (x != map.getXMax())
      x++;
      else
	{
	  y++;
	  x = 0;
	}
      if (checkViable(map) == 1)
	tmp == hook;
    }
}

int	game::IaManager::setMoveX(int mv, game::Map const &map)
{
  if (map.getTile(static_cast<int>(_pos.x  + mv),
		  static_cast<int>(_pos.z))->getType() != game::Indestructible
	  && map.getTile(static_cast<int>(_pos.x  + mv),
			 static_cast<int>(_pos.z))->getType() !=
			   game::Destructible)
    {
      move(Ogre::Vector3(mv, 0, 0));
      return (0);
    }
  else if (map.getTile(static_cast<int>(_pos.x  + mv),
		       static_cast<int>(_pos.z))->getType() ==
	  game::Destructible)
    {
      pose_bomb();
      return (0);
    }
  return (1);
}

int	game::IaManager::setMoveY(int mv, game::Map const &map)
{
  if (map.getTile(static_cast<int>(_pos.x),
		  static_cast<int>(_pos.z + mv))->getType() !=
		  game::Indestructible
	  && map.getTile(static_cast<int>(_pos.x),
			 static_cast<int>(_pos.z + mv))->getType() !=
			 game::Destructible)
    {
      move(Ogre::Vector3(0, 0, mv));
      return (0);
    }
  else if (map.getTile(static_cast<int>(_pos.x),
		       static_cast<int>(_pos.z + mv))->getType() ==
		       game::Destructible)
  {
    pose_bomb();
    return (0);
  }
  return (1);
}

void	game::IaManager::deterMove(game::Map const &map)
{
  int diffx;
  int diffy;

  diffx = static_cast<int>(hook.x - _pos.x);
  diffy = static_cast<int>(hook.z - _pos.z);
  if (diffx > 0)
    {
      if (setMoveX(1, map) == 1)
	setHook(map);
    }
  else if (diffx < 0)
    {
      if (setMoveX(-1, map) == 1)
	setHook(map);
    }
  else if (diffy > 0)
    {
      if (setMoveY(1, map) == 1)
	setHook(map);
    }
  else if (diffy < 0)
    {
      if (setMoveY(-1, map) == 1)
	setHook(map);
    }
  if (diffx == 0 && diffy == 0)
    setHook(map);
}

void game::IaManager::KillPlayer(game::Map const &map)
{
  for (auto it : _entities.players)
    {
      if (isDanger(_pos, static_cast<int>(it->getPos().x),
		   static_cast<int>(it->getPos().y), _bomb_power, map) == 1)
	pose_bomb();
    }
}

void game::IaManager::algo(game::Map const &map, int style)
{
  if (hook == Ogre::Vector3(-1, -1, -1))
    setHook(map);
  if (checkBomb(map) == 1)
  safeZone(map);
  deterMove(map);
  if (style == 1)
    KillPlayer(map);
}

void game::IaManager::apply_input(e_action action)
{
  if (action == IA_ALGO)
      algo(*_entities.mapManager->get_map().get(), 1);
  else
    return ;
}