//
// TileBomb.cpp for Indie Studio in /home/kiyonari/Epitech/Tek2/Cpp/IndieStudio/cpp_indie_studio/src/srcmap
// 
// Made by  Rémi Sezille
// Login    <sezill_r@epitech.net>
// 
// Started on  Tue May  9 10:12:40 2017 Rémi Sezille
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#include	"ATile.hpp"
#include	"TileBomb.hpp"

game::TileBomb::TileBomb(game::BombManager *Bomb, std::string const
&texture) : ATile(texture, game::Tile::Bomb), bomb(Bomb)
{
}

game::TileBomb::TileBomb(std::string const &texture) : ATile(texture, game::Tile::Bomb)
{
}

game::TileBomb::~TileBomb()
{
}

std::string	const &game::TileBomb::getTexture() const
{
  return (_tex);
}

void game::TileBomb::setTexture(std::string const &tex)
{
_tex = tex;
}

game::Tile		game::TileBomb::getType() const
{
  return (tile);
}

game::BombManager *game::TileBomb::getBomb() const
{
  return (bomb);
}