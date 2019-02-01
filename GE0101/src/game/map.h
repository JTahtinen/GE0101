#pragma once

class Game;
class Graphics;

class Map
{
	int			_width; 
	int			_height;
public:
	Map(int width, int height);
	void update(Game* game);
};