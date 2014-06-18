#include "Animation.hpp"

Animation::Animation()
{
    m_spritesheet = nullptr;

    m_currentFrame = 0;

    m_updateTime = 0;
    m_timeSinceLast = 0;
}

Animation::~Animation()
{

}

bool Animation::loadFromFile(std::string path)
{
    bool success = true;

    int linenum = 1;
    std::string line;

    std::ifstream file;
    file.open(path);

    if (!file.is_open()){
        DEBUG_LOG << "Unable to open animation file " << path << std::endl << std::endl;

        success = false;
    }

    else {
        while (std::getline(file, line)){
            if (line == ""){
                linenum++;

                continue;
            }

            if (linenum == 1){
                // get spritesheet from resource manager
                if ((m_spritesheet = resManager.getSpritesheet(line)) == 
                    nullptr){

                    DEBUG_LOG << "Animation: Unable to get spritesheet " << line << " from the resource manager" << std::endl << std::endl;

                    success = false;

                    break;
                }
            }

            else {
                    std::vector<std::string> temp = stringSplit(line);

                    // temp.size() - 1 because the last element is the update time for the animation and not a frame
                    for (int i = 0; i < temp.size() - 1; i++){
                        SDL_Rect* sprite = m_spritesheet->getSprite(temp[i]);

                        if (sprite == nullptr){
                            DEBUG_LOG << "Animation: Unable to get sprite " << temp[i] << " from line " << linenum << " in animation file " << path << std::endl << std::endl;

                            success = false;

                            break;
                        }

                        else
                            m_frames.push_back(sprite);
                    }

                    //TODO: Add error handling for if the last element is not an int
                    m_updateTime = atoi(temp[temp.size() - 1].c_str());

                    if (m_updateTime == 0){
                        DEBUG_LOG << "Animation: invalid update time " << temp[temp.size() - 1] << std::endl << std::endl;

                        success = false;

                        break;
                    }
                }

            linenum++;
        }
    }

    return success;
}

void Animation::run()
{
    if (!m_timer.isStarted()){
        m_timer.start();

        m_currentFrame++;

        m_timeSinceLast = m_timer.getTicks();
    }

    else {
        Uint32 timePassed = m_timer.getTicks() - m_timeSinceLast;

        if (timePassed >= (Uint32)m_updateTime){
            m_currentFrame++;

            if (m_currentFrame > m_frames.size() - 1)
                m_currentFrame = 1;

            m_timeSinceLast = m_timer.getTicks();
        }

        else
            return;
    }
}

void Animation::render(int x, int y, SDL_Renderer* renderer)
{
    m_spritesheet->render(m_frames[m_currentFrame], x, y, renderer);
}

void Animation::reset()
{
    m_currentFrame = 0;
}