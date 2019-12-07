#pragma once
#include"../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	enum MoveDirection
	{
		MoveToLeft, //chay tu phai sang trai
		MoveToRight, //chay tu trai sang phai
		None //dung im
	};

	D3DXVECTOR3 coodirnateTransfer(D3DXVECTOR3 cameraPos);

	void SetCamera(Camera *camera);

	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void SetState(PlayerState *newState);

	void OnCollision(int normalX=0, int normalY=0);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	void OnNoCollisionWithBottom();

	MoveDirection getMoveDirection();

	RECT GetBound();

	PlayerState::StateName Player::getState();

	//xu ly input
	//gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
	void HandleKeyboard(std::map<int, bool> keys);

	void OnKeyPressed(int key);

	void OnKeyUp(int key);

	//true thi se lat nguoc anh theo truc y
	void SetReverse(bool flag);

	bool GetReverse();

	bool allowMoveLeft;
	bool allowMoveRight;

	Animation * GetCurrentAnimation();

	Entity *standingSurface;

	int lastFrameHeight;

protected:

	Camera      * camera;

	PlayerData * playerData;

	Animation   * currentAnimation,
		*animationStanding,
		*animationRunning,
		*animationJumping,
		*animationJumpMoving,
		*animationFalling;

	void changeAnimation(PlayerState::StateName state);

	PlayerState::StateName currentState;

	//chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
	bool allowJump, mCurrentReverse;;
};



