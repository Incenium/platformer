#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <iostream>
#include "Animation.hpp"
#include "Music.hpp"
#include "ResourceManager.hpp"
#include "SoundEffect.hpp"
#include "Spritesheet.hpp"
#include "strutil.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

SDL_Renderer* renderer;
SDL_Window* window;
const int screenWidth = 1280, screenHeight = 720;
int renderPosX, renderPosY;

ResourceManager resManager;
std::ofstream DEBUG_LOG;

bool Init();
void Update(float deltaTime);

Texture background;

int main(int argc, char* args[]) {
	if (!Init()) {
		DEBUG_LOG << "Failed to initiate program";
	} else {

		renderPosX = 0;
		renderPosY = 0;
		background.loadFromFile("res/spritesheets/Kenny's Stuff (temp storage)/Mushroom pack (50 assets)/Backgrounds/bg_grasslands.png", renderer);

		if (false) { //for a loading function/routine
			DEBUG_LOG << "Failed to load program files";
		} else {
			bool quit = false;
			SDL_Event e;

			Uint32 lastTime, currentTime = SDL_GetTicks(); //set up deltaTime
			float deltaTime;

			while (!quit) {
				while(SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				lastTime = currentTime;
				currentTime = SDL_GetTicks(); //calculate deltaTime
				deltaTime = (currentTime - lastTime) / 1000.0f;

				Update(deltaTime);
			}
		}
	}

	return 0;
}

void Update(float deltaTime) {
	SDL_RenderClear(renderer);

	//updates done here

	int x, y;
	SDL_GetMouseState(&x, &y);

	renderPosX = -x + screenWidth;

	SDL_Rect bgRect = {0, 0, screenWidth * 2, screenHeight};
	background.render(0, 0, renderer, &bgRect);

	SDL_RenderPresent(renderer);
}

bool Init() {
	bool sucess = true;

	if (SDL_INIT_VIDEO < 0) {
		DEBUG_LOG << "Error: Failed to initiate SDL Video Subsystem. SDL_Error: " << SDL_GetError() << std::endl;
		sucess = false;
	} else {
		window = SDL_CreateWindow("The Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, NULL);
		if (window == NULL) {
			DEBUG_LOG << "Error: Failed to create window. SDL Error: " << SDL_GetError() << std::endl;
			sucess = false;
		} else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				DEBUG_LOG << "Error: Failed to create renderer. SDL Error: " << SDL_GetError() << std::endl;
				sucess = false;
			} else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					DEBUG_LOG << "Error: Failed to initiate Image Subsystem. SDL_IMG Error: " << IMG_GetError() << std::endl;
					sucess = false;
				} else {
					int mixFlags = MIX_INIT_MP3;
					if (!(Mix_Init(mixFlags) & mixFlags)) {
						DEBUG_LOG << "Error: Failed to initiate Mixer Subsystem. SDL_MIX Error: " << Mix_GetError() << std::endl;
						sucess = false;
					} else {
						if (TTF_Init() == -1) {
							DEBUG_LOG << "Error: Failed to initiate Font Subsystem. SDL_TTF Error: " << TTF_GetError() << std::endl;
							sucess = false;
						} else {
							SDL_Surface* icon = IMG_Load(/*Icon location for the window*/"");
							SDL_SetWindowIcon(window, icon);
						}
					}
				}
			}
		}
	}

	return sucess;
}