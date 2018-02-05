//
// MenuManager.hpp for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Thu Jun 15 16:09:53 2017 Hugo Baldassin
// Last update Thu Jun 15 16:10:04 2017 Hugo Baldassin
//

#ifndef		INDIE_STUDIO_MENUMANAGER_HPP
# define	INDIE_STUDIO_MENUMANAGER_HPP

# include	<OGRE/Ogre.h>
# include	<OGRE/SdkTrays.h>
# include	<OIS/OIS.h>
# include 	"MapManager.hpp"
# include	"EntitiesManager.hpp"

namespace game {

  class MenuManager : public OgreBites::SdkTrayListener {
  public:
    MenuManager();
    ~MenuManager();

    void launch(Ogre::RenderWindow *window, OIS::Mouse *mouse, OIS::Keyboard *keyboard,
		MapManager *mapManager, EntitiesManager *entitiesManager);

    void displayMenu(const std::string &name);

    void pauseGame();

    std::string actualMenu;
    std::vector<OgreBites::SdkTrayManager*> _sdkTrayManagers;
    bool stop;
    std::vector<OgreBites::SelectMenu*> _selectMenus;
    std::vector<OgreBites::SelectMenu*> _controllerMenus;
    std::vector<OgreBites::SelectMenu*> _controllerSetMenus;
    bool play;
    MapManager *_mapManager;
    EntitiesManager *_entitiesManager;
    bool pause;
    bool isingame;

  private:
    bool launchGame();
    bool validateConfig();

    void createMainMenu();
    void createGameMenu();
    void createPauseMenu();

    void initMap();
    void initEntities(int nbPlayer, int nbIA);
    void initPlayerConfig();
    void updateConfigFile();
    void updatePlayersConfig();

    void writeKeyboardConfig(int nbPlayer, std::ofstream &confFile, int selectPanelID);
    void writeGamePadConfig(int nbPlayer, int nbGamePad, std::ofstream &confFile);

    // Event Callbacks
    void buttonHit(OgreBites::Button* button);
    void itemSelected(OgreBites::SelectMenu* menu);

  };

}

#endif 		//INDIE_STUDIO_MENUMANAGER_HPP
