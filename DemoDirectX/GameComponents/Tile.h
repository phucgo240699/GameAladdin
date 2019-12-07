#pragma once
class Tile
{
private:
	int x, y, width, height;
public:
	void SetX(int x);
	void SetY(int y);
	void SetWidth(int width);
	void SetHeight(int height);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	Tile();
	Tile(int x, int y, int w, int h);
	~Tile();
};

