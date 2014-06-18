/*
===============================================================================
* File: Texture.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: SDL_Texture wrapper
===============================================================================
*/

#include <stdio.h>
#include <fstream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// For writing to debug.log
extern std::ofstream DEBUG_LOG;

class Texture {
  public:
    Texture();
    ~Texture();

    bool loadFromFile(std::string path, SDL_Renderer* renderer);

    void free();

    void render(int x, int y, SDL_Renderer* renderer,
                SDL_Rect* clip = nullptr);

    //SDL_Texture* getTexture();
    int getWidth();
    int getHeight();

  private:
    SDL_Texture* m_texture;

    int m_width;
    int m_height;
};

#endif