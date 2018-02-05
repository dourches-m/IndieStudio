//
// TileDestroy.cpp for Indie Studio in /home/kiyonari/Epitech/Indie Studio
//
// Made by  Rémi SEZILLE
// Login    <remi.sezille@epitech.eu>
//
// Started on  mar. mai 09 11:22:34 2017 by Rémi SEZILLE
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include	"TileDestroy.hpp"

game::TileDestroy::TileDestroy(std::string texture) : ATile(texture, game::Tile::Destructible)
{
}

game::TileDestroy::~TileDestroy()
{
}

std::string const	&game::TileDestroy::getTexture() const
{
  return (_tex);
}

void            game::TileDestroy::setTexture(std::string const &t)
{
  _tex = t;
}

game::Tile		game::TileDestroy::getType() const
{
  return (tile);
}