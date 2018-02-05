//
// Map.hpp for map in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Wed May  3 15:03:15 2017 dourches
// Last update Thu May  4 18:07:54 2017 dourches
//

#ifndef		MAP_HPP_
# define	MAP_HPP_

# include       <vector>
# include	"ITile.hpp"

namespace game
{
  class Map
  {
    private:
    std::vector<game::ITile *>	_map;
    int				_xMax;
    int				_yMax;

    public:
    Map(unsigned int xMax = 8, unsigned int yMax = 8);
    ~Map();

    std::vector<game::ITile *> const &getMap() const;
    void addTile(game::ITile *);
    void modTile(game::Tile , int, int);
    game::ITile const *getTile(int, int) const;
    int getYMax() const;
    int getXMax() const;
  };
}

#endif		// !MAP_HPP_
