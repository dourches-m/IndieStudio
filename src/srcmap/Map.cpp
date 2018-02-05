//
// Map.cpp for Bomberman in /home/kiyonari/Epitech/Tek2/Cpp/IndieStudio/cpp_indie_studio/src
// 
// Made by  Rémi Sezille
// Login    <sezill_r@epitech.net>
// 
// Started on  Wed May  3 15:49:21 2017 Rémi Sezille
// Last update Fri Jun  2 18:18:45 2017 dourches
//

#include <vector>
#include <iostream>
#include "TileBase.hpp"
#include "TileBomb.hpp"
#include "TileInde.hpp"
#include "TileDestroy.hpp"
#include "TileBonusBomb.hpp"
#include "TileBonusBasket.hpp"
#include "TileBonusFlame.hpp"
#include "TileExplosion.hpp"
#include "Map.hpp"

game::Map::Map(unsigned int xMax, unsigned int yMax) :	_xMax(xMax),
							      _yMax(yMax)
{
}

game::Map::~Map()
{
}

std::vector<game::ITile *> const &game::Map::getMap() const
{
  return (_map);
}

void	game::Map::addTile(game::ITile *tile)
{
  _map.push_back(tile);
}

void	game::Map::modTile(game::Tile tile, int x, int y)
{
  int i;
  game::ITile *c;

  i = 0;
  switch (tile)
    {
      case Base:
	c = new game::TileBase("cubebase.mesh");
      break;
      case Bomb:
	c = new game::TileBomb("cubebase.mesh");
      break;
      case Indestructible:
	c = new game::TileInde("cubeinde.mesh");
      break;
      case Destructible:
	c = new game::TileDestroy("cubedestroy.mesh");
      break;
      case BonusBomb:
	c = new game::TileBonusBomb("cubebonusbomb.mesh");
      break;
      case BonusBasket:
	c = new game::TileBonusBasket("cubebonusspeed.mesh");
      break;
      case BonusFlamme:
	c = new game::TileBonusFlame("cubebonusflame.mesh");
      break;
      case Explosion:
	c = new game::TileExplosion("cubeexplosion.mesh");
	break;
    default:
      c = new game::TileBase("cubebase.mesh");
      break;
    }
  if (x > _xMax || y > _yMax)
    std::cerr << "you cannot insert element at " << x << ", " << y << ". Map size is " << _xMax << ", " << _yMax << "." << std::endl;
  for (auto it = _map.begin(); it != _map.end();)
    {
      if (i == x + (y * _xMax))
	{
	 it = _map.erase(it);
	  _map.insert(it, c);
	  it = _map.end();
	}
      else
	++it;
      i++;
    }
}

game::ITile const *game::Map::getTile(int x, int y) const
{
  if (x > _xMax || y > _yMax)
    std::cerr << "you cannot insert element at " << x << ", " << y << ". Map size is " << _xMax << ", " << _yMax << "." << std::endl;
  return (_map[x + (y * _xMax)]);
}

int	game::Map::getXMax() const
{
  return (_xMax);
}

int	game::Map::getYMax() const
{
  return (_yMax);
}
