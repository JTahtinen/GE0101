#include "game.h"

Game::Game()
{
	_map = new Map(10, 10);
}

Game::~Game()
{
}

void Game::update()
{
	_map->update(this);
}

void Game::render(Graphics* g)
{
	_map->render(g);
}