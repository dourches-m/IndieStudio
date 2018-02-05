//
// TileBonusBasket.hpp for Tilebonusbasket in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Thu May  4 17:46:10 2017 dourches
// Last update Thu May  4 18:16:11 2017 dourches
//

#ifndef		TILEBONUSBASKET_HPP_
# define	TILEBONUSBASKET_HPP_

# include 	"ATile.hpp"

namespace game
{
class TileBonusBasket : public ATile
{
 public:
  TileBonusBasket(std::string texture = "");
  ~TileBonusBasket();

  std::string const &getTexture() const override;
  void setTexture(std::string const&) override;
  Tile getType() const override;
};
}

#endif		//TILEBONUSBASKET_HPP_
