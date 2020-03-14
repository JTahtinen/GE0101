#include <SDL2\SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "application\application.h"
#include "globals.h"
#include "math/math.h"
#include "external/triangulate.h"
#include "application/factory.h"


static void playground()
{
	String* string = Factory::createString("Hello, World!");
	string->print();
}

static void run()
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

int main(int argc, char** argv)
{
	Factory::init();
	playground();
	run();
	MSG("\nTotal Heap allocations during runtime: " << g_heapTracker.getTotalAllocationsInMegaBytes() << " MB");
	MSG("Total Heap allocations freed during runtime: " << g_heapTracker.getFreedAllocationsInMegaBytes() << " MB");
	MSG("Current heap allocations: " << g_heapTracker.getCurrentAllocationsInMegaBytes() << " MB\n");
	MSG("Press enter to exit program...");
	std::cin.get();
	return 0;
}

/*
static std::vector<unsigned int> s_indices;
static unsigned int finishedTriangles;

static bool angleIsEqualToOrGreaterThan180(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	Vec2 p01 = (p1 - p0).setToAbs();
	Vec2 p12 = (p2 - p1).setToAbs();


	float tanp01angle = 0;
	float tanp12angle = 0;

	if (p01.y > p1.y)
	{
		tanp01angle = p01.y / p01.x + 2.0f;
	}
	else
	{
		tanp01angle = p01.x / p01.y;
	}

	if (p2.y > p1.y)
	{
		tanp12angle = p12.y / p12.x + 2.0f;
	}
	else
	{
		tanp12angle = p12.x / p12.y;
	}

	return (8.0f - (tanp01angle + tanp12angle) >= 4.0f);
}

static void playground()
{
	while (true)
	{
		Vec2 points[3];
		for (unsigned int i = 0; i < 3; ++i)
		{
			std::cout << "X for point " << i << ": ";
			std::cin >> points[i].x;
			std::cout << "Y for point " << i << ": ";
			std::cin >> points[i].y;
		}
		bool a = angleIsEqualToOrGreaterThan180(points[0], points[1], points[2]);
		if (a)
		{
			MSG("Angle was equal to or greater than 180 degrees\n");
		}
		else
		{
			MSG("Angle was less that 180 degrees\n");
		}

	}


	s_indices.reserve(18);
	finishedTriangles = 0;
	auto makeTriangle = [](unsigned int p0, unsigned int p1, unsigned int p2)
	{
		s_indices[finishedTriangles + 0] = p0;
		s_indices[finishedTriangles + 1] = p1;
		s_indices[finishedTriangles + 2] = p2;
		++finishedTriangles;
	};

	auto getThirdPoint = [](const unsigned int first, const unsigned int second)
	{

		return 0;
	};

	Vec2 points[8] = { {0.0f, 1.0f}, {0.3f, 0.5f}, {0.4f, 0.6f}, {0.5f, 0.1f}, {1.0f, 0.9f}, {0.75f, 0.8f}, {0.9f, 1.3f}, {0.5f, 1.8f} };
	makeTriangle(0, 1, 2);
	unsigned int pointsHandled = 3;

	unsigned int lastHandledPoint = 2;
	unsigned int currentPoint = 3;
	while (pointsHandled < 8)
	{
		makeTriangle(lastHandledPoint, currentPoint, getThirdPoint(lastHandledPoint, currentPoint));
	}


}*/