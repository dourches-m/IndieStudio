//
// TileBonusBomb.hpp for TileBonus in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Wed May  3 16:46:25 2017 dourches
// Last update Thu May  4 18:16:21 2017 dourches
//

#ifndef		TILEBONUSBOMB_HPP_
# define	TILEBONUSBOMB_HPP_

# include 	"ATile.hpp"

namespace game
{
class TileBonusBomb : public ATile
{
 public:
  TileBonusBomb(std::string texture = "");
  ~TileBonusBomb();
  
  std::string const &getTexture() const override;
  void	setTexture(std::string const &) override;
  game::Tile getType() const override;
};
}

#endif		//TILEBONUSBOMB_HPP_
