//
// TileInde.hpp for TileIndes in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src/includemap
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Thu May  4 17:51:27 2017 dourches
// Last update Thu May  4 18:16:57 2017 dourches
//

#ifndef		TILEINDE_HPP_
# define	TILEINDE_HPP_

# include 	"ATile.hpp"

namespace game
{
class TileInde : public ATile
{
 public:
  TileInde(std::string texture);
  ~TileInde();

  std::string const &getTexture() const override;
  void setTexture(std::string const &) override;
  game::Tile getType() const override;
};
}

#endif		//TILEINDE_HPP_
