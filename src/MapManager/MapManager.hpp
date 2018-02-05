//
// MapManager.hpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed Jun 14 13:55:17 2017 Hugo Willaume
// Last update Sun Jun 18 21:37:14 2017 Hugo Willaume
//

#ifndef INDIE_STUDIO_MAPMANAGER_HPP
# define INDIE_STUDIO_MAPMANAGER_HPP

#include "SceneManager.hpp"
#include "Map.hpp"

namespace game
{
  class MapManager
  {
    public:
    MapManager(Ogre::SceneManager &scene);
    ~MapManager();

    Ogre::Vector3 map_pos_to_vector(int x, int y);
    Ogre::Vector2 vector_to_map_pos(Ogre::Vector3 pos);

    void create_map(unsigned int maxX, unsigned int maxY);
    void load_map(const std::string & mapname = "");
    void start_classic_map();
    std::shared_ptr<game::Map> get_map();
    void modTile(game::Tile tile, int x, int y);
    void unload_map();

    private:

    void _create_plane();
    void _load_map_file();
    void _render_map();

    std::string			_map_name;
    std::fstream		_map_file;
    std::shared_ptr<game::Map>	_map;

    Ogre::SceneManager		&sceneMgr;

    std::vector<Ogre::SceneNode *>	_tiles_nodes;
    std::vector<Ogre::Entity *>		_tiles_entities;

    Ogre::Plane			*_plane;
    Ogre::Entity		*_plane_entity;
    Ogre::SceneNode		*_plane_node;
  };
}

#endif //INDIE_STUDIO_MAPMANAGER_HPP
