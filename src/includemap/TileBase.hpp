//
// TileBase.hpp for Tile in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Thu May  4 17:39:03 2017 dourches
// Last update Tue May  9 10:11:30 2017 Rémi Sezille
//

#ifndef		TILEBASE_HPP_
# define	TILEBASE_HPP_

# include 	"ATile.hpp"

namespace game
{
class TileBase : public ATile
{
 public:
  TileBase(std::string const &texture = "");
  ~TileBase();
  
  std::string const &getTexture() const override;
  void setTexture(std::string const &) override;
  game::Tile getType() const override;
};
}

#endif		//TILE_BOMB_HPP_
