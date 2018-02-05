//
// PlayerManager.cpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Thu Jun 1 16:26:20 2017 Hugo Willaume
// Last update Sun Jun 18 22:11:55 2017 Hugo Willaume
//

#include "PlayerManager.hpp"

game::PlayerManager::PlayerManager(Ogre::Vector3 pos, Ogre::Vector3 dir,
				   EntitiesManager &entities, const std::string &mesh_name,
				   unsigned int lives,
				   unsigned int bombs, int score,
				   unsigned int bomb_power, bool shoot, unsigned int speed)
	: AMovableEntity(pos, dir, entities, mesh_name, lives, bombs, score, bomb_power, shoot, speed),
	  _move_up(false), _move_down(false), _move_left(false), _move_right(false), _posing_bomb(false)
{
}

game::PlayerManager::~PlayerManager()
{
  std::cerr << "PLAYER CLEAR" << std::endl,
  _node->detachObject(_entity);
  _entities.scnMgr->sceneMgr->destroyEntity(_entity);
  _entities.scnMgr->sceneMgr->destroySceneNode(_node);
}

void game::PlayerManager::move_kbd()
{
  _direction = Ogre::Vector3::ZERO;
  if (_move_up)
    _direction = Ogre::Vector3::NEGATIVE_UNIT_Z;
  else if (_move_left)
    _direction = Ogre::Vector3::NEGATIVE_UNIT_X;
  else if (_move_right)
    _direction = Ogre::Vector3::UNIT_X;
  else if (_move_down)
    _direction = Ogre::Vector3::UNIT_Z;
  _pos += _direction;
}

void game::PlayerManager::apply_input_stick(e_action action)
{
  switch (action)
    {
      case MOVE_UP:
	move(Ogre::Vector3::NEGATIVE_UNIT_Z);
	break;
      case MOVE_LEFT:
	move(Ogre::Vector3::NEGATIVE_UNIT_X);
	break;
      case MOVE_RIGHT:
	move(Ogre::Vector3::UNIT_X);
	break;
      case MOVE_DOWN:
	move(Ogre::Vector3::UNIT_Z);
	break;
      case PLACE_BOMB:
	_posing_bomb = !_posing_bomb;
      move(Ogre::Vector3::ZERO);
      break;
      default:
	move(Ogre::Vector3::ZERO);
	break;
    }
  if (_posing_bomb)
    pose_bomb();
  turn_translate();
}

void game::PlayerManager::apply_input_kbd(e_action action)
{
  switch (action)
    {
      case MOVE_UP:
	_move_up = !_move_up;
	break;
      case MOVE_LEFT:
	_move_left = !_move_left;
	break;
      case MOVE_RIGHT:
	_move_right = !_move_right;
	break;
      case MOVE_DOWN:
	_move_down = !_move_down;
	break;
      case PLACE_BOMB:
	_posing_bomb = !_posing_bomb;
	break;
      default:
	Ogre::LogManager::getSingleton().logMessage("Unrecognized command " +
						    std::to_string(action) +
						    "for apply_input()");
      break;
    }
  move_kbd();
  if (_posing_bomb)
    pose_bomb();
  turn_translate();
}