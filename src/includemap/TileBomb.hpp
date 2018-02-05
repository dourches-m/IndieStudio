//
// TileBomb.hpp for Tile in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Wed May  3 16:43:30 2017 dourches
// Last update Thu May  4 18:16:00 2017 dourches
//

#ifndef		TILEBOMB_HPP_
# define	TILEBOMB_HPP_

#include <BombManager.hpp>
# include 	"ATile.hpp"

namespace game
{
class TileBomb : public ATile
{
  game::BombManager *bomb;

 public:
  TileBomb(std::string const &texture = "");
  TileBomb(game::BombManager *, std::string const &texture = "");
  ~TileBomb();
  
  std::string const &getTexture() const override;
  void setTexture(std::string const &) override;
  game::Tile getType() const override;
  game::BombManager *getBomb() const;
};
}

#endif		//TILE_BOMB_HPP_
