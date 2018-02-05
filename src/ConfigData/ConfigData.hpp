//
// ConfigData.hpp for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Wed Jun 14 13:25:39 2017 Hugo Baldassin
// Last update Wed Jun 14 13:25:41 2017 Hugo Baldassin
//

#ifndef 	INDIE_STUDIO_ConfigData_HPP
# define 	INDIE_STUDIO_ConfigData_HPP

# include	<string>
# include	<OGRE/Ogre.h>
# include	<OGRE/OgreConfigFile.h>

namespace game
{
  class ConfigData
  {
  public:
    ConfigData();
    ~ConfigData();

    void initData();

    static ConfigData &getInstance();

    int getValueAsInt(std::string key);
    Ogre::Real getValueAsReal(std::string key);
    std::string getValueAsString(std::string key);
    Ogre::Vector3 getValueAsVector3(std::string key);
    bool getValueAsBool(std::string key);
    Ogre::ColourValue getValueAsColourValue(std::string key);
    bool getKeyExists(std::string key);

  private:
    Ogre::ConfigFile _configFile;
    std::map<std::string, std::string> _configs;
  };
}
#endif 		//INDIE_STUDIO_ConfigData_HPP
