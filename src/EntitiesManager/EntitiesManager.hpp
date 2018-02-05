//
// EntitiesManager.hpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed May 31 16:45:48 2017 Hugo Willaume
// Last update Sun Jun 18 22:11:54 2017 Hugo Willaume
//


#ifndef                INDIE_EntitiesManager_HPP
# define                INDIE_EntitiesManager_HPP

#include <vector>
#include "SceneManager.hpp"
#include "AMovableEntity.hpp"
#include "MapManager.hpp"
#include "Map.hpp"
#include "BombManager.hpp"

namespace game
{
  class BombManager;
  class AMovableEntity;

  class EntitiesManager
  {
    public:
    EntitiesManager();
    ~EntitiesManager();

    void launch(SceneManager *sceneManager);
    void animate(Ogre::Real time);
    void phys_act(Ogre::Real time);

    void unload();
    void spawn_player(unsigned int x, unsigned int y, const std::string &mesh_name);
    void spawn_AI(unsigned int x, unsigned int y, const std::string &mesh_name);

    bool collides(IMovableEntity *);

    std::vector<IMovableEntity *> players;
    std::vector<BombManager *> bombs;

    MapManager			*mapManager;
    SceneManager		*scnMgr;
  };
}

#endif                //INDIE_EntitiesManager_HPP

