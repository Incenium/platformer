/*
===============================================================================
* File: Music.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Mix_Music wrapper
===============================================================================
*/

#include <fstream>
#include <string>

#include "SDL2/SDL_mixer.h"

#ifndef MUSIC_HPP
#define MUSIC_HPP

extern std::ofstream DEBUG_LOG;

class Music {
  public:
    Music();
    ~Music();

    bool loadFromFile(std::string path);

    void play();
    //void pause();
    //void resume();
    void stop();

    // Add stuff like fade out
  private:
    Mix_Music* m_music;
};

#endif