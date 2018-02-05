//
// ConfigData.cpp for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Wed Jun 14 13:25:07 2017 Hugo Baldassin
// Last update Wed Jun 14 17:26:27 2017 Hugo Willaume
//

#include "ConfigData.hpp"
#include <OGRE/OgreResourceGroupManager.h>
#include <OGRE/OgreStringConverter.h>

game::ConfigData::ConfigData()
{
  _configFile.load("BomberConfig.txt", "=", true);

  Ogre::ConfigFile::SectionIterator seci = _configFile.getSectionIterator();
  Ogre::String sectionName;
  Ogre::String keyName;
  Ogre::String valueName;

  while (seci.hasMoreElements())
  {
    sectionName = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i)
    {
      keyName = i->first;
      valueName = i->second;
      if (keyName.size() && valueName.size())
	_configs.insert(std::pair<std::string, std::string>(sectionName + "/" + keyName, valueName));
    }
  }
}

game::ConfigData::~ConfigData()
{
}

void game::ConfigData::initData()
{
  _configs.clear();
  _configFile.clear();
  _configFile.load("BomberConfig.txt", "=", true);
  Ogre::ConfigFile::SectionIterator seci = _configFile.getSectionIterator();
  Ogre::String sectionName;
  Ogre::String keyName;
  Ogre::String valueName;

  while (seci.hasMoreElements())
  {
    sectionName = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i)
    {
      keyName = i->first;
      valueName = i->second;
      if (keyName.size() && valueName.size())
	_configs.insert(std::pair<std::string, std::string>(sectionName + "/" + keyName, valueName));
    }
  }
}

game::ConfigData& game::ConfigData::getInstance()
{
  static ConfigData Instance;
  return Instance;
}

bool game::ConfigData::getKeyExists(std::string key)
{
  if (_configs.count(key) > 0)
    return true;
  return false;
}

std::string game::ConfigData::getValueAsString(std::string key)
{
  if (getKeyExists(key) == true)
    return _configs[key];
  else
    throw Ogre::Exception(Ogre::Exception::ERR_ITEM_NOT_FOUND,"Configuration key: " + key + " not found", "ConfigData::getValue");
}

int game::ConfigData::getValueAsInt(std::string key)
{
  return atoi(getValueAsString(key).c_str());
}

Ogre::Real game::ConfigData::getValueAsReal(std::string key)
{
  return Ogre::StringConverter::parseReal(getValueAsString(key));
}

bool game::ConfigData::getValueAsBool(std::string key)
{
  return Ogre::StringConverter::parseBool(getValueAsString(key));
}

Ogre::Vector3 game::ConfigData::getValueAsVector3(std::string key)
{
  return Ogre::StringConverter::parseVector3(getValueAsString(key));
}

Ogre::ColourValue game::ConfigData::getValueAsColourValue(std::string key)
{
  return Ogre::StringConverter::parseColourValue(getValueAsString(key));
}