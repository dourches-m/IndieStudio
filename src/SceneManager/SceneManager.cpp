//
// SceneManager.cpp for indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Wed May 31 19:06:51 2017 Hugo Baldassin
// Last update Thu Jun 15 17:52:51 2017 Hugo Willaume
//

#include <exception>
#include "SceneManager.hpp"

game::SceneManager::SceneManager():
  _camera(nullptr),
  _overlaySystem(nullptr)
{
}

void game::SceneManager::launch(Ogre::Root *root,
				Ogre::RenderWindow *window)
{
  sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
  sceneMgr->setAmbientLight(Ogre::ColourValue(0.7, 0.7, 0.7));
  sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  _overlaySystem = new Ogre::OverlaySystem();
  sceneMgr->addRenderQueueListener(_overlaySystem);
  _camera = sceneMgr->createCamera("Cam");
  _camera->setPosition(Ogre::Vector3(0, 3000, -300));
  _camera->lookAt(Ogre::Vector3::ZERO);
  _vp = window->addViewport(_camera);
  _vp->setBackgroundColour(Ogre::ColourValue(0.2, 0.4, 0.3));
}

game::SceneManager::~SceneManager()
{

}
