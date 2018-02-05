//
// TileExplosion.hpp for TileExplosion in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Thu May  4 17:42:48 2017 dourches
// Last update Thu May  4 18:16:49 2017 dourches
//

#ifndef		TILEEXPLOSION_HPP_
# define	TILEEXPLOSION_HPP_

# include 	"ATile.hpp"

namespace game
{
class TileExplosion : public ATile
{
 public:
  TileExplosion(std::string texture = "");
  ~TileExplosion();
  
  std::string const &getTexture() const override;
  void setTexture(std::string const &) override;
  game::Tile getType() const override;
};
}

#endif		// TILEEXPLOSION_HPP_
