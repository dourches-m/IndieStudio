//
// PlayerManager.hpp for indie in /home/hurlu/rendu/
//
// Made by Hu_move Willaume
// Login   <hu_move.willaume@epitech.eu>
//
// Started on  Thu Jun 1 16:15:43 2017 Hu_move Willaume
// Last update Sun Jun 18 21:37:15 2017 Hugo Willaume
//

#ifndef                INDIE_PlayerManager_HPP
# define                INDIE_PlayerManager_HPP

#include "AMovableEntity.hpp"

namespace game
{
  class PlayerManager : public AMovableEntity
  {
  public:

    PlayerManager(Ogre::Vector3 pos, Ogre::Vector3 dir,
		  EntitiesManager &entities, const std::string &mesh_name,
		  unsigned int lives = 1,
		  unsigned int bombs = 1, int score = 0,
		  unsigned int bomb_power = 2, bool shoot = 1, unsigned int speed = 1);

    virtual ~PlayerManager();

    void apply_input_kbd(e_action action);
    void move_kbd();

    void apply_input_stick(e_action action);

  private:
    bool _move_up;
    bool _move_down;
    bool _move_left;
    bool _move_right;
    bool _posing_bomb;
  };
}

#endif                //INDIE_PlayerManager_HPP

