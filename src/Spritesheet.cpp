#include "Spritesheet.hpp"

Spritesheet::Spritesheet()
{
    
}

Spritesheet::~Spritesheet()
{
    m_spritesheet.free();

    m_sprites.clear();
}

bool Spritesheet::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    bool success = true;

    std::ifstream file;

    std::string line;

    int linenum = 1;

    file.open(path);
    if (!file.is_open()){
        DEBUG_LOG << "Unable to open spritesheet file " << path << std::endl << std::endl;

        success = false;
    }

    else {
        // Read in spritesheet file
        while (std::getline(file, line)){
            if (line == ""){
                linenum++;
                
                continue;
            }

            // Load spritesheet texture from spritesheet image path
            if (linenum == 1){
                if (!m_spritesheet.loadFromFile(line, renderer)){
                    DEBUG_LOG << "Unable to load texture " << line << std::endl << std::endl;

                    success = false;
                    break;
                }
            }

            // Get the sprite's x, y, width and height
            else {
                std::vector<std::string> temp = stringSplit(line, ", ");

                if (temp.size() != 5){
                    DEBUG_LOG << "Data at line " << linenum << " is malformatted" << std::endl << std::endl;

                    success = false;
                    break;
                }

                SDL_Rect sprite = {atoi(temp[1].c_str()),
                                   atoi(temp[2].c_str()),
                                   atoi(temp[3].c_str()),
                                   atoi(temp[4].c_str())};

                m_sprites[temp[0]] = sprite;
            }

            linenum++;
        }
    }

    return success;
}

void Spritesheet::render(SDL_Rect* sprite, int x, int y,
                         SDL_Renderer* renderer)
{
    m_spritesheet.render(x, y, renderer, sprite);
}

SDL_Rect* Spritesheet::getSprite(std::string spriteName)
{
    std::map<std::string, SDL_Rect>::iterator it = m_sprites.find(spriteName);

    if (it == m_sprites.end()){
        // Change debug message to Sprite (sprite) is not in spritesheet
        DEBUG_LOG << "Unable to find sprite " << spriteName << std::endl << std::endl;

        return nullptr;
    }

    else {
        return &it->second;
    }
}