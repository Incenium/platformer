#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
    // Deallocate the spritesheets in m_spritesheets
    std::vector<std::pair<std::string, Spritesheet*>> ss(
                                                         m_spritesheets.begin(),
                                                         m_spritesheets.end());
    for (int i = 0; i < ss.size(); i++)
        delete ss[i].second;

    ss.clear();

    // Deallocate the animations in m_animations
    std::vector<std::pair<std::string, Animation*>> a(m_animations.begin(),
                                                      m_animations.end());

    for (int i = 0; i < a.size(); i++)
        delete a[i].second;

    a.clear();
}

bool ResourceManager::loadResources(std::string path, SDL_Renderer* renderer)
{
    bool success = true;

    std::string line;

    std::ifstream file;
    file.open(path);

    if (!file.is_open()){
        DEBUG_LOG << "ResourceManager loadResources(): Unable to open resource file " << path << '\n' << std::endl;

        success = false;
    }

    else {
        while (std::getline(file, line)){
            std::vector<std::string> temp = stringSplit(line);

            if (temp.size() != 2){
                DEBUG_LOG << "ResourceManager loadResources(): Malformed line in resource file " << path << '\n' << std::endl;

                success = false;

                break;
            }

            else {
                std::string resType = temp[0];
                std::string name = temp[1];

                if (resType == "spritesheet"){
                    Spritesheet* s = new Spritesheet;

                    if (!s->loadFromFile(name, renderer)){
                        DEBUG_LOG << "ResourceManager loadResources(): Unable to load spritesheet " << name << '\n' << std::endl;

                        success = false;

                        break;
                    }

                    else
                        m_spritesheets[name] = s;
                }

                else if (resType == "animation"){
                    Animation* a = new Animation;

                    if (!a->loadFromFile(name)){
                        DEBUG_LOG << "Resource Manager: Unable to load animation " << name << '\n' << std::endl;

                        success = false;

                        break;
                    }

                    else
                        m_animations[name] = a;
                }

                else if (resType == "music"){
                    Music* m = new Music;

                    if (!m->loadFromFile(name)){
                        DEBUG_LOG << "ResourceManager loadResources(): Unable to load music " << name << '\n' << std::endl;

                        success = false;

                        break;
                    }

                    else
                        m_music[name] = m;
                }

                else if (resType == "soundeffect"){
                    SoundEffect* se = new SoundEffect;

                    if (!se->loadFromFile(name)){
                        DEBUG_LOG << "ResourceManager loadResources(): Unable to load sound effect " << name << '\n' << std::endl;

                        success = false;
                    }

                    else
                        m_soundeffects[name] = se;
                }
            }
        }
    }

    return success;
}

Spritesheet* ResourceManager::getSpritesheet(std::string spritesheet)
{
    std::map<std::string, Spritesheet*>::iterator it = m_spritesheets.find(spritesheet);

    if (it == m_spritesheets.end()){
        DEBUG_LOG << "ResourceManager getSpritesheet(): Unable to find spritesheet " << spritesheet << '\n' << std::endl;

        return nullptr;
    }

    else
        return it->second;
}

Animation* ResourceManager::getAnimation(std::string animation)
{
    std::map<std::string, Animation*>::iterator it = m_animations.find(animation);

    if (it == m_animations.end()){
        DEBUG_LOG << "ResourceManager getAnimation(): Unable to find animation " << animation << '\n' << std::endl;

        return nullptr;
    }

    else
        return it->second;
}

Music* ResourceManager::getMusic(std::string music)
{
    std::map<std::string, Music*>::iterator it = m_music.find(music);

    if (it == m_music.end()){
        DEBUG_LOG << "ResourceManager getMusic(): Unable to find music " << music << '\n' << std::endl;

        return nullptr;
    }

    else
        return it->second;
}

SoundEffect* ResourceManager::getSoundEffect(std::string soundEffect)
{
    std::map<std::string, SoundEffect*>::iterator it = m_soundeffects.find(soundEffect);

    if (it == m_soundeffects.end()){
        DEBUG_LOG << "ResourceManager getSoundEffect(): Unable to find sound effect " << soundEffect << '\n' << std::endl;

        return nullptr;
    }

    else
        return it->second;
}