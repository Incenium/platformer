#ifdef _WIN32
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>
#include "Animation.hpp"
#include "Music.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "SoundEffect.hpp"
#include "Spritesheet.hpp"
#include "strutil.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

SDL_Renderer* renderer;
SDL_Window* window;
const int screenWidth = 1280, screenHeight = 720;
SDL_Rect cameraRect;

ResourceManager resManager;
std::ofstream DEBUG_LOG;

bool Init();
void Update(float deltaTime);

Texture background;
//Player currentPlayer(screenHeight, screenWidth / 2);

Spritesheet* playerSpritesheet = nullptr;
SDL_Rect* sprite;

Animation* playerAnimation = nullptr;

int main(int argc, char* args[]) {
	DEBUG_LOG.open("debug.log");

	if (!Init()) {
		DEBUG_LOG << "Failed to initiate program";
	}
	
	else {
		cameraRect.x = 0;
		cameraRect.y = 0;
		cameraRect.w = screenWidth;
		cameraRect.h = screenHeight;
		background.loadFromFile("res/spritesheets/Kenny's Stuff (temp storage)/Mushroom pack (50 assets)/Backgrounds/bg_grasslands.png", renderer);

		if (false) { //for a loading function/routine
			DEBUG_LOG << "Failed to load program files";
		}

		else {
			bool quit = false;
			SDL_Event e;

			Uint32 lastTime, currentTime = SDL_GetTicks(); //set up deltaTime
			float deltaTime;

			playerSpritesheet = resManager.getSpritesheet("res/spritesheets/player.spritesheet");

			sprite = playerSpritesheet->getSprite("player_walk02");

			playerAnimation = resManager.getAnimation("res/animations/player_running.animation");

			while (!quit) {
				while(SDL_PollEvent(&e) != 0) {
					//currentPlayer.handleInput(e);
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

	cameraRect.x = -x + screenWidth;

	SDL_Rect bgRect = {0, 0, screenWidth * 2, screenHeight};
	background.render(0, 0, renderer, &bgRect);

	playerSpritesheet->render(sprite, 500, 500, renderer);

	playerAnimation->run();

	playerAnimation->render(600, 500, renderer);

	// currentPlayer.update(deltaTime);
	// currentPlayer.render(renderer);

	SDL_RenderPresent(renderer);
}

bool Init() {
	bool sucess = true;

	if (SDL_INIT_VIDEO < 0) {
		DEBUG_LOG << "Error: Failed to initiate SDL Video Subsystem. SDL_Error: " << SDL_GetError() << std::endl;
		sucess = false;
	}
	
	else {
		window = SDL_CreateWindow("The Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, NULL);
		if (window == NULL) {
			DEBUG_LOG << "Error: Failed to create window. SDL Error: " << SDL_GetError() << std::endl;
			sucess = false;
		}
		
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				DEBUG_LOG << "Error: Failed to create renderer. SDL Error: " << SDL_GetError() << std::endl;
				sucess = false;
			}
			
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					DEBUG_LOG << "Error: Failed to initiate Image Subsystem. SDL_IMG Error: " << IMG_GetError() << std::endl;
					sucess = false;
				}
				
				else {
					/*int mixFlags = MIX_INIT_MP3;
					if (!(Mix_Init(mixFlags) & mixFlags)) {
						DEBUG_LOG << "Error: Failed to initiate Mixer Subsystem. SDL_MIX Error: " << Mix_GetError() << std::endl;
						sucess = false;
					}*/

					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
					    printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());

					    sucess = false;
					}
					
					else {
						if (TTF_Init() == -1) {
							DEBUG_LOG << "Error: Failed to initiate Font Subsystem. SDL_TTF Error: " << TTF_GetError() << std::endl;
							sucess = false;
						}
						
						else {
							SDL_Surface* icon = IMG_Load(/*Icon location for the window*/"");
							SDL_SetWindowIcon(window, icon);
						}
					}
				}
			}
		}
	}

	if (!resManager.loadResources("res/resources.res", renderer)){
		DEBUG_LOG << "Could not load resources from resource file\n" << std::endl;

		sucess = false;
	}

	return sucess;
}