//
// IaManager.hpp for IndieStudio in /home/dourches/Epitech
//
// Made by Martin Dourches
// Login   <martin.dourches@epitech.eu>
//
// Started on  mar. juin 13 15:49:00 2017 Martin Dourches
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//


#ifndef                IaManager_HPP
# define                IaManager_HPP

#include <Map.hpp>
#include "EntitiesManager.hpp"
#include "AMovableEntity.hpp"


namespace game
{
class IaManager : public AMovableEntity
{
  Ogre::Vector3 hook;

 public:
  IaManager(Ogre::Vector3 pos, Ogre::Vector3 dir,
	    EntitiesManager &entities, const std::string &mesh_name,
	    unsigned int lives = 1, unsigned int bombs = 1,
	    int score = 0, unsigned int bomb_power = 2,
	    bool shoot = 1, unsigned int speed = 1);

  virtual ~IaManager();
  void apply_input(e_action action);
  int isDanger(Ogre::Vector3, int, int , int, game::Map const &);
  void algo(game::Map const &, int style);
  void setHook(game::Map const &);
  void safeZone(game::Map const &);
  int checkBomb(game::Map const &);
  int checkViable(game::Map const &);
  void deterMove(game::Map const &);
  int setMoveX(int , game::Map const &);
  int setMoveY(int , game::Map const &);
  void KillPlayer(game::Map const &);
};
}

#endif                //IaManager_HPP
