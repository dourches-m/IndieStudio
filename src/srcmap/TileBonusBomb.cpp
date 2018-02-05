//
// TileBonusBomb.cpp for Indie Studio in /home/kiyonari/Epitech/Indie Studio
//
// Made by  Rémi SEZILLE
// Login    <remi.sezille@epitech.eu>
//
// Started on  mar. mai 09 11:19:43 2017 by Rémi SEZILLE
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include	"TileBonusBomb.hpp"

game::TileBonusBomb::TileBonusBomb(std::string texture) : ATile(texture, game::Tile::BonusBomb)
{
}

game::TileBonusBomb::~TileBonusBomb()
{
}

std::string const		&game::TileBonusBomb::getTexture()
const
{
  return (_tex);
}

void            game::TileBonusBomb::setTexture(std::string const &t)
{
  _tex = t;
}

game::Tile		game::TileBonusBomb::getType() const
{
  return (tile);
}