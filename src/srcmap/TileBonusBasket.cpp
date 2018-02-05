//
// TileBonusBasket.cpp for Indie Studio in /home/kiyonari/Epitech/Tek2/Cpp/IndieStudio/cpp_indie_studio/src/srcmap
// 
// Made by  Rémi Sezille
// Login    <sezill_r@epitech.net>
// 
// Started on  Tue May  9 10:14:03 2017 Rémi Sezille
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include	"TileBonusBasket.hpp"

game::TileBonusBasket::TileBonusBasket(std::string texture) : ATile(texture, game::Tile::BonusBasket)
{
}

game::TileBonusBasket::~TileBonusBasket()
{
}

std::string const	&game::TileBonusBasket::getTexture() const
{
  return (_tex);
}

void			game::TileBonusBasket::setTexture(std::string const &s)
{
  _tex = s;
}

game::Tile		game::TileBonusBasket::getType() const
{
  return (tile);
}
