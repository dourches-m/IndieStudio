/*
** InputLinker.h for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
**
** Made by Hugo Baldassin
** Login   <baldas@epitech.net>
**
** Started on  Mon Jun 12 20:54:25 2017 Hugo Baldassin
** Last update Mon Jun 12 20:54:26 2017 Hugo Baldassin
*/

#ifndef 	INDIE_STUDIO_INPUTLINKER_H
# define 	INDIE_STUDIO_INPUTLINKER_H

# include 	<OIS/OIS.h>
# include 	<OIS/OISJoyStick.h>
# include	<map>
# include 	<mutex>
# include	"EntitiesManager.hpp"
# include	"KeyMap.hpp"

namespace game {

  class InputLinker {
  public:
    InputLinker(EntitiesManager *entitiesManager, bool playing);
    ~InputLinker();

    void initPlayersMaps();

    void sendKeyboardEvent(const OIS::KeyEvent& ke);
    void sendStickButtonEvent(int controllerID, int button);
    void sendStickAxisEvent(int controllerID, AMovableEntity::e_action dir);

    void setPlaying(bool playing);
    void setEntitiesManager(EntitiesManager *entitiesManager);

  private:
    void setConfigKeys(KeyMap *keyMap, std::string section);
    void setKeyCode(KeyMap *keyMap, std::string keyCode, AMovableEntity::e_action action);
    void setKeyConfig1(KeyMap *keyMap);
    void setKeyConfig2(KeyMap *keyMap);

    EntitiesManager *_entitiesManager;
    bool _playing;
    std::vector<KeyMap*> _keyMaps;
  };

}

#endif //INDIE_STUDIO_INPUTLINKER_H
