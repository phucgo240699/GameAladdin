#include "GameMap.h"

GameMap::GameMap()
{
	LoadMap("./Resources/ListImage/map_aladdin.png");
}

GameMap::~GameMap()
{
}

void GameMap::LoadMap(char * filePath)
{
	int r, c;
	map = new Sprite(filePath);

	infile.open("./Resources/ListImage/map_info.txt");

	infile >> spriteSize;
	infile >> c;
	infile >> r;

	infile.close();

	// Initialize listID
	listID.resize(r);
	for (int i = 0; i < r; ++i)
		listID[i].resize(c);

	// Read tile id into listID
	infile.open("./Resources/ListImage/sprite_sheet_map_aladdin.txt");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			infile >> listID[i][j];
		}
	}
	infile.close();

	grid = new Grid("./Resources/Grid_Dungeon.txt");
}

void GameMap::Update()
{


}

void GameMap::Draw()
{
	// begin ---> end: from left ro right
	int cellIDBeginX = camera->getX() / spriteSize;
	int cellIDEndX = (camera->getX() + camera->getWidth()) / spriteSize;
	numberOfSpritesPerRow = cellIDEndX - cellIDBeginX ;
	//	begin
	//	  |
	//	  |
	//	  v
	//	 end
	// from up to down
	int cellIDBeginY = camera->getY() / spriteSize;
	int cellIDEndY = (camera->getY() + camera->getHeight()) / spriteSize;
	numberOfSpritesPerColumn = cellIDEndY - cellIDBeginY;

	for (int m = cellIDBeginY; m <= cellIDEndY; ++m) {
		for (int n = cellIDBeginX; n <= cellIDEndX; ++n) {
			rect.top = m * spriteSize;
			rect.bottom = rect.top + spriteSize;
			rect.left = n * spriteSize;
			rect.right = rect.left + spriteSize;
			
			// Postion of a tile compare to position of camera.
			// (top-left)

			D3DXVECTOR3 position(n * spriteSize - camera->getX(), m * spriteSize - camera->getY(), 0);

			map->Draw(position, rect);
		}
	}
}



void GameMap::SetCamera(Camera * camera)
{
	this->camera = camera;
}

Grid * GameMap::getGrid()
{
	return grid;
}
