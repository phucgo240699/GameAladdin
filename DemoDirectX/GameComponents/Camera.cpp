#include "Camera.h"



Camera::Camera()
{
	x = 0;
	y = 0;
	height = 480;
	width = 640;
	isAllowedToFollowPlayerX = 0;
	isAllowedToFollowPlayerY = 0;

	catchUpDistance = 0;
	leftBorder = 0;
	rightBorder = 2272;
}

Camera::Camera(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


Camera::~Camera()
{
}

int Camera::getX()
{
	return x;
}

void Camera::setX(int x)
{

	this->x = x;
}

int Camera::getY() {
	return y;
}

void Camera::setY(int y) {
	this->y = y;
}

int Camera::getWidth() {
	return width;
}

void Camera::setWidth(int width) {
	this->width = width;
}

int Camera::getHeight() {
	return height;
}

void Camera::setHeight(int height) {
	this->height = height;
}

bool Camera::isInFollowState() {
	return isAllowedToFollowPlayerX;
}

void Camera::setFollowState(bool followState) {
	isAllowedToFollowPlayerX = followState;
}

float Camera::getCatchUpDistance() {
	return catchUpDistance;
}

void Camera::setCatchUpDistance(float distance) {
	catchUpDistance = distance;
}

int Camera::getLeftBorder() {
	return leftBorder;
}

void Camera::setLeftBorder(int left) {
	leftBorder = left;
}

int Camera::getRightBorder() {
	return rightBorder;
}

void Camera::setRightBorder(int right) {
	rightBorder = right;
}

int Camera::calCatchUpDistance(Entity* player) {
	int anchorPoint = SCREEN_WIDTH / 2;

	if (player->GetPosition().x >= anchorPoint) {
		catchUpDistance = anchorPoint = 1;
	}

	if (!x && player->GetVx() < 0) {
		catchUpDistance = 0;
	}
	else if (x == -anchorPoint && player->GetVx() > 0) {
		catchUpDistance = 0;
	}
	else {
		catchUpDistance = player->GetPosition().x - anchorPoint;
	}

	return catchUpDistance;
}

void Camera::displayObject(Entity * object, LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture)
{
	/*if (object->getX() < x || object->getX() > x + width) {
		return;
	}*/

	/*D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1.0f;
	matrix._41 = (float)-x;
	matrix._42 = (float)y;

	D3DXVECTOR3 position(object->GetPosition().x, object->GetPosition().y, 1);

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &matrix);

	D3DXVECTOR3 pos(vp_pos.x, -vp_pos.y, 0);

	object->setViewX(pos.x);
	object->setViewY(pos.y);*/

	D3DXVECTOR3 pos(object->GetPosition().x - x, object->GetPosition().y - y, 0);

	spriteHandler->Draw(texture, NULL, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));
}

void Camera::moveCamera(Entity* player, float dt)
{
	isAllowedToFollowPlayerX = (player->GetPosition().x + player->GetWidth() / 2 >= width / 2 && player->GetPosition().x + player->GetWidth() / 2 <= 2272 - width / 2);
	isAllowedToFollowPlayerY = (player->GetPosition().y + player->GetHeight() / 2 >= height / 2 && player->GetPosition().y + player->GetHeight() / 2 <= 1120 - height / 2);

	if (x + player->GetVx()*dt < 0 || x + player->GetVx()*dt > 2272) {
		float d = (player->GetVx() > 0) ? 2272 - x : x;
		float t = d / player->GetVx();

		x += player->GetVx()*t;
		isAllowedToFollowPlayerX = 0;
	}

	if (y + player->GetVy()*dt < 0 || y + player->GetVy()*dt > 1120) {
		float d = (player->GetVy() > 0) ? 1120 - y : y;
		float t = d / player->GetVy();

		y += player->GetVy()*t;
		isAllowedToFollowPlayerY = 0;
	}
/*
	if (player->GetPosition().x + player->GetWidth() / 2 <= 320) {
		x = 0;
		isAllowedToFollowPlayerX = 0;
	}
	if (player->GetPosition().x + player->GetWidth() / 2 >= 2272 - width / 2) {
		x = 2272 - width;
		isAllowedToFollowPlayerX = 0;
	}*/

	/*if (player->GetPosition().y + player->GetHeight() / 2 <= 320) {
		y = 0;
		isAllowedToFollowPlayerY = 0;
	}
	if (player->GetPosition().y + player->GetHeight() / 2 >= 1120 - width / 2) {
		y = 1120 - height;
		isAllowedToFollowPlayerY = 0;
	}*/

	if (isAllowedToFollowPlayerX) {
		x += player->GetVx()*dt;
		//x = player->GetPosition().x + player->GetWidth() / 2 - 320;

		/*string p = to_string(player->GetPosition().x) + '\n';
		wstring pp(p.begin(), p.end());
		const wchar_t* r = pp.c_str();
		DebugOut(r);*/
	}
	if (isAllowedToFollowPlayerY) {
		if (player->GetVy()) {
			y = player->GetPosition().y + player->GetHeight() / 2 - 240;
		}
	}
	string tmp = "Cam: " + to_string(player->GetVx()*dt) + '\n';
	wstring t(tmp.begin(), tmp.end());
	const wchar_t* rs = t.c_str();
	DebugOut(rs);
}

RECT Camera::getBound()
{
	RECT rs;

	rs.left = x;
	rs.right = x + width;
	rs.top = y;
	rs.bottom = y + height;

	return rs;
}

