//
// MapManager.cpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed Jun 14 13:55:29 2017 Hugo Willaume
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//

#include "MapGeneration.hpp"
#include "MapManager.hpp"
#include "TileBase.hpp"
#include "TileDestroy.hpp"
#include "TileInde.hpp"

game::MapManager::MapManager(Ogre::SceneManager &scene) : _map_name(""), _map_file(""),
							  _map(nullptr),
							  sceneMgr(scene),
							  _plane(nullptr),
							  _plane_entity(nullptr), _plane_node(nullptr)
{
}

game::MapManager::~MapManager()
{
  unload_map();
}

void		game::MapManager::start_classic_map()
{
  Ogre::Vector2 pos(0, 0);
  std::vector<Ogre::Vector2> safe_pos{{1, 1}, {1, 2}, {2, 1}, {11, 1}, {10, 1}, {11, 2},
				      {1, 11}, {1, 10}, {2, 11}, {11, 11}, {10, 11}, {11, 10}};

  if (_map)
    return;
  _map = std::make_shared<game::Map>(13, 13);
  while (pos.y < 13)
  {
    while (pos.x < 13)
    {
      if (pos.x == 0 || pos.y == 0 || pos.x == 12 || pos.y == 12
	  || (static_cast<int>(pos.x) % 2 != 0 && static_cast<int>(pos.y) % 2 != 0))
	_map.get()->addTile(new game::TileInde("cubeinde.mesh"));
      else if (std::rand() % 100 < 80)
	_map.get()->addTile(new game::TileDestroy("cubedestroy.mesh"));
      else
	_map.get()->addTile(new game::TileBase("cubebase.mesh"));
      pos.x++;
    }
    pos.x = 0;
    pos.y++;
  }
  for (auto it : safe_pos) {
    _map.get()->modTile(game::Tile::Base, static_cast<int>(it.x),
			static_cast<int>(it.y));
  }
  _render_map();
}

void 		game::MapManager::modTile(game::Tile tile, int x, int y)
{
  int	vecpos = y * _map.get()->getYMax() + x;

  std::cerr << "Prepared to modtile" << std::endl;
  _map->modTile(tile, x, y);
  std::cerr << "Ready to do graphics shit" << std::endl;
  _tiles_nodes[vecpos]->detachObject(_tiles_entities[vecpos]);
  std::cerr << "Detached done" << std::endl;
  sceneMgr.destroyEntity(_tiles_entities[vecpos]);
  std::cerr << "Destroyed done" << std::endl;
  _tiles_entities[vecpos] = sceneMgr.createEntity(_map.get()->getTile(x, y)->getTexture());
  std::cerr << "Create done" << std::endl;
  _tiles_nodes[vecpos]->attachObject(_tiles_entities[vecpos]);
  std::cerr << "Attach done" << std::endl;
  std::cerr << "Graphic shit done" << std::endl;

}

Ogre::Vector3	game::MapManager::map_pos_to_vector(int x, int y)
{
  return Ogre::Vector3((-(_map.get()->getXMax() * 100 / 2) + x * 100) + 50,
	  50, (-(_map.get()->getYMax() * 100 / 2) + y * 100) + 50);
}

Ogre::Vector2	game::MapManager::vector_to_map_pos(Ogre::Vector3 pos)
{
  return Ogre::Vector2(static_cast<int>((pos.x + (_map.get()->getXMax() * 100 / 2)) / 100),
		       static_cast<int>((pos.z + (_map.get()->getXMax() * 100 / 2)) / 100));
}

void game::MapManager::create_map(unsigned int maxX, unsigned int maxY)
{
  if (_map)
    {
      std::cerr << "Map already exists" << std::endl;
      return;
    }
  int	idx= 0;
  MapGeneration	generator;

  while ((_map_name == "" || !_map_file.is_open()) && idx < 100)
    {
      _map_name = "bombMapFile" + std::to_string(std::rand() % 10000) + ".txt";
      _map_file.open(_map_name, std::fstream::out | std::fstream::in | std::fstream::trunc);
      idx++;
    }
  if (idx == 100)
    {
      std::cerr << "No possible name for the map" << std::endl;
      return;
    }
  _map_file.close();
  if (generator.createRandomMap(maxX, maxY, _map_name) == EXIT_FAILURE)
    {
      std::cerr << "Could not create map" << std::endl;
      return;
    }
  _map = std::make_shared<game::Map>(maxX, maxY);
  load_map(_map_name);
}

void game::MapManager::_create_plane()
{
  _plane = new Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);

  Ogre::MeshManager::getSingleton().createPlane(
	  "ground",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  *_plane,
	  _map.get()->getXMax() * 100, _map.get()->getYMax() * 100, 5, 5,
	  true,
	  1, 1, 1,
	  Ogre::Vector3::UNIT_Z);

  _plane_entity = sceneMgr.createEntity("ground");
  _plane_node = sceneMgr.getRootSceneNode()->createChildSceneNode();

  _plane_node->attachObject(_plane_entity);
  _plane_entity->setMaterialName("Ogre/Skin");
  _plane_entity->setCastShadows(false);

  sceneMgr.getCamera("Cam")->setPosition(
	  Ogre::Vector3(0,
			_map.get()->getYMax() * 120,
			_map.get()->getYMax() * 60));
  sceneMgr.getCamera("Cam")->lookAt(Ogre::Vector3(0,0,0));
}

void game::MapManager::_render_map()
{
  int			idx = 0;
  Ogre::Vector3		pos(-(_map->getYMax() * 100 / 2) + 50
	  , 50
	  , -(_map->getYMax() * 100 / 2) + 50);

  _create_plane();
  for(auto it : _map.get()->getMap())
    {
      _tiles_nodes.push_back(_plane_node->createChildSceneNode());
      _tiles_entities.push_back(sceneMgr.createEntity(it->getTexture()));
      _tiles_nodes.back()->setPosition(pos);
      _tiles_nodes.back()->_updateBounds();
      pos.x += 100;
      if (pos.x == (_map->getYMax() * 100 / 2) + 50)
	{
	  pos.x = -(_map->getYMax() * 100 / 2) + 50;
	  pos.z += 100;
	}
      _tiles_nodes.back()->attachObject(_tiles_entities.back());
      idx++;
    }
}

void game::MapManager::_load_map_file()
{
  std::string	line;

  while (!_map_file.eof())
    {
      getline(_map_file, line);
      for(int i = 0; line[i]; i++)
	{
	  switch (line[i])
	    {
	      case '0':
		_map->addTile(new game::TileBase ("cubebase.mesh"));
	      break;
	      case '1':
		_map->addTile(new game::TileDestroy ("cubedestroy.mesh"));
	      break;
	      case '2':
		_map->addTile(new game::TileInde("cubeinde.mesh"));
	      break;
	      default:
		Ogre::LogManager::getSingleton().logMessage("Unknown case loaded in _load_map_file.()");
	      break;
	    }
	}
    }
  _render_map();
}

void game::MapManager::load_map(const std::string & mapname)
{
  if (mapname == "")
    return ;
  else if (!_map_file.is_open())
    _map_file.open(mapname);
  if (!_map_file.is_open() || _map_file.bad())
    {
      std::cerr << "broken file " << std::endl;
      return;
    }
  _load_map_file();
}

std::shared_ptr<game::Map> game::MapManager::get_map()
{
  return _map;
}

void game::MapManager::unload_map()
{
  if (_plane_entity == nullptr || _plane_node == nullptr || _map == nullptr)
    return;
  _map.reset();
  _plane = nullptr;
  _plane_entity = nullptr;
  _map_file.close();
  std::remove(_map_name.c_str());
  _plane_node->removeAndDestroyAllChildren();
  Ogre::MeshManager::getSingleton().unload("ground");
  Ogre::MeshManager::getSingleton().remove("ground");
  _plane_node = nullptr;
}