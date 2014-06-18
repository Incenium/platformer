#include "SoundEffect.hpp"

SoundEffect::SoundEffect()
{
    m_soundEffect = nullptr;
}

SoundEffect::~SoundEffect()
{
    Mix_FreeChunk(m_soundEffect);
    m_soundEffect = nullptr;
}

bool SoundEffect::loadFromFile(std::string path)
{
    bool success = true;

    m_soundEffect = Mix_LoadWAV(path.c_str());
    if (m_soundEffect == nullptr){
        DEBUG_LOG << "Unable to load sound effect " << path << "! SDL_mixer error: " << Mix_GetError() << std::endl << std::endl;
    
        success = false;
    }

    return success;
}

void SoundEffect::play(int numRepeats)
{
    Mix_PlayChannel(-1, m_soundEffect, numRepeats);
}