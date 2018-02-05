//
// TileBonusFlamme.hpp for i in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Thu May  4 17:48:15 2017 dourches
// Last update Thu May  4 18:16:32 2017 dourches
//

#ifndef		TILEBONUSFLAME_HPP_
# define	TILEBONUSFLAME_HPP_

# include 	"ATile.hpp"

namespace game
{
  class TileBonusFlame : public ATile
  {
    public:
    TileBonusFlame(std::string texture = "");
    ~TileBonusFlame();

    std::string const &getTexture() const override;
    void setTexture(std::string const &) override;
    game::Tile getType() const override;
  };
}

#endif		//TILEBONUSFLAME_HPP_
