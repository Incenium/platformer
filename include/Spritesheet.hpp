/*
===============================================================================
* File: SpriteSheet.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Collection of sprites in one texture
===============================================================================
*/

// For atoi
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "SDL2/SDL.h"

#include "Texture.hpp"
#include "strutil.hpp"

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

// For writing to debug.log
extern std::ofstream DEBUG_LOG;

class Spritesheet {
  public:
    Spritesheet();
    ~Spritesheet();

    // Loads a *.spritesheet file containing info about the spritesheet
    bool loadFromFile(std::string path, SDL_Renderer* renderer);

    void render(SDL_Rect* sprite, int x, int y, SDL_Renderer* renderer);

    SDL_Rect* getSprite(std::string spriteName);

  private:
    // The spritesheet texture
    Texture m_spritesheet;

    // map of sprites (aka SDL_Rects)
    std::map<std::string, SDL_Rect> m_sprites;
};

#endif