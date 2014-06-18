#include "Texture.hpp"

Texture::Texture()
{
    m_texture = nullptr;

    m_width = 0;
    m_height = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    free();

    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL){
        DEBUG_LOG << "Unable to load image " << path << "! SDL_image error: "<< IMG_GetError() << std::endl << std::endl;
    }

    else {
        // This sets color key, just comment the line if we don't need it
        SDL_SetColorKey(loadedSurface, SDL_TRUE,
                        SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (newTexture == nullptr){
            DEBUG_LOG << "Unable to create texture from " << path << "! SDL error: " << SDL_GetError() << std::endl << std::endl;
        }

        else {
            m_width = loadedSurface->w;
            m_height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    m_texture = newTexture;

    return m_texture != nullptr;
}

void Texture::free()
{
    if (m_texture != nullptr){
        SDL_DestroyTexture(m_texture);

        m_width = 0;
        m_height = 0;
    }
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, m_width, m_height};

    if (clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, m_texture, clip, &renderQuad);
}

int Texture::getWidth()
{
    return m_width;
}

int Texture::getHeight()
{
    return m_height;
}