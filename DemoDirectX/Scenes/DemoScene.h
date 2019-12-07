#pragma once

#include <math.h>
#include <vector>
#include <string>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"

class DemoScene : public Scene
{
public:
    DemoScene();


	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void OnMouseDown(float x, float y);

    void Update(float dt);
    void LoadContent();
    void Draw();

	float calEntryDistance(int x, int y, int p1, int p2, int speed, char option);
	float calExitDistance(int x, int y, int p1, int p2, int speed, char option);
	float calEntryTime(float entryDistance, int speed);
	//void calNormalVector(float collisionEntryTime, float collisionExitTime,int &normalX, int &normalY);
	float calExitTime(float exitDistance, int speed);
	float Swept_AABB(Entity* object1, Entity* object2, int &normalX, int &normalY, float dt);
	Entity* GetSweptBroadphaseBox(Entity* object);
	bool AABBCheck(Entity* object1, Entity* object2);
protected:
	GameMap * map;
	Camera * camera;
	Player * player;
	std::vector<Sprite*> listSprite;
	int count = 0;
	int posx = 0;
    float mTimeCounter;

	std::map<int, bool> keys;

	void checkCollision(Entity *object, float dt);
};

