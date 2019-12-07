#pragma once
//#include "../GameComponents/GameObject.h"
//#include "../GameComponents/StaticObject.h"
#include "../GameComponents/Game.h"
//#include "../GameComponents/Camera.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
//#include "../GameObjects/Entity.h"
#include "../Define/Define.h"
#include "../GameObjects/Entity.h"
#include "../GameComponents/Camera.h"
#include "../debug.h"
#include <string>
//#include "../GameComponents/ObjectInstancesManager.h"

using namespace std;

class Grid
{
	vector<Entity* > cells[CELL_MAX_COLUMN][CELL_MAX_ROW];
	char* filePath;
	set<Entity*> entities;
public:
	Grid();
	Grid(char* filePath);
	~Grid();
	void setFilePath(char* s);
	//void loadGridFromFile();
	bool loadGridFromFileTXT();
	void clearGrid();
	void reloadGrid();
	void reloadGrid(vector<Entity* > &Objects);
	void insertGameObject(Entity* object, int cellX, int cellY);
	vector<Entity*> getObjectInCamera(Camera *cam);
	
	vector<Entity* > getCellObject(int x, int y);
};

