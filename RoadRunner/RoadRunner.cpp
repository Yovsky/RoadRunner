#include "RoadRunner.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

using namespace std;

void CleanUp(SDL_Window* window);

int main(int argc, char *argv[])
{
	// Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
		return 1;
	}

	// Create window
	int h = 540;
	int w = 960;
	SDL_Window* window = SDL_CreateWindow("RoadRunner", w, h, SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating game window", nullptr);
	}

	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr);
	}

	// Handle window resize
	SDL_SetRenderLogicalPresentation(renderer, w, h, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_Event event;

	const bool* keyState = SDL_GetKeyboardState(nullptr);

	// Start game loop
	bool isRunning = true;
	while (isRunning)
	{
		// Handle exit
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				isRunning = false;
				break;
			}
			else if (keyState[SDL_SCANCODE_ESCAPE] == true)
			{
				isRunning = false;
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}

	CleanUp(window);
	return 0;
}

void CleanUp(SDL_Window* window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
