//
// CheckMap.cpp for IndieStudio in /home/kiyonari/rendu/IndieStudio
//
// Made by Rémi Sezille
// Login   <remi.sezille@epitech.eu>
//
// Started on  mar. 13 06 2017 02:19:57  by Rémi Sezille
// Last update mar. 13 06 2017 02:19:57  by Rémi Sezille
//

#include "Map.hpp"

bool	checkBorders(const game::Map &map)
{
  for (int y = 0; y < map.getYMax(); ++y)
    if (map.getTile(0, y)->getType() != game::Tile::Indestructible)
      return false;
  for (int y = 0; y < map.getYMax(); ++y)
    if (map.getTile(map.getXMax(), y)->getType() != game::Tile::Indestructible)
      return false;
  for (int x = 0; x < map.getXMax(); ++x)
    if (map.getTile(x, 0)->getType() != game::Tile::Indestructible)
      return false;
  for (int x = 0; x < map.getXMax(); ++x)
    if (map.getTile(x, map.getYMax())->getType() != game::Tile::Indestructible)
      return false;
  return true;
}

bool	checkCorners(const game::Map &map)
{
  int	xMax;
  int 	yMax;

  xMax = map.getXMax();
  yMax = map.getYMax();
  if (map.getTile(1, 1)->getType() != game::Tile::Indestructible ||
      map.getTile(1, 2)->getType() != game::Tile::Indestructible ||
      map.getTile(2, 1)->getType() != game::Tile::Indestructible)
    return false;
  else if (map.getTile(xMax - 1, 1)->getType() != game::Tile::Indestructible ||
      map.getTile(xMax - 1, 2)->getType() != game::Tile::Indestructible ||
      map.getTile(xMax - 2, 1)->getType() != game::Tile::Indestructible)
    return false;
  else if (map.getTile(1, yMax - 1)->getType() != game::Tile::Indestructible ||
      map.getTile(1, yMax - 2)->getType() != game::Tile::Indestructible ||
      map.getTile(2, yMax - 1)->getType() != game::Tile::Indestructible)
    return false;
  else if (map.getTile(xMax - 1, yMax - 1)->getType() != game::Tile::Indestructible ||
      map.getTile(xMax - 1, yMax - 2)->getType() != game::Tile::Indestructible ||
      map.getTile(xMax - 2, yMax - 1)->getType() != game::Tile::Indestructible)
    return false;
  else
    return true;
}

bool 	checkMap(const game::Map &map)
{
  if (map.getYMax() != map.getXMax())
    return false;
  if (!checkBorders(map))
    return false;
  else if (!checkCorners(map))
    return false;
  return true;
}
