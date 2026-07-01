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
};

void CleanUp(SDL_State &window);

int main(int argc, char *argv[])
{
	SDL_State state;

	// Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
		return 1;
	}
	
	// Create window
	int h = 540;
	int w = 960;
	state.window = SDL_CreateWindow("RoadRunner", w, h, SDL_WINDOW_RESIZABLE);
	if (!state.window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating game window", nullptr);
	}

	// Create renderer
	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr);
	}

	// Handle window resize
	SDL_SetRenderLogicalPresentation(state.renderer, w, h, SDL_LOGICAL_PRESENTATION_LETTERBOX);

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

		SDL_RenderPresent(state.renderer);
	}

	CleanUp(state);
	return 0;
}

void CleanUp(SDL_State &state)
{
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
