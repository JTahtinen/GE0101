#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "application\application.h"
#include "globals.h"
#include "util/file.h"
#include <sstream>
#include "graphics/font.h"

static void playground()
{
	char a = 'a';
	int aVal = (int)a;
	char aa = aVal;
	MSG("ASCII value of " << aa << " equals " << aVal);
}


int main(int argc, char** argv)
{
	playground();
	
	std::string text = load_text_file("res/test.txt");
	int var[2];
	std::string line;
	std::istringstream ss(text);
	int i = 0;
	while (getline(ss, line, ' '))
	{
		if (line == "variable:")
		{
			getline(ss, line);
			var[i++] = stoi(line, nullptr, 10);
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		std::cout << var[i] << std::endl;
	}
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
	MSG("Press enter to exit program...");
	std::cin.get();
	return 0;
}