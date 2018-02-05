//
// BombManager.hpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Thu Jun 1 16:23:06 2017 Hugo Willaume
// Last update Fri Jun 16 14:29:59 2017 Hugo Willaume
//

#ifndef                INDIE_BombManager_HPP
# define                INDIE_BombManager_HPP

#include <chrono>

#include "AMovableEntity.hpp"

namespace game
{
  class AMovableEntity;

  class BombManager
  {
    public:
    BombManager(AMovableEntity &player, SceneManager &sceneManager,
		unsigned int alive_time, unsigned int explode_time);
    ~BombManager();


    void animate(Ogre::Real time);
    AMovableEntity const &getPlayer() const;
    Ogre::Vector3 getPos() const;
    void changeTileExplosion(game::Map *);
    void changeTileBase(game::Map *);
    bool changeXtileBase(game::Map *, int);
    bool changeXtileExplosion(game::Map * , int);
    bool changeYtileExplosion(game::Map *, int);
    bool changeYtileBase(game::Map *map, int i);
    bool	update(Ogre::Real time);
    void	checkPlayers();
    int		setBonus(int, int);
    void	checkExplode(game::Map *);
    private:
    AMovableEntity	&_player;
    Ogre::Vector3	_pos;

    Ogre::SceneNode		*_bomb_node;
    Ogre::Entity		*_bomb_entity;
    Ogre::AnimationState	*_anim;

    Ogre::Real	_alive_time;
    Ogre::Real	_explode_time;
  };
}

#endif                //INDIE_BombManager_HPP
