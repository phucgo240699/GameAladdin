#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
	this->playerData = playerData;
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;

	if (this->playerData->player->GetVx() == 0)
	{
		allowMoveX = false;
	}
	else
	{
		allowMoveX = true;
	}
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	this->playerData->player->AddVy(acceleratorY);

	if (playerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		playerData->player->SetReverse(false);

		isLeftOrRightKeyPressed = true;
		//di chuyen sang phai
		if (this->playerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->playerData->player->AddVx(acceleratorX);

			if (this->playerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->playerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		playerData->player->SetReverse(true);

		isLeftOrRightKeyPressed = true;
		//di chuyen sang trai
		if (this->playerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->playerData->player->AddVx(-acceleratorX);

			if (this->playerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->playerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else
	{
		isLeftOrRightKeyPressed = false;
	}
}

void PlayerFallingState::OnCollision(int normalX, int normalY) {
	if (normalY < 0) {
		this->playerData->player->SetState(new PlayerStandingState(this->playerData));
	}
}

void PlayerFallingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->playerData->player, data);

	switch (side)
	{
	case Entity::Left:
		if (playerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			this->playerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->playerData->player->SetVx(0);
		}
		break;

	case Entity::Right:
		if (playerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->playerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->playerData->player->SetVx(0);
		}
		break;

	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			this->playerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			if (isLeftOrRightKeyPressed)
			{
				this->playerData->player->SetState(new PlayerRunningState(this->playerData));
			}
			else
			{
				this->playerData->player->SetState(new PlayerStandingState(this->playerData));
			}
		}
		return;

	default:
		break;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return PlayerState::Falling;
}
