#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState
{
public:
    PlayerRunningState(PlayerData *playerData);
    ~PlayerRunningState();

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void OnCollision(int normalX, int normalY);

    virtual StateName GetState();

protected:
    float acceleratorX;
	bool isMovingLeft, isMovingRight;
};

