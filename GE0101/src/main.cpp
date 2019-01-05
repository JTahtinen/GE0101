#include <iostream>
#include <SDL2\SDL.h>
#include "application\application.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized succesfully!" << std::endl;
		Application app;
		app.run();
	}
	else
	{
		std::cout << "SDL failed to initialize!" << std::endl;
	}
	SDL_Quit();
	std::cout << "Press enter to exit program..." << std::endl;
	std::cin.get();
	return 0;
}