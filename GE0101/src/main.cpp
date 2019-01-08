#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2/SDL_image.h>
#include "application\application.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		std::cout << "SDL initialized succesfully!" << std::endl;
		Application app;
		app.run();
	}
	else
	{
		std::cout << "SDL failed to initialize!" << std::endl;
	}
	IMG_Quit();
	SDL_Quit();
	std::cout << "Press enter to exit program..." << std::endl;
	std::cin.get();
	return 0;
}