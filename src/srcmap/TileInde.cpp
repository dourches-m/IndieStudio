//
// TileInde.cpp for Indie Studio in /home/kiyonari/Epitech/Indie Studio
//
// Made by  Rémi SEZILLE
// Login    <remi.sezille@epitech.eu>
//
// Started on  mar. mai 09 11:24:30 2017 by Rémi SEZILLE
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include	"TileInde.hpp"

game::TileInde::TileInde(std::string texture) : ATile(texture, game::Tile::Indestructible)
{
}

game::TileInde::~TileInde()
{
}

std::string const		&game::TileInde::getTexture() const
{
  return (_tex);
}

void            game::TileInde::setTexture(std::string const &t)
{
  _tex = t;
}
game::Tile		game::TileInde::getType() const
{
  return (tile);
}
