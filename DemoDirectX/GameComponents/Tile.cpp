#include "Tile.h"



int Tile::GetHeight()
{
	return this->height;
}

Tile::Tile()
{
}

Tile::Tile(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}


Tile::~Tile()
{
}

void Tile::SetX(int x)
{
	this->x = x;
}

void Tile::SetY(int y)
{
	this->y = y;
}

void Tile::SetWidth(int width)
{
	this->width = width;
}

void Tile::SetHeight(int height)
{
	this->height = height;
}

int Tile::GetX()
{
	return this->x;
}

int Tile::GetY()
{
	return this->y;
}

int Tile::GetWidth()
{
	return this->width;
}
