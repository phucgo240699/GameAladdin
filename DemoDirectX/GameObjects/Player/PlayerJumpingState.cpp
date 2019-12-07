#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->playerData = playerData;
    this->playerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

    acceleratorY = 15.0f;
    acceleratorX = 14.0f;

    noPressed = false;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
    this->playerData->player->AddVy(acceleratorY);   

    if (playerData->player->GetVy() >= 0)
    {
        //playerData->player->SetState(new PlayerFallingState(this->playerData));

        return;
    }

    if (noPressed)
    {
        if (playerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            //player dang di chuyen sang ben trai      
            if (playerData->player->GetVx() < 0)
            {
                this->playerData->player->AddVx(acceleratorX);

                if (playerData->player->GetVx() > 0)
                    this->playerData->player->SetVx(0);
            }
        }
        else if (playerData->player->getMoveDirection() == Player::MoveToRight)
        {
            //player dang di chuyen sang phai   
            if (playerData->player->GetVx() > 0)
            {
                this->playerData->player->AddVx(-acceleratorX);

                if (playerData->player->GetVx() < 0)
                    this->playerData->player->SetVx(0);
            }
        }
    }
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        playerData->player->SetReverse(false);

        //di chuyen sang phai
        if (this->playerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->playerData->player->AddVx(acceleratorX);

            if (this->playerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->playerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else if (keys[VK_LEFT])
    {
        playerData->player->SetReverse(true);

        //di chuyen sang trai
        if (this->playerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->playerData->player->AddVx(-acceleratorX);

            if (this->playerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->playerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else
    {
        noPressed = true;
    }
}

void PlayerJumpingState::OnCollision(int normalX, int normalY) {
	if (normalY < 0) {
		this->playerData->player->SetState(new PlayerStandingState(this->playerData));
	}
}

void PlayerJumpingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
 {
    switch (side)
    {
        case Entity::Left:
        {
            this->playerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
            this->playerData->player->SetVx(0);
            break;
        }     

        case Entity::Right:
        {
            this->playerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
            this->playerData->player->SetVx(0);
            break;
        }

        case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
        {          
            this->playerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);            
            this->playerData->player->SetVy(0);
            break;
        }

        case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
        {
            this->playerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
        }

        default:
            break;
    }
}

PlayerState::StateName PlayerJumpingState::GetState()
{
    return PlayerState::Jumping;
}
