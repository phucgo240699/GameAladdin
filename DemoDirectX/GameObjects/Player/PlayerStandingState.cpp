#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->playerData = playerData;
    this->playerData->player->SetVx(0);
    this->playerData->player->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->playerData->player->SetState(new PlayerRunningState(this->playerData));
		
        return;
    }
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
