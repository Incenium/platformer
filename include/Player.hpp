/*
===============================================================================
* File: Player.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: The player
===============================================================================
*/

#include <fstream>

#include "SDL2/SDL.h"

#include "Animation.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

extern class ResourceManager resManager;
extern std::ofstream DEBUG_LOG;

class Player {
  public:
    Player();
    Player(float x, float y);
    ~Player();

    bool init(float x, float y);

    void handleInput(SDL_Event e);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);

  private:
    float m_x, m_y;
    float m_velocity;

    enum Animations {
        PLAYER_RUNNING_RIGHT,
        PLAYER_RUNNING_LEFT,
		//PLAYER_JUMPING,
		//PLAYER_FALLING
        //MARIO_JUMPING_RIGHT,
        //MARIO_JUMPING_LEFT
    };

    int m_currentAnimation;

    Animation* m_animations[2];
};

#endif