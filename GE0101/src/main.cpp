#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "application\application.h"
#include "globals.h"

int main(int argc, char** argv)
{
	gameLog.message("Message looks like this");
	gameLog.warning("Warning looks like this");
	gameLog.error("Error looks like this");
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		MSG("SDL initialized succesfully!");
		Application app;
		app.run();
	}
	else
	{
		MSG("SDL failed to initialize!");
	}
	IMG_Quit();
	SDL_Quit();
	MSG("Press enter to exit program...");
	std::cin.get();
	return 0;
}