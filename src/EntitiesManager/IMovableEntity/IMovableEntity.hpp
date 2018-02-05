//
// IMovableEntity.hpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Fri Jun 16 14:20:00 2017 Hugo Willaume
// Last update Sun Jun 18 17:54:58 2017 Hugo Willaume
//


#ifndef INDIE_STUDIO_IMOVABLEENTITY_HPP
#define INDIE_STUDIO_IMOVABLEENTITY_HPP

#include "SceneManager.hpp"

namespace game
{
class EntitiesManager;

  class IMovableEntity
  {
    public:
    virtual ~IMovableEntity(){};

    virtual Ogre::Vector3 const &getPos() const = 0;
    virtual Ogre::Vector3 const &getVirPos() const = 0;
    virtual Ogre::Vector3 const &getOrientation() const = 0;
    virtual Ogre::Vector3 const &getVirOrientation() const = 0;
    virtual EntitiesManager &getEntities() const = 0 ;
    virtual int getPower() const = 0;
    virtual void lostLife(int) = 0;
    virtual bool isDead() = 0;
    virtual void check_env() = 0;

    virtual void	animate(Ogre::Real time) = 0;
    virtual void	instantiate(SceneManager *scene) = 0;
    virtual void	pose_bomb() = 0;
    virtual void	move(Ogre::Vector3 const &pos) = 0;

    virtual void	turn_translate() = 0;
  };
}
#endif //INDIE_STUDIO_IMOVABLEENTITY_HPP
