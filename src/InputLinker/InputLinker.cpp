//
// Game::InputLinker.cpp for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Mon Jun 12 20:54:11 2017 Hugo Baldassin
// Last update Sun Jun 18 01:50:10 2017 Hugo Willaume
//

#include "InputLinker.hpp"
#include "ConfigData.hpp"
#include "PlayerManager.hpp"

// -----------------------------------------------------------------------------
game::InputLinker::InputLinker(EntitiesManager *entitiesManager, bool playing):
	_entitiesManager(entitiesManager),
	_playing(playing)
{
}

// -----------------------------------------------------------------------------
game::InputLinker::~InputLinker()
{
  for (unsigned int i = 0; i < _keyMaps.size(); ++i)
    delete _keyMaps[i];
}

// -----------------------------------------------------------------------------
void game::InputLinker::initPlayersMaps()
{
  std::string section("Player1");
  std::string key;
  int i = 1;

  if (_keyMaps.size())
    _keyMaps.clear();
  if (!ConfigData::getInstance().getKeyExists(section + "/Controller"))
    throw Ogre::Exception(Ogre::Exception::ERR_ITEM_NOT_FOUND,
			  "Configuration section: " + section + " or key " + section + "/Controller not found", "ConfigData::getValue");
  while (ConfigData::getInstance().getKeyExists(section + "/Controller") && i < 5)
  {
    key = section + "/";
    _keyMaps.push_back(new KeyMap);
    _keyMaps.back()->playerID = i;
    if (ConfigData::getInstance().getValueAsString(key + "Controller") == "GamePad")
      _keyMaps.back()->gamePad = true;
    else
      _keyMaps.back()->gamePad = false;
    if (_keyMaps.back()->gamePad)
      _keyMaps.back()->controllerID = ConfigData::getInstance().getValueAsInt(key + "ControllerID") - 1;
    else
      _keyMaps.back()->controllerID = -1;
    setConfigKeys(_keyMaps.back(), key);
    i++;
    section[section.size() - 1] = i + 48;
  }
}

// -----------------------------------------------------------------------------
void game::InputLinker::setConfigKeys(KeyMap *keyMap, std::string section)
{
  if (keyMap->gamePad)
    setKeyCode(keyMap, "A", AMovableEntity::PLACE_BOMB);
  else if (!keyMap->gamePad)
  {
    if (!ConfigData::getInstance().getKeyExists(section + "KeySet") ||
	ConfigData::getInstance().getValueAsString(section + "KeySet") == "Set1")
      setKeyConfig1(keyMap);
    else
      setKeyConfig2(keyMap);
  }
}

// -----------------------------------------------------------------------------
void game::InputLinker::setKeyConfig1(KeyMap *keyMap)
{
  setKeyCode(keyMap, "SPACE", AMovableEntity::PLACE_BOMB);
  setKeyCode(keyMap, "UP", AMovableEntity::MOVE_UP);
  setKeyCode(keyMap, "DOWN", AMovableEntity::MOVE_DOWN);
  setKeyCode(keyMap, "LEFT", AMovableEntity::MOVE_LEFT);
  setKeyCode(keyMap, "RIGHT", AMovableEntity::MOVE_RIGHT);
}

// -----------------------------------------------------------------------------
void game::InputLinker::setKeyConfig2(KeyMap *keyMap)
{
  setKeyCode(keyMap, "E", AMovableEntity::PLACE_BOMB);
  setKeyCode(keyMap, "Z", AMovableEntity::MOVE_UP);
  setKeyCode(keyMap, "S", AMovableEntity::MOVE_DOWN);
  setKeyCode(keyMap, "Q", AMovableEntity::MOVE_LEFT);
  setKeyCode(keyMap, "D", AMovableEntity::MOVE_RIGHT);
}

// -----------------------------------------------------------------------------
void game::InputLinker::setKeyCode(KeyMap *keyMap, std::string val, AMovableEntity::e_action action)
{
  if (keyMap->gamePad)
  {
    if (val == "A")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(0, action));
  }
  else
  {
    if (val == "SPACE")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_SPACE, action));
    else if (val == "UP")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_UP, action));
    else if (val == "DOWN")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_DOWN, action));
    else if (val == "LEFT")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_LEFT, action));
    else if (val == "RIGHT")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_RIGHT, action));
    else if (val == "Z")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_Z, action));
    else if (val == "Q")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_Q, action));
    else if (val == "S")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_S, action));
    else if (val == "D")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_D, action));
    else if (val == "E")
      keyMap->keyMap.insert(std::pair<int, AMovableEntity::e_action>(OIS::KC_E, action));
  }
}

// -----------------------------------------------------------------------------
void game::InputLinker::sendKeyboardEvent(const OIS::KeyEvent &ke)
{
  KeyMap *map;
  int keyCode;

  keyCode = ke.key;
  if (_playing)
  {
    for (unsigned int i = 0; i < _keyMaps.size(); ++i)
    {
      map = _keyMaps[i];
      if (!map->gamePad && map->keyMap.count(ke.key))
	dynamic_cast<PlayerManager *>(_entitiesManager->players[map->playerID - 1])->apply_input_kbd(map->keyMap.at(keyCode));
    }
  }
}

// -----------------------------------------------------------------------------
void game::InputLinker::sendStickButtonEvent(int controllerID, int button)
{
  KeyMap *map;

  if (_playing)
    {
      for (unsigned int i = 0; i < _keyMaps.size(); ++i)
	{
	  map = _keyMaps[i];
	  if (map->controllerID == controllerID)
	    if (map->keyMap.count(button))

	      dynamic_cast<PlayerManager *>(_entitiesManager->players[map->playerID - 1])->apply_input_stick(
		      map->keyMap.at(button));

	}
    }
}

// -----------------------------------------------------------------------------
void game::InputLinker::sendStickAxisEvent(int controllerID, AMovableEntity::e_action dir)
{
  KeyMap *map;

  if (_playing)
    {
      for (unsigned int i = 0; i < _keyMaps.size(); ++i)
	{
	  map = _keyMaps[i];
	  if (map->controllerID == controllerID)
	    dynamic_cast<PlayerManager *>(_entitiesManager->players[map->playerID - 1])->apply_input_stick(dir);
	}
    }
}

// -----------------------------------------------------------------------------
void game::InputLinker::setPlaying(bool playing)
{
  _playing = playing;
}

// -----------------------------------------------------------------------------
void game::InputLinker::setEntitiesManager(EntitiesManager *entitiesManager)
{
  _entitiesManager = entitiesManager;
}
