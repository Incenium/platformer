/*
===============================================================================
* File: Animation.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Contains sequences of images to be displayed one after the other
===============================================================================
*/

// For atoi
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

#include "SDL2/SDL.h"

#include "Spritesheet.hpp"
#include "Timer.hpp"
#include "ResourceManager.hpp"

#include "strutil.hpp"

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

extern std::ofstream DEBUG_LOG;
extern class ResourceManager resManager;

class Animation {
  public:
    Animation();
    ~Animation();

    bool loadFromFile(std::string path);
    void run();
    void render(int x, int y, SDL_Renderer* renderer);
    void reset();

  private:
    Timer m_timer;

    Spritesheet* m_spritesheet;
    std::vector<SDL_Rect*> m_frames;

    int m_currentFrame;

    // time is in milliseconds
    int m_updateTime;
    Uint32 m_timeSinceLast;
};

#endif