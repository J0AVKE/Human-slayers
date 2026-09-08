//#include <SDL_events.h>
//#include <SDL_init.h>
//#include <SDL_log.h>
//#include <SDL_video.h>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
int main(int argc, char* argv[])
{
	SDL_Window *window; // Declare a pointer
	bool done = false;

	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL3

	// Create an application window with the following settings
	window = SDL_CreateWindow(
			"An SDL3 window", 
			640, 
			480, 
			SDL_WINDOW_OPENGL
			);

	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return -1;
	}
	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_EVENT_QUIT)
			{
				done = true;
			}
		}
		// Do game logic, present a frame, etc.
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
