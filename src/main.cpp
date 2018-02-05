//
// main.cpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Fri Jun 2 22:21:50 2017 Hugo Willaume
// Last update Wed Jun 14 17:22:35 2017 Hugo Willaume
//

#include "GameLoop/GameLoop.hpp"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
# define WIN32_LEAN_AND_MEAN
# include "windows.h"

#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main()
#endif
{
// Create application object
  game::GameLoop app("resources.cfg", "plugins.cfg");

try {
    app.launch();
} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
}
return 0;
}

#ifdef __cplusplus
}
#endif
