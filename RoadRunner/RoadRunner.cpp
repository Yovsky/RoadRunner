#include "RoadRunner.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

using namespace std;

struct SDL_State
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int h, w, logH, logW;
};

bool Init(SDL_State &state);

void CleanUp(SDL_State &window);

int main(int argc, char *argv[])
{
	SDL_State state;
	state.h = 720;
	state.w = 1280;
	state.logH = 360;
	state.logW = 640;

	if (!Init(state))
	{
		return -1;
	}

	// Load player car texture
	SDL_Texture* playerCar = IMG_LoadTexture(state.renderer, "assets/textures/cars/Compact/compact_blue.png");
	SDL_SetTextureScaleMode(playerCar, SDL_SCALEMODE_NEAREST);

	SDL_Event event;

	const bool* keyState = SDL_GetKeyboardState(nullptr);

	// Start game loop
	bool isRunning = true;
	while (isRunning)
	{
		// Handle exit
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
				{
					isRunning = false;
					break;
				}
			}

			if (keyState[SDL_SCANCODE_ESCAPE] == true)
			{
				isRunning = false;
				break;
			}
		}

		SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
		SDL_RenderClear(state.renderer);

		SDL_FRect dst{
			.x = 0,
			.y = 0,
			.w = 26,
			.h = 58
		};

		SDL_RenderTexture(state.renderer, playerCar, nullptr, &dst);

		SDL_RenderPresent(state.renderer);
	}

	// Clean up
	SDL_DestroyTexture(playerCar);
	CleanUp(state);
	return 0;
}

bool Init(SDL_State &state)
{
	bool success = true;

	// Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
		success = false;
	}

	// Create window
	state.window = SDL_CreateWindow("RoadRunner", state.w, state.h, SDL_WINDOW_RESIZABLE);
	if (!state.window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating game window", nullptr);
		success = false;
	}

	// Create renderer
	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr);
		success = false;
	}

	// Handle window resize
	SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	
	return success;
}

void CleanUp(SDL_State &state)
{
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
