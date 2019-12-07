#include "Grid.h"

//using namespace tinyxml2;

Grid::Grid()
{
}

Grid::Grid(char * filePath)
{
	this->filePath = filePath;

	//loadGridFromFile();
	loadGridFromFileTXT();
}

Grid::~Grid()
{
	/*for (int i = 0; i < CELL_MAX_COLUMN; ++i) {
		for (int j = 0; j < CELL_MAX_ROW; ++j) {
			cells[i][j].clear();
		}
	}*/
}

void Grid::setFilePath(char * s)
{
	filePath = s;
}

//Entity *initObject(int typeID, tinyxml2::XMLElement *pElement) {
//	switch(typeID){
//	case 3:
//		return new Entity(pElement);
//	case 5:
//		return new Entity(pElement);
//	case 6:
//		return new Entity(pElement);
//	case 8:
//		return new Entity(pElement);
//	}
//	//return ObjectInstancesManagemer::instances[typeID]->createObject(pElement);
//}

Entity *initObject(int typeID, int id, int x, int y, int width, int height) {
	switch(typeID){
	case 3:
		return new Entity(x, y, width, height, id);
	case 5:
		return new Entity(x, y, width, height, id);
	case 6:
		return new Entity(x, y, width, height, id);
	case 8:
		return new Entity(x, y, width, height, id);
	}
}

//void Grid::loadGridFromFile()
//{
//	tinyxml2::XMLDocument doc;
//	doc.LoadFile(filePath);
//
//	if (!doc.ErrorID()) {
//		tinyxml2::XMLElement *pRoot = doc.FirstChildElement("map");
//		tinyxml2::XMLElement *pElement = pRoot->FirstChildElement("objectgroup");
//
//		while (pElement) {
//			int typeID = atoi(pElement->Attribute("id"));
//			tinyxml2::XMLElement *pObjectElement = pElement->FirstChildElement("object");
//
//			while (pObjectElement) {
//				insertGameObject(initObject(typeID, pObjectElement));
//
//				pObjectElement = pObjectElement->NextSiblingElement("object");
//			}
//
//			pElement = pElement->NextSiblingElement("objectgroup");
//		}
//	}
//}

bool Grid::loadGridFromFileTXT() {
	ifstream inp;
	float typeID, id, x, y, width, height, cellX, cellY;

	//clearGrid();

	inp.open(filePath);
	if (!inp.is_open()) {
		DebugOut(L"[Error]: Failed to open grid data file.\n");

		return false;
	}

	while (inp >> typeID >> id >> x >> y >> width >> height >> cellX >> cellY) {
		insertGameObject(initObject(typeID, id, x, y, width, height), cellX, cellY);
	}

	inp.close();

	DebugOut(L"[Succeed]: Initiated grid successfully.\n");

	return 1;
}

void Grid::clearGrid()
{
	for (int i = 0; i < CELL_MAX_COLUMN; ++i) {
		for (int j = 0; j < CELL_MAX_ROW; ++j) {
			cells[i][j].clear();
		}
	}

	entities.clear();
}

void Grid::reloadGrid()
{
	clearGrid();
}

void Grid::reloadGrid(vector<Entity* > &Objects)
{
	clearGrid();

	/*for (Entity* object : Objects) {
		insertGameObject(object, );
	}*/
}

void Grid::insertGameObject(Entity* object, int cellX, int cellY) {
	cells[cellX][cellY].push_back(object);

	if (entities.empty()) {
		object->cellList.push_back({ cellX, cellY });
		entities.insert(object);
	}
	else {
		set<Entity*>::iterator it = entities.find(object);

		if (it != entities.end()) {
			(*it)->cellList.push_back({ cellX, cellY });
		}
		else {
			object->cellList.push_back({ cellX, cellY });
			entities.insert(object);
		}
	}

	string p = "inserted to grid object: " + to_string(object->getID()) + '\n';
	wstring pp(p.begin(), p.end());
	const wchar_t* r = pp.c_str();
	DebugOut(r);
}

vector<Entity*> Grid::getObjectInCamera(Camera * cam)
{
	RECT rect = cam->getBound();
	vector<Entity*> result;

	for (int i = rect.left; i <= rect.right; ++i) {
		for (int j = rect.top; j <= rect.bottom; ++j) {
			vector<Entity*> tmp = getCellObject(i, j);

			for (Entity* object : tmp) {
				result.push_back(object);
			}
		}
	}

	return result;
}

vector<Entity*> Grid::getCellObject(int x, int y)
{
	return cells[x][y];
}
