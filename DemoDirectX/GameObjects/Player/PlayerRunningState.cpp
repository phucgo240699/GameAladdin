#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->playerData = playerData;
    
    acceleratorX = 25.0f;

    this->playerData->player->allowMoveLeft = true;
    this->playerData->player->allowMoveRight = true;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
		isMovingLeft = 0;
		isMovingRight = 1;
        if (playerData->player->allowMoveRight)
        {
			/*if (this->playerData->player->GetReverse() == true) {
				D3DXVECTOR3 pos = this->playerData->player->GetPosition();
				int w = this->playerData->player->GetWidth();
				this->playerData->player->SetPosition(pos.x - w, pos.y);
			}*/
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
        }
    }
    else if (keys[VK_LEFT])
    {
		isMovingLeft = 1;
		isMovingRight = 0;
        if (playerData->player->allowMoveLeft)
        {
			/*if (this->playerData->player->GetReverse() == false) {
				D3DXVECTOR3 pos = this->playerData->player->GetPosition();
				int w = this->playerData->player->GetWidth();
				this->playerData->player->SetPosition(pos.x + w, pos.y);
			}*/
            playerData->player->SetReverse(true);
			
			//D3DXVECTOR3 positionPlayer = playerData->player->GetPosition();
			//int wid = playerData->player->GetWidth();
			////if(playerData->player->GetReverse())
			//playerData->player->SetPosition(positionPlayer.x + this->playerData->player->GetCurrentAnimation()->GetSpriteSheet()->GetWidth(),positionPlayer.y);
			//D3DXVECTOR3 p = playerData->player->GetPosition();
            //di chuyen sang trai
            if (this->playerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->playerData->player->AddVx(-acceleratorX);

                if (this->playerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->playerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
                }
            }
        }
    }
    else
    {
        this->playerData->player->SetState(new PlayerStandingState(this->playerData));
        return;
    }
}

void PlayerRunningState::OnCollision(int normalX, int normalY) {
	//if (normalX) {
	//	this->playerData->player->SetState(new PlayerStandingState(this->playerData)); // pushing state, vx=0, unable to move horizontal
	//}
	Entity *temp = playerData->player->standingSurface;

	if (temp) {
		if ((playerData->player->GetPosition().x > temp->GetPosition().x + temp->GetWidth()) || (playerData->player->GetPosition().x + playerData->player->GetWidth() < temp->GetPosition().x)) {
			this->playerData->player->SetState(new PlayerFallingState(this->playerData));
		}
	}
}

void PlayerRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->playerData->player, data);

    switch (side)
    {
        case Entity::Left:
        {
            //va cham phia ben trai player
            if (this->playerData->player->getMoveDirection() == Player::MoveToLeft)
            {
                this->playerData->player->allowMoveLeft = false;

                //day Player ra phia ben phai de cho player khong bi xuyen qua object
                this->playerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

                this->playerData->player->SetState(new PlayerStandingState(this->playerData));
            }

            return;
        }

        case Entity::Right: 
        {
            //va cham phia ben phai player
            if (this->playerData->player->getMoveDirection() == Player::MoveToRight)
            {
                this->playerData->player->allowMoveRight = false;
                this->playerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
                this->playerData->player->SetState(new PlayerStandingState(this->playerData));
            }
            return;
        }

		case Entity::Top: {
			//
			break;
		}
			

        case Entity::Bottom: case Entity::BottomLeft : case Entity::BottomRight:           
        {
            this->playerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

            this->playerData->player->SetVy(0);

			//this->playerData->player->SetState(new PlayerStandingState(this->playerData));
            return;
        }
    }
}

PlayerState::StateName PlayerRunningState::GetState()
{
    return PlayerState::Running;
}
