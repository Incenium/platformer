/*
===============================================================================
* File: Timer.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Timer class
===============================================================================
*/

#include "SDL2/SDL.h"

#ifndef TIMER_HPP
#define TIMER_HPP

//extern std::ofstream DEBUG_LOG;

class Timer {
  public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks();

    bool isStarted();
    bool isPaused();

  private:
    Uint32 m_startTicks;
    Uint32 m_pausedTicks;

    bool m_paused;
    bool m_started;
};

#endif