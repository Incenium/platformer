#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <iostream>
#include "include\Animation.hpp"
#include "include\Music.hpp"
#include "include\ResourceManager.hpp"
#include "include\SoundEffect.hpp"
#include "include\Spritesheet.hpp"
#include "include\strutil.hpp"
#include "include\Texture.hpp"
#include "include\Timer.hpp"

SDL_Renderer* renderer;
SDL_Window* window;
const int screenWidth = 1280, screenHeight = 720;

ResourceManager resManager;
std::ofstream DEBUG_LOG;

bool Init();
void Update(float deltaTime);

int main(int argc, char* args[]) {
	if (!Init()) {
		printf("Failed to initiate program");
	} else {
		if (false) { //for a loading function/routine
			printf("Failed to load program files");
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

	SDL_RenderPresent(renderer);
}

bool Init() {
	bool sucess = true;

	if (SDL_INIT_VIDEO < 0) {
		printf("Error: Failed to initiate SDL Video Subsystem. SDL_Error: %s\n", SDL_GetError());
		sucess = false;
	} else {
		window = SDL_CreateWindow("The Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, NULL);
		if (window == NULL) {
			printf("Error: Failed to create window. SDL Error: %s\n", SDL_GetError());
			sucess = false;
		} else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				printf("Error: Failed to create renderer. SDL Error: %s\n", SDL_GetError());
				sucess = false;
			} else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("Error: Failed to initiate Image Subsystem. SDL_IMG Error: %s\n", IMG_GetError());
					sucess = false;
				} else {
					int mixFlags = MIX_INIT_MP3;
					if (!(Mix_Init(mixFlags) & mixFlags)) {
						printf("Error: Failed to initiate Mixer Subsystem. SDL_MIX Error: %s", Mix_GetError());
						sucess = false;
					} else {
						if (TTF_Init() == -1) {
							printf("Error: Failed to initiate Font Subsystem. SDL_TTF Error: %s\n", TTF_GetError());
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