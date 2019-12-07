#pragma once
#include <fstream>
#include <iostream>
using namespace std;
#include"../../GameComponents/Sprite.h"
#include"../../GameComponents/Camera.h"

class WoodColumnMap {
private:
	Sprite * map;
	Camera * camera;
	int spriteSize, numberOfSpritesPerRow, numberOfSpritesPerColumn;

	RECT rect;
	int tileID;
	int ** listID;
	int posX, posY;


	ifstream infile;
	ofstream outfile;

public:
	WoodColumnMap();
	~WoodColumnMap();
	void LoadMap(char *filePath);
	void Update();
	void Draw();
	void SetCamera(Camera * camera);
};


