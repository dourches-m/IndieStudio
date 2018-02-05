//
// AMovableEntity.cpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed Jun 14 11:03:23 2017 Hugo Willaume
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//

#include "AMovableEntity.hpp"

game::AMovableEntity::AMovableEntity(Ogre::Vector3 pos, Ogre::Vector3 dir, EntitiesManager &entities,
				     const std::string &mesh_name,
				     unsigned int lives,
				     unsigned int bombs, int score,
				     unsigned int bomb_power, bool shoot,
				     unsigned int speed)
	: _nbBombs(0), _anim("Idle1"), _entity(nullptr),
	_pos(pos), _direction(dir), _lives(lives),
	_bomb_max(bombs), _score(score),
	_bomb_power(bomb_power), _shoot(shoot),
	_speed(speed) , _entities(entities)
{
  _node = entities.scnMgr->sceneMgr->getRootSceneNode()->createChildSceneNode();
  _entity = entities.scnMgr->sceneMgr->createEntity(mesh_name);
  _node->setPosition(pos);
  _node->attachObject(_entity);
  _anim_state = _entity->getAnimationState(_anim);
  _anim_state->setEnabled(true);
  _anim_state->setLoop(true);
}

void    game::AMovableEntity::lostLife(int x)
{
  if (_lives != 0)
    {
    _lives -= x;
      if (_lives == 0)
	  _set_anim("Death1", false);
    }
}

void	game::AMovableEntity::check_env()
{
  Ogre::Vector2 xy_pos = _entities.mapManager->vector_to_map_pos(_pos);
  game::Tile type = _entities.mapManager->get_map().get()->getTile(xy_pos.x, xy_pos.y)->getType();

  switch (type)
    {
      case Explosion:
	lostLife(1);
      return;
      case BonusBasket:
	_speed += 0.20;
      _speed = (_speed < 2.2)? _speed : 2;
      break;
      case BonusFlamme:
	_bomb_power += 1;
	break;
      case BonusBomb:
	_bomb_max += 1;
	break;
      default:
	return;
    }
  _entities.mapManager->modTile(Base, xy_pos.x, xy_pos.y);
}

game::EntitiesManager  &game::AMovableEntity::getEntities() const
{
  return (_entities);
}

void	game::AMovableEntity::move(Ogre::Vector3 const &pos)
{
  _direction = pos;
  _pos += pos;
}

bool	game::AMovableEntity::isDead()
{
  return _lives <= 0;
}

void game::AMovableEntity::_set_anim(std::string anim, bool loop)
{
  if (_anim == anim || (!_anim_state->getLoop() && !_anim_state->hasEnded()))
    return ;
  _anim = anim;
  _anim_state->setTimePosition(0);
  _anim_state->setEnabled(false);
  _anim_state->setLoop(false);
  _anim_state = _entity->getAnimationState(_anim);
  _anim_state->setTimePosition(0);
  _anim_state->setEnabled(true);
  _anim_state->setLoop(loop);
}

void	game::AMovableEntity::animate(Ogre::Real time)
{
  if (isDead() && _anim_state->hasEnded())
    {
      _node->setVisible(false);
      return;
    }
  if (_direction != Ogre::Vector3::ZERO)
    _set_anim("Walk", true);
  else
    _set_anim("Idle1", true);
  _anim_state->addTime(time);
}

int	game::AMovableEntity::getPower() const
{
  return (_bomb_power);
}

void	game::AMovableEntity::pose_bomb()
{
  Ogre::Vector2 tile;

  if (isDead())
    return;
  if (_nbBombs < _bomb_max)
    {
      tile = _entities.mapManager->vector_to_map_pos(_pos);
      if (_entities.mapManager->get_map().get()->getTile(static_cast<int>(tile.x),
							 static_cast<int>(tile.y))->getType() != game::Bomb)
      {
	  BombManager *manage = new BombManager(*this, *_entities.scnMgr, 2, 1);

	std::cerr << "Modtile ==" << tile << std::endl;
	  _entities.mapManager->modTile(game::Bomb,
				   static_cast<int>(tile.x),
				   static_cast<int>(tile.y));
	std::cerr << "ON ARRIVE PAS ICI" << std::endl;
	  _entities.bombs.push_back(manage);
	std::cerr << "ON L'A DESPASSE" << std::endl;
	_nbBombs++;
	}
    }
}

void	game::AMovableEntity::instantiate(SceneManager *)
{
  _node->setVisible(true);
}

void	game::AMovableEntity::turn_translate()
{
  _node->lookAt(_pos + (_direction * 100), Ogre::SceneNode::TS_WORLD);
  if (_direction == Ogre::Vector3::ZERO ||
      _entities.collides(this))
    {
      _pos = getPos();
      _direction = getOrientation();
      return ;
    }
  _node->translate(_direction * _speed);
  _pos = _node->getPosition();
}

Ogre::Vector3 const & game::AMovableEntity::getPos() const
{
  return _node->getPosition();
}

const Ogre::Vector3 & game::AMovableEntity::getOrientation() const
{
  return _direction;
}

Ogre::Vector3 const &game::AMovableEntity::getVirPos() const
{
  return _pos;
}

Ogre::Vector3 const &game::AMovableEntity::getVirOrientation() const
{
  return _direction;
}
