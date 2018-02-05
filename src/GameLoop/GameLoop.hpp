//
// GameLoop.hpp for indie_studio in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed May 31 16:26:39 2017 Hugo Willaume
// Last update Sun Jun 18 14:56:05 2017 Hugo Willaume
//

#ifndef                INDIE_GameLoop_HPP
# define                INDIE_GameLoop_HPP

# include <OGRE/Ogre.h>

# include "InputManager.hpp"
# include "MapManager.hpp"
# include "SoundManager.hpp"
# include "EntitiesManager.hpp"
# include "SceneManager.hpp"
# include "ScoreManager.hpp"
# include "GUIManager.hpp"
# include "ConfigData.hpp"
# include "MenuManager.hpp"

namespace game
{
    class GameLoop
    {
    public:
        GameLoop(Ogre::String pluginFile, Ogre::String);
        ~GameLoop();

        InputManager		*inputManager;
        SoundManager		*soundManager;
        EntitiesManager	*entitiesManager;
        SceneManager		*sceneManager;
        ScoreManager		*scoreManager;
        GUIManager		*guiManager;
        ConfigData		*configData;
        MapManager		*mapManager;
        MenuManager		*menuManager;

        void launch();
    private:
        Ogre::String	pluginFile;
        Ogre::String	cfgFile;

        Ogre::Root			*_root;
        Ogre::RenderWindow		*_window;

        void _init_config_files();
        bool _init_window();
    };
}

#endif                //INDIE_GameLoop_HPP