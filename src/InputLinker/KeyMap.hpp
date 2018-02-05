//
// KeyMap.hpp for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Wed Jun 14 15:48:44 2017 Hugo Baldassin
// Last update Wed Jun 14 17:22:35 2017 Hugo Willaume
//

#ifndef		INDIE_STUDIO_KEYMAP_HPP
# define	INDIE_STUDIO_KEYMAP_HPP

# include	"AMovableEntity.hpp"

struct 		KeyMap {
  int		controllerID;
  int		playerID;
  bool		gamePad;
  std::map<int, game::AMovableEntity::e_action> keyMap;
};

#endif		//INDIE_STUDIO_KEYMAP_HPP

