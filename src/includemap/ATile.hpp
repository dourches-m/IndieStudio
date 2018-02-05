//
// ATile.hpp for Atile in /home/dourches/Epitech/Seconde/CPP/cpp_indie_studio/src
// 
// Made by dourches
// Login   <martin.dourches@epitech.eu>
// 
// Started on  Wed May  3 16:19:37 2017 dourches
// Last update Sat Jun 17 15:19:50 2017 Hugo Willaume
//

#ifndef		ATILE_HPP_
# define	ATILE_HPP_

# include <string>
# include	"ITile.hpp"

namespace game
{
class ATile : public ITile
{
 protected:
  std::string _tex;
  game::Tile tile;
  
 public:
  ATile(std::string texture, game::Tile tiletype) : _tex(texture), tile(tiletype) {};
  ~ATile() {};
  
  virtual void setTexture(std::string const &) = 0;
  virtual std::string const &getTexture() const = 0;
  virtual game::Tile getType() const = 0;
};
}

#endif		//ATILE_HPP_
