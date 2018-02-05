//
// GenerateMap.cpp for IndieStudio in /home/kiyonari/rendu/IndieStudio
//
// Made by Rémi Sezille
// Login   <remi.sezille@epitech.eu>
//
// Started on  sam. 03 06 2017 03:54:27  by Rémi Sezille
// Last update Thu Jun 15 17:52:51 2017 Hugo Willaume
//

#include	<cstdlib>
#include 	<ctime>
#include	<iostream>
#include	<fstream>
#include        <unistd.h>
#include        "MapGeneration.hpp"

int		MapGeneration::writeRandom(std::fstream &file)
{
  int n;
  n = rand() % 100;
  if (n >= 0 && n < 60)
    file << "1";
  if (n >= 60 && n < 80)
    file << "2";
  if (n >= 80 && n < 100)
    file << "0";
  return (EXIT_SUCCESS);
}

bool		checkTopLeftCorner(int x, int y)
{
  if ((x == 1 && y == 1) ||
      (x == 1 && y == 2) ||
      (x == 2 && y == 1))
    return (0);
  else
    return (1);
}

bool 		checkTopRightCorner(int x, int y, int xMax)
{
  if (((x == xMax - 2) && (y == 1)) ||
      ((x == xMax - 2) && (y == 2)) ||
      ((x == xMax - 3) && (y == 1)))
    return (0);
  else
    return (1);
}

bool		checkBottomLeftCorner(int x, int y, int yMax)
{
  if (((x == 1) && (y == yMax - 2)) ||
      ((x == 1) && (y == yMax - 3)) ||
      ((x == 2) && (y == yMax - 2)))
    return (0);
  else
    return (1);
}

bool 		checkBottomRightCorner(int x, int y, int xMax, int yMax)
{
  if (((x == xMax - 2) && (y == yMax - 2)) ||
      ((x == xMax - 2) && (y == yMax - 3)) ||
      ((x == xMax - 3) && (y == yMax - 2)))
    return (0);
  else
    return (1);
}

int		MapGeneration::writeFile(std::fstream &file, int xMax, int yMax)
{
  int           x;
  int           y;

  y = 0;
  while (y < yMax)
    {
      x = 0;
      while (x < xMax)
	{
	  if (y == 0 || x == 0 || x == xMax - 1 || y == yMax - 1)
	    file << "2";
	  else if ((checkTopLeftCorner(x, y) == 0) ||
		   (checkTopRightCorner(x, y, xMax) == 0) ||
		   (checkBottomLeftCorner(x, y, yMax) == 0) ||
		   (checkBottomRightCorner(x, y, xMax, yMax)) == 0)
	      file << "0";
	  else
	    writeRandom(file);
	  x++;
	}
      file << std::endl;
      y++;
    }
  return (EXIT_SUCCESS);
}

int		MapGeneration::createRandomMap(int xMax, int yMax, std::string const &filename)
{
  std::fstream file(filename);

  if (!file.is_open())
    return (EXIT_FAILURE);
  else
    writeFile(file, xMax, yMax);
  return (0);
}
