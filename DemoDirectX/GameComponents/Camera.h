#pragma once
#include "../GameObjects/Entity.h"
#include "../Define/Define.h"
#include "../GameComponents/GameGlobal.h"
#include "../debug.h"
#include "string"

using namespace std;

class Camera
{
	float x, y;
	int width, height;
	bool isAllowedToFollowPlayerX;
	bool isAllowedToFollowPlayerY;
	float catchUpDistance; // the distance that cam has to travel to catch up with the ball
	int leftBorder, rightBorder;
public:
	Camera();
	Camera(int x, int y, int width, int height);
	~Camera();
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getWidth();
	void setWidth(int width);
	int getHeight();
	void setHeight(int height);
	bool isInFollowState();
	void setFollowState(bool followState);
	float getCatchUpDistance();
	void setCatchUpDistance(float distance);
	int getLeftBorder();
	void setLeftBorder(int left);
	int getRightBorder();
	void setRightBorder(int right);
	int calCatchUpDistance(Entity* ball);
	void displayObject(Entity* object, LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture);
	void moveCamera(Entity* player, float dt);
	RECT getBound();
};

