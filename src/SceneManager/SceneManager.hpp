//
// SceneManager.hpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed May 31 16:46:10 2017 Hugo Willaume
// Last update Thu Jun 15 17:52:51 2017 Hugo Willaume
//

#ifndef                INDIE_SceneManager_HPP
# define                INDIE_SceneManager_HPP

# include		<vector>
# include		"OGRE/Ogre.h"
# include		"OGRE/Overlay/OgreOverlaySystem.h"

namespace game
{
  class SceneManager
  {
    public:
    SceneManager();
    ~SceneManager();

    void launch(Ogre::Root *root, Ogre::RenderWindow *win);

    Ogre::SceneManager *sceneMgr;
    Ogre::Camera *_camera;
    std::vector<Ogre::Viewport*> _vps;
    std::vector<Ogre::SceneNode*> _nodes;
    Ogre::OverlaySystem *_overlaySystem;
    Ogre::Viewport *_vp;


  };
}


#endif                /* !INDIE_SceneManager_HPP */

