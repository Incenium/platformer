#include "Music.hpp"

Music::Music()
{
    m_music = nullptr;
}

Music::~Music()
{
    Mix_FreeMusic(m_music);

    m_music = nullptr;
}

bool Music::loadFromFile(std::string path)
{
    bool success = true;

    m_music = Mix_LoadMUS(path.c_str());
    if (m_music == nullptr){
        DEBUG_LOG << "Unable to load music " << path << "! SDL_mixer error: " << Mix_GetError() << std::endl << std::endl;

        success = false;
    }

    return success;
}

// Might want to add a feature to add if we want repeat or not
void Music::play()
{
    if (Mix_PlayingMusic() == 0){
        Mix_PlayMusic(m_music, -1);
    }

    else {
        if (Mix_PausedMusic() == 1){
            Mix_ResumeMusic();
        }

        else {
            Mix_PauseMusic();
        }
    }
}

void Music::stop()
{
    Mix_HaltMusic();
}