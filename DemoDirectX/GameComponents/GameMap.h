#pragma once
#include <fstream>
#include <iostream>
using namespace std;
#include"../GameComponents/Sprite.h"
#include"../GameComponents/Camera.h"
#include"Grid.h"

class GameMap {
private:
	Sprite * map;
	Camera * camera;
	int spriteSize, numberOfSpritesPerRow, numberOfSpritesPerColumn;
	
	RECT rect;
	int tileID;
	vector<vector<int> > listID;
	int posX, posY;


	ifstream infile;
	ofstream outfile;

	Grid *grid;

public:
	GameMap();
	~GameMap();
	void LoadMap(char *filePath);
	void Update();
	void Draw();
	void SetCamera(Camera * camera);
	Grid* getGrid();
};


