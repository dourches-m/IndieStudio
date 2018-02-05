//
// AMovableEntity.hpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed Jun 14 11:04:11 2017 Hugo Willaume
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//


#ifndef                INDIE_AMovableEntity_HPP
# define                INDIE_AMovableEntity_HPP

#include <OGRE/Ogre.h>
#include <Map.hpp>
#include "IMovableEntity.hpp"
#include "EntitiesManager.hpp"
#include "SceneManager.hpp"
#include "BombManager.hpp"

namespace game
{
  class EntitiesManager;
  class BombManager;

  class AMovableEntity : public IMovableEntity
  {
    public:

    enum e_action
    {
      UNDEF = -1,
      IA_ALGO = 0,
      MOVE_UP = 1,
      MOVE_LEFT,
      MOVE_RIGHT,
      MOVE_DOWN,
      NO_MOVE,
      PLACE_BOMB
    };

  public:

    explicit AMovableEntity(Ogre::Vector3 pos, Ogre::Vector3 dir,
			    EntitiesManager &entities, const std::string &meshName,
			    unsigned int lives = 1, unsigned int bombs = 1,
			    int score = 0, unsigned int bomb_power = 2,
			    bool shoot = false, unsigned int speed = 1);

    virtual ~AMovableEntity(){};

    Ogre::Vector3 const &getPos() const override;
    Ogre::Vector3 const &getVirPos() const override;
    Ogre::Vector3 const &getOrientation() const override;
    Ogre::Vector3 const &getVirOrientation() const override;
    EntitiesManager &getEntities() const override;
    int getPower() const override;

    void	animate(Ogre::Real time) override;
    void	instantiate(SceneManager *scene) override;
    void	pose_bomb() override;
    void	move(Ogre::Vector3 const &pos) override;
    void	lostLife(int) override;
    bool	isDead() override;

    void	turn_translate() override;
    void	check_env() override;

    unsigned int	_nbBombs;
  protected:

    void _set_anim(std::string anim, bool loop);

    Ogre::String		_anim;
    Ogre::Entity		*_entity;
    Ogre::SceneNode		*_node;
    Ogre::AnimationState	*_anim_state;

    Ogre::Vector3		_pos;
    Ogre::Vector3		_direction;
    unsigned int	_lives;
    unsigned int	_bomb_max;
    int			_score;
    unsigned int	_bomb_power;
    bool		_shoot;
    Ogre::Real		_speed;
    EntitiesManager	&_entities;
  };
}

#endif                //INDIE_AMovablexty_HPP
