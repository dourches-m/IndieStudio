//
// GenerateMap.hpp for IndieStudio in /home/kiyonari/rendu/IndieStudio
//
// Made by Rémi Sezille
// Login   <remi.sezille@epitech.eu>
//
// Started on  sam. 03 06 2017 03:42:49  by Rémi Sezille
// Last update Thu Jun 15 17:52:51 2017 Hugo Willaume
//

#ifndef 	INDIE_STUDIO_GENERATEMAP_HPP
# define 	INDIE_STUDIO_GENERATEMAP_HPP

#include <string>

class	MapGeneration
{
 public:
  int		createRandomMap(int xMax, int yMax, std::string const &file = "tmp");

 private:
  int 		writeRandom(std::fstream &file);
  int 		writeFile(std::fstream &file, int x, int y);

};

#endif 		//INDIE_STUDIO_GENERATEMAP_HPP