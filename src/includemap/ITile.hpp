//
// ITile.hpp for ITile in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Wed May  3 15:14:22 2017 dourches
// Last update Sat Jun 17 15:08:20 2017 Hugo Willaume
//

#ifndef		ITILE_HPP_
# define	ITILE_HPP_

#include <string>

namespace game
{
enum Tile
{
  Base,
  Bomb,
  Indestructible,
  Destructible,
  BonusBomb,
  BonusBasket,
  BonusFlamme,
  Explosion
};

  class ITile
  {
    public:
    virtual ~ITile() {};

    virtual void setTexture(std::string const &) = 0;
    virtual std::string const &getTexture() const = 0;
    virtual game::Tile getType() const = 0;
  };
}


#endif		//ITILE_HPP_
