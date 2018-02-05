//
// TileBonusFlame.cpp for Indie Studio in /home/kiyonari/Epitech/Indie Studio
//
// Made by  Rémi SEZILLE
// Login    <remi.sezille@epitech.eu>
//
// Started on  mar. mai 09 11:20:38 2017 by Rémi SEZILLE
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include        "TileBonusFlame.hpp"

game::TileBonusFlame::TileBonusFlame(std::string texture) : ATile(texture, game::Tile::BonusFlamme)
{
}

game::TileBonusFlame::~TileBonusFlame()
{
}

std::string const	&game::TileBonusFlame::getTexture() const
{
  return (_tex);
}

void  game::TileBonusFlame::setTexture(std::string const &t)
{
  _tex = t;
}

game::Tile		game::TileBonusFlame::getType() const
{
  return (tile);
}