/*
===============================================================================
* File: ResourceManager.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Manages the resources for the game
===============================================================================
*/

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "strutil.hpp"

#include "Spritesheet.hpp"
#include "Animation.hpp"
#include "Music.hpp"
#include "SoundEffect.hpp"

extern std::ofstream DEBUG_LOG;

class ResourceManager {
  public:
    ResourceManager();
    ~ResourceManager();

    bool loadResources(std::string path, SDL_Renderer* renderer);

    Spritesheet* getSpritesheet(std::string spritesheet);
    Animation*   getAnimation(std::string animation);
    Music*       getMusic(std::string music);
    SoundEffect* getSoundEffect(std::string soundEffect);

  private:
    std::map<std::string, Spritesheet*> m_spritesheets;
    std::map<std::string, Animation*> m_animations;
    std::map<std::string, Music*> m_music;
    std::map<std::string, SoundEffect*> m_soundeffects;
};

#endif