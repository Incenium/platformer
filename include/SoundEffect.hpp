/*
===============================================================================
* File: SoundEffect.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Mix_chunk wrapper
===============================================================================
*/

#include <fstream>
#include <string>

#include "SDL2/SDL_mixer.h"

#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

extern std::ofstream DEBUG_LOG;

class SoundEffect {
  public:
    SoundEffect();
    ~SoundEffect();

    bool loadFromFile(std::string path);

    void play(int numRepeats);

  private:
    Mix_Chunk* m_soundEffect;
};

#endif