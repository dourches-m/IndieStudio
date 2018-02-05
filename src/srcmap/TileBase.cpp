//
// TileBase.cpp for Indie Studio in /home/kiyonari/Epitech/Tek2/Cpp/IndieStudio/cpp_indie_studio/src/srcmap
// 
// Made by  Rémi Sezille
// Login    <sezill_r@epitech.net>
// 
// Started on  Tue May  9 09:58:56 2017 Rémi Sezille
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include	"TileBase.hpp"

game::TileBase::TileBase(std::string const &texture) : ATile(texture, game::Tile::Base)
{
}

game::TileBase::~TileBase()
{
}

std::string const	&game::TileBase::getTexture() const
{
  return (_tex);
}

void game::TileBase::setTexture(std::string const &t)
{
  _tex = t;
}

game::Tile		game::TileBase::getType() const
{
  return (tile);
}
