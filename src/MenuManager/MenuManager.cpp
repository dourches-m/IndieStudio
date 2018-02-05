//
// MenuManager.cpp for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Thu Jun 15 16:18:02 2017 Hugo Baldassin
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//

#include <random>
#include <ConfigData.hpp>
#include "MenuManager.hpp"

// -----------------------------------------------------------------------------
game::MenuManager::MenuManager():
  _sdkTrayManagers(0),
  stop(false),
  _selectMenus(0),
  _controllerMenus(0),
  _controllerSetMenus(0),
  play(false),
  pause(false),
  isingame(false)
{
}

// -----------------------------------------------------------------------------
game::MenuManager::~MenuManager()
{
  if (_sdkTrayManagers.size())
    {
      _sdkTrayManagers[0]->destroyAllWidgets();
      _sdkTrayManagers[1]->destroyAllWidgets();
      delete _sdkTrayManagers[0];
      delete _sdkTrayManagers[1];
    }
}

// -----------------------------------------------------------------------------
void game::MenuManager::launch(Ogre::RenderWindow *window, OIS::Mouse *mouse,
			       OIS::Keyboard *keyboard, MapManager *mapManager,
			       EntitiesManager *entitiesManager)
{
  OgreBites::InputContext inputContext;

  _entitiesManager = entitiesManager;
  _mapManager = mapManager;
  inputContext.mKeyboard = keyboard;
  inputContext.mMouse = mouse;
  actualMenu = "MainMenu";

  _sdkTrayManagers.push_back(new OgreBites::SdkTrayManager("MainMenu", window, inputContext, this));
  _sdkTrayManagers.push_back(new OgreBites::SdkTrayManager("GameMenu", window, inputContext, this));
  _sdkTrayManagers.push_back(new OgreBites::SdkTrayManager("PauseMenu", window, inputContext, this));

  createMainMenu();
  createGameMenu();
  createPauseMenu();
}

// -----------------------------------------------------------------------------
void game::MenuManager::displayMenu(const std::string &name)
{
  _sdkTrayManagers[0]->hideAll();
  _sdkTrayManagers[1]->hideAll();
  _sdkTrayManagers[2]->hideAll();
  if (name == "MainMenu")
    _sdkTrayManagers[0]->showAll();
  else if (name == "GameMenu")
    _sdkTrayManagers[1]->showAll();
  else if (name == "PauseMenu")
    _sdkTrayManagers[2]->showAll();
  actualMenu = name;
}

// -----------------------------------------------------------------------------
void game::MenuManager::buttonHit(OgreBites::Button *button)
{
  if (button->getName() == "mPlayButton")
    displayMenu("GameMenu");
  else if (button->getName() == "mBackButton")
    displayMenu("MainMenu");
  else if (button->getName() == "mQuitButton")
    stop = true;
  else if (button->getName() == "mGoButton" && launchGame())
  {
    isingame = true;
    play = true;
    displayMenu("None");
    game::ConfigData::getInstance().initData();
  }
  else if (button->getName() == "mResumeButton")
  {
    pause = false;
    displayMenu("None");
  }
  else if (button->getName() == "mBackToMenuButton")
  {
    std::cerr << "BAK TO MENU" << std::endl;
    pause = false;
    play = false;
    isingame = false;
    _entitiesManager->unload();
    _mapManager->unload_map();
    displayMenu("MainMenu");
  }

}

// -----------------------------------------------------------------------------
void game::MenuManager::itemSelected(OgreBites::SelectMenu *menu)
{
  std::stringstream selectMenu("mGameMenuPlayer");

  (void)menu;
  for (unsigned int i = 0; i < _selectMenus.size(); ++i)
  {
    if (_selectMenus[i]->getSelectedItem() == "Player")
      _controllerMenus[i]->show();
    else
      _controllerMenus[i]->hide();
  }
  for (unsigned int i = 0; i < _controllerMenus.size(); ++i)
  {
    if (_controllerMenus[i]->isVisible() && _controllerMenus[i]->getSelectedItem() == "Keyboard")
      _controllerSetMenus[i]->show();
    else
      _controllerSetMenus[i]->hide();
  }
}

// -----------------------------------------------------------------------------
bool game::MenuManager::launchGame()
{
  if (!validateConfig())
    return false;
  play = true;
  initMap();
  updateConfigFile();
  std::cerr << "EXITED LAUNCHGAME WITH TRUE" << std::endl;
  return true;
}

// -----------------------------------------------------------------------------
bool game::MenuManager::validateConfig()
{
  int nbKeyboards = 0;
  int nbPlayers = 0;

  for (unsigned int i = 0; i < _controllerMenus.size(); ++i)
  {
    if (_controllerMenus[i]-> isVisible() &&
	_controllerMenus[i]->getSelectedItem() == "Keyboard")
      nbKeyboards++;
    if (_selectMenus[i]->getSelectedItem() != "None")
      nbPlayers++;
  }
  if (nbKeyboards > 2)
  {
    _sdkTrayManagers[1]->showOkDialog("mGameMenuOKDialog", "Error: only two keyboard users allowed.");
    return false;
  }
  else if (nbPlayers < 2)
  {
    _sdkTrayManagers[1]->showOkDialog("mGameMenuOKDialog", "Error: a minimum of two Players / IA is required.");
    return false;
  }
  return true;
}

// -----------------------------------------------------------------------------
void game::MenuManager::createMainMenu()
{
  // === Main Menu ===
  _sdkTrayManagers[0]->showLogo(OgreBites::TL_BOTTOMLEFT);
  _sdkTrayManagers[0]->createLabel(OgreBites::TL_TOP, "mMainMenuLabel", "Main Menu", 300);
  _sdkTrayManagers[0]->createButton(OgreBites::TL_CENTER, "mPlayButton", "Play", 220);
  _sdkTrayManagers[0]->createButton(OgreBites::TL_CENTER, "mQuitButton", "Quit", 220);
  _sdkTrayManagers[0]->showBackdrop("MainMenuBackdrop");
}

// -----------------------------------------------------------------------------
void game::MenuManager::createGameMenu()
{
  Ogre::StringVector playerTypeParams;
  Ogre::StringVector playerControllerParams;
  Ogre::StringVector playerControllerSetParams;
  Ogre::StringVector mapParams;

  playerTypeParams.push_back("None");
  playerTypeParams.push_back("Player");
  playerTypeParams.push_back("IA");
  playerControllerParams.push_back("Keyboard");
  playerControllerParams.push_back("GamePad");
  playerControllerSetParams.push_back("Set1");
  playerControllerSetParams.push_back("Set2");
  mapParams.push_back("Standard");
  mapParams.push_back("Small");
  mapParams.push_back("Medium");
  mapParams.push_back("Large");

  // === Game Menu ===
  // Player 1
  //_sdkTrayManagers[1]->createLabel(OgreBites::TL_TOP, "mGameMenuLabel", "Game Menu", 300);
  _sdkTrayManagers[1]->createLabel(OgreBites::TL_CENTER, "mGameMenuPlayer1Label", "Player1", 280);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER,"mGameMenuPlayer1Select",
					     "Player Type", 270, 3, playerTypeParams);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer1Select2",
					     "Player Controller", 270, 3, playerControllerParams)->hide();
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer1Select3",
					     "Keys Set", 270, 3, playerControllerSetParams)->hide();
  _sdkTrayManagers[1]->createSeparator(OgreBites::TL_CENTER, "mGameMenuPlayer1Separator", 270);
  _selectMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer1Select")));
  _controllerMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer1Select2")));
  _controllerSetMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer1Select3")));

  // Player 2
  _sdkTrayManagers[1]->createLabel(OgreBites::TL_CENTER, "mGameMenuPlayer2Label", "Player2", 280);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer2Select",
					     "Player Type", 270, 3, playerTypeParams);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer2Select2",
					     "Player Controller", 270, 3, playerControllerParams)->hide();
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer2Select3",
					     "Keys Set", 270, 3, playerControllerSetParams)->hide();
  _sdkTrayManagers[1]->createSeparator(OgreBites::TL_CENTER, "mGameMenuPlayer2Separator", 270);
  _selectMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer2Select")));
  _controllerMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer2Select2")));
  _controllerSetMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer2Select3")));

  // Player 3
  _sdkTrayManagers[1]->createLabel(OgreBites::TL_CENTER, "mGameMenuPlayer3Label", "Player3", 280);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer3Select",
					     "Player Type", 270, 3, playerTypeParams);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer3Select2",
					     "Player Controller", 270, 3, playerControllerParams)->hide();
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer3Select3",
					     "Keys Set", 270, 3, playerControllerSetParams)->hide();
  _sdkTrayManagers[1]->createSeparator(OgreBites::TL_CENTER, "mGameMenuPlayer3Separator", 270);
  _selectMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer3Select")));
  _controllerMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer3Select2")));
  _controllerSetMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer3Select3")));

  // Player 4
  _sdkTrayManagers[1]->createLabel(OgreBites::TL_CENTER, "mGameMenuPlayer4Label", "Player4", 280);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer4Select",
					     "Player Type", 270, 3, playerTypeParams);
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer4Select2",
					     "Player Controller", 270, 3, playerControllerParams)->hide();
  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_CENTER, "mGameMenuPlayer4Select3",
					     "Keys Set", 270, 3, playerControllerSetParams)->hide();
  _selectMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer4Select")));
  _controllerMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer4Select2")));
  _controllerSetMenus.push_back(static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mGameMenuPlayer4Select3")));

  _sdkTrayManagers[1]->createButton(OgreBites::TL_BOTTOMRIGHT, "mGoButton", "Go !", 220);
  _sdkTrayManagers[1]->createButton(OgreBites::TL_BOTTOMLEFT, "mBackButton", "Back", 220);

  _sdkTrayManagers[1]->createThickSelectMenu(OgreBites::TL_LEFT, "mMapMenu", "Map Type", 270, 4, mapParams);

  _sdkTrayManagers[1]->showBackdrop("GameMenuBackdrop");
  _sdkTrayManagers[1]->setWidgetPadding(15);
  _sdkTrayManagers[1]->hideAll();
  initPlayerConfig();
}

// -----------------------------------------------------------------------------
void game::MenuManager::initPlayerConfig()
{
  int i = 1;
  std::string section("Player1");
  std::string key;

  while (game::ConfigData::getInstance().getKeyExists(section + "/Controller"))
  {
    key = section + "/";
    std::cout << "Section: " << section << " I: " << i << std::endl;
    _selectMenus[i - 1]->selectItem("Player");
    if (ConfigData::getInstance().getValueAsString(key + "Controller") == "GamePad")
      _controllerMenus[i - 1]->selectItem("GamePad");
    else
    {
      _controllerMenus[i - 1]->selectItem("Keyboard");
      if (ConfigData::getInstance().getValueAsString(key + "KeySet") == "Set1")
	_controllerSetMenus[i - 1]->selectItem("Set1");
      else
	_controllerSetMenus[i - 1]->selectItem("Set2");
    }
    i++;
    section[section.size() - 1] = i + 48;
  }
}

// -----------------------------------------------------------------------------
void game::MenuManager::updateConfigFile()
{
  updatePlayersConfig();
}

// -----------------------------------------------------------------------------
void game::MenuManager::updatePlayersConfig()
{
  int nbGamePad = 0;
  int nbPlayer = 0;
  int nbIA = 0;
  std::ofstream confFile("BomberConfig.txt", std::ofstream::trunc);

  if (!confFile.is_open())
  {
    Ogre::LogManager::getSingleton().logMessage("\nFailed to edit config file: BomberConfig.txt.\n");
    return ;
  }
  confFile.clear();
  for (unsigned int i = 0; i < _selectMenus.size(); ++i)
  {
    if (_selectMenus[i]->getSelectedItem() == "IA")
      nbIA++;
    if (_selectMenus[i]->getSelectedItem() == "Player")
    {
      nbPlayer++;
      if (_controllerMenus[i]->getSelectedItem() == "Keyboard")
	writeKeyboardConfig(nbPlayer, confFile, i);
      else
      {
	nbGamePad++;
	writeGamePadConfig(nbPlayer, nbGamePad, confFile);
      }
    }
  }
  confFile.close();
  initEntities(nbPlayer, nbIA);
}

// -----------------------------------------------------------------------------
void game::MenuManager::writeKeyboardConfig(int nbPlayer, std::ofstream &confFile, int selectPanelID)
{
  std::string section("[Player");

  section += std::to_string(nbPlayer) + "]\n";
  confFile << section;
  confFile << "Controller = Keyboard\n";
  confFile << "KeySet = " + _controllerSetMenus[selectPanelID]->getSelectedItem() + "\n";
  confFile << "\n";
}

// -----------------------------------------------------------------------------
void game::MenuManager::writeGamePadConfig(int nbPlayer, int nbGamePad, std::ofstream &confFile)
{
  std::string section("[Player");
  std::string line("ControllerID = ");

  section += std::to_string(nbPlayer) + "]\n";
  line += std::to_string(nbGamePad) + "\n";
  confFile << section;
  confFile << "Controller = GamePad\n";
  confFile << line;
  confFile << "\n";
}

// -----------------------------------------------------------------------------
void game::MenuManager::initMap()
{
  OgreBites::SelectMenu *mapMenu;
  std::string type;

  mapMenu = static_cast<OgreBites::SelectMenu*>(_sdkTrayManagers[1]->getWidget("mMapMenu"));
  type = mapMenu->getSelectedItem();

  std::cerr << "MAP TYPE CHOSEN IS " << type << std::endl;
   if (type == "Small")
    _entitiesManager->mapManager->create_map(10, 10);
  else if (type == "Medium")
    _entitiesManager->mapManager->create_map(15, 15);
  else if (type == "Large")
    _entitiesManager->mapManager->create_map(20, 20);
  else
    _entitiesManager->mapManager->start_classic_map();


  _mapManager = _entitiesManager->mapManager;
}

// -----------------------------------------------------------------------------
void game::MenuManager::initEntities(int nbPlayer, int nbIA)
{
  std::vector<std::string> skins = {"ninjablue.mesh", "ninjared.mesh", "ninjayellow.mesh", "ninja.mesh"};
  std::vector<Ogre::Vector2> positions = {{1, 1}, {1, static_cast<Ogre::Real>(_mapManager->get_map().get()->getYMax()) - 2},
					  {static_cast<Ogre::Real>(_mapManager->get_map().get()->getYMax()) - 2, 1},
					  {static_cast<Ogre::Real>(_mapManager->get_map().get()->getYMax()) - 2,
						  static_cast<Ogre::Real>(_mapManager->get_map().get()->getYMax()) - 2}};

  std::random_device rd;

  std::shuffle(skins.begin(), skins.end(), std::mt19937(rd()));

  int	i;

  for (i = 0; i < nbPlayer; i++)
    _entitiesManager->spawn_player(positions[i].x, positions[i].y, skins[i]);
  for (i = i; i < nbPlayer; i++)
    _entitiesManager->spawn_AI(positions[i].x, positions[i].y, skins[i]);

}

// -----------------------------------------------------------------------------
void game::MenuManager::pauseGame()
{
  if (actualMenu == "None")
  {
    pause = true;
    displayMenu("PauseMenu");
  }
}

// -----------------------------------------------------------------------------
void game::MenuManager::createPauseMenu()
{
  _sdkTrayManagers[2]->createButton(OgreBites::TL_CENTER, "mResumeButton", "Resume", 270);
  _sdkTrayManagers[2]->createButton(OgreBites::TL_CENTER, "mBackToMenuButton", "Back to Menu", 270);
  _sdkTrayManagers[2]->hideAll();
}

