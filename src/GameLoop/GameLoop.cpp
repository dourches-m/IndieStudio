//
// GameLoop.cpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed May 31 17:17:29 2017 Hugo Willaume
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//

#include "GameLoop.hpp"

game::GameLoop::GameLoop(Ogre::String resources, Ogre::String plugins) : pluginFile(plugins),
								   cfgFile(resources)
{
  std::srand(std::time(nullptr));
  inputManager = new InputManager;
  //soundManager = new SoundManager;
  entitiesManager = new EntitiesManager;
  sceneManager = new SceneManager;
  scoreManager = new ScoreManager;
  guiManager = new GUIManager;
  configData = new ConfigData;
  menuManager = new MenuManager;
  soundManager = new SoundManager;
}

game::GameLoop::~GameLoop()
{
  inputManager->windowClosed(_window);
  delete inputManager;
//  delete soundManager;
  delete entitiesManager;
  delete sceneManager;
  delete scoreManager;
  delete guiManager;
  delete configData;
  delete menuManager;
  delete _root;
}

void game::GameLoop::launch()
{
  _root = new Ogre::Root(pluginFile);
  if (!_init_window())
    return ;
  sceneManager->launch(_root, _window);
  _init_config_files();
  entitiesManager->launch(sceneManager);
  entitiesManager->mapManager = new MapManager(*sceneManager->sceneMgr);
  inputManager->launch(_window, _root, true, true, true, entitiesManager);
  menuManager->launch(_window, inputManager->getMouse(), inputManager->getKeyboard(),
		      mapManager, entitiesManager);
  inputManager->setMenuManager(menuManager);
  inputManager->inputLinker.setEntitiesManager(entitiesManager);

  _root->startRendering();
  Ogre::LogManager::getSingleton().logMessage("\n\nStopped rendering.\n\n");
}

void game::GameLoop::_init_config_files()
{
  Ogre::ConfigFile	conf_file;

  conf_file.load(cfgFile);
  auto secIt = conf_file.getSectionIterator();
  Ogre::String name, locType;
  while (secIt.hasMoreElements())
    {
      Ogre::ConfigFile::SettingsMultiMap *settings = secIt.getNext();
      for (auto it : *settings)
	{
	  name = it.second;
	  locType = it.first;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
	}
    }
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  sceneManager->sceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
  std::cout << "Finished confFile" << std::endl;
}

bool game::GameLoop::_init_window()
{
  if (!(_root->restoreConfig() || _root->showConfigDialog()))
    return false;
  _window = _root->initialise(true, "Indie Studio - Bomberman");
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::LogManager::getSingleton().logMessage("Loaded window!");
  return true;
}
