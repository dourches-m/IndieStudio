//
// SoundManager.hpp for indie in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed May 31 16:46:40 2017 Hugo Willaume
// Last update Wed May 31 16:46:40 2017 Hugo Willaume
//


#ifndef                INDIE_SoundManager_HPP
# define                INDIE_SoundManager_HPP

# include "irrKlang.h"
# include <string>

namespace game
{
  class SoundManager
  {
  public:
      SoundManager();
      ~SoundManager();
      void playSound(std::string const &);
      irrklang::ISound* playLoop(std::string const &);
      void stopLoop(irrklang::ISound &);
      void pauseLoop(irrklang::ISound &);
      void resumeLoop(irrklang::ISound &);
      irrklang::ik_f32 getVolume(void);
      void setVolume(irrklang::ik_f32);
  private:
      irrklang::ISoundEngine *_engine;
  };
}
#endif                //INDIE_SoundManager_HPP
