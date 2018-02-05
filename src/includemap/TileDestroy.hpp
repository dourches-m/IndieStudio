//
// TitleDestroy.hpp for tile in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Wed May  3 15:38:05 2017 dourches
// Last update Thu May  4 18:16:42 2017 dourches
//

#ifndef		TILEDESTROY_HPP_
# define	TILEDESTROY_HPP_

# include	"ITile.hpp"
# include        "ATile.hpp"

namespace game
{
class TileDestroy : public ATile
{
 public:
  TileDestroy(std::string texture = "");
  ~TileDestroy();
  
  std::string const &getTexture() const override;
  void setTexture(std::string const &) override;
  game::Tile getType() const override;
};
}

#endif		//TILEDESTROY_HPP_
