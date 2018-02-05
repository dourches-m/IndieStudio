//
// SoundManager.cpp for IndieStudio in /home/kiyonari/rendu/IndieStudio
//
// Made by Rémi Sezille
// Login   <remi.sezille@epitech.eu>
//
// Started on  dim. 18 06 2017 11:48:56  by Rémi Sezille
// Last update dim. 18 06 2017 11:48:56  by Rémi Sezille
//

#include "SoundManager.hpp"

game::SoundManager::SoundManager() {
    _engine = irrklang::createIrrKlangDevice();
}

game::SoundManager::~SoundManager() {
    _engine->drop();
}

void game::SoundManager::playSound(std::string const &filename) {
    _engine->play2D(filename.c_str())->drop();
}

irrklang::ISound* game::SoundManager::playLoop(std::string const &filename) {
    return _engine->play2D(filename.c_str(), true);
}

void game::SoundManager::stopLoop(irrklang::ISound &sound) {
    sound.drop();
}

void game::SoundManager::pauseLoop(irrklang::ISound &sound) {
    sound.setIsPaused(true);
}

void game::SoundManager::resumeLoop(irrklang::ISound &sound) {
    sound.setIsPaused(false);
}

irrklang::ik_f32 game::SoundManager::getVolume() {
    return _engine->getSoundVolume();
}

void game::SoundManager::setVolume(irrklang::ik_f32 volume) {
    _engine->setSoundVolume(volume);
}