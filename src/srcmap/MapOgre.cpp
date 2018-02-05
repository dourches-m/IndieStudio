//
// MapOgre.cpp for  in /home/dourches/Epitech
//
// Made by Martin Dourches
// Login   <martin.dourches@epitech.eu>
//
// Started on  ven. juin 2 12:26:24 2017 Martin Dourches
// Last update ven. juin 2 12:26:24 2017 Martin Dourches
//

#include <SceneManager.hpp>
#include "Map.hpp"

void	BuildTile(std::string const &tex, Ogre::SceneManager * scene, int x, int y)
{
  Ogre::Entity* blockEntity = scene->createEntity(tex);
  Ogre::SceneNode* blocknode = scene->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x * 100, y * 100,0));
  blocknode->attachObject(blockEntity);
}

void	MapOgre(Ogre::SceneManager *scene, game::Map *map)
{
  int y;
  int x;

  y = 0;
  Ogre::Plane plane(Ogre::Vector3::UNIT_Y,0);

  Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1000, 1000, 0, 0);
  Ogre::Entity* groundEntity = scene->createEntity("ground");
  scene->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
  groundEntity->setMaterialName("Tusk");
  groundEntity->setCastShadows(false);

  while (y != map->getYMax())
    {
      x = 0;
      while (x != map->getXMax())
	{
	  BuildTile(map->getTile(x, y)->getTexture(), scene, x, y);
	  x++;
	}
      y++;
    }
}