//
// TileExplosion.cpp for Indie Studio in /home/kiyonari/Epitech/Indie Studio
//
// Made by  Rémi SEZILLE
// Login    <remi.sezille@epitech.eu>
//
// Started on  mar. mai 09 11:23:23 2017 by Rémi SEZILLE
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include	"TileExplosion.hpp"

game::TileExplosion::TileExplosion(std::string texture) :ATile(texture, game::Tile::Explosion)
{
}

game::TileExplosion::~TileExplosion()
{
}

std::string const		&game::TileExplosion::getTexture() const
{
  return (_tex);
}

void            game::TileExplosion::setTexture(std::string const &t)
{
 _tex = t;
}

game::Tile		game::TileExplosion::getType() const
{
  return (tile);
}
