#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "application\application.h"
#include "globals.h"
#include "util/file.h"
#include <sstream>
#include "graphics/font.h"

class P
{
public:
	int c;
	P(int c) : c(c) {}
};

static void playground()
{
	std::unique_ptr<P> p = std::make_unique<P>(5);
	std::cout << p->c;
}


int main(int argc, char** argv)
{
	playground();
	
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
			Application app;
			app.run();
		}
		else
		{
			ERR("SDL failed to initialize!");
		}
		IMG_Quit();
		SDL_Quit();
	}
	MSG("Press enter to exit program...");
	std::cin.get();
	return 0;
}