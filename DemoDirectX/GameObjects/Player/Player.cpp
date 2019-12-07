#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"

Player::Player()
{
	animationStanding = new Animation("Resources/Aladdin/AladdinSpriteSheet.png", "Resources/Aladdin/Standing.txt", 0.15f);
	animationStanding->id = 1;
	animationRunning = new Animation("Resources/Aladdin/AladdinSpriteSheet.png", "Resources/Aladdin/Running.txt");
	animationJumping = new Animation("Resources/Aladdin/AladdinSpriteSheet.png", "Resources/Aladdin/Jumping.txt");
	//animationJumpMoving = new Animation("Resources/Aladdin/AladdinSpriteSheet.png", "JumpMoving.txt");
	animationFalling = new Animation("Resources/Aladdin/AladdinSpriteSheet.png", "Resources/Aladdin/Falling.txt");
	this->playerData = new PlayerData();
	this->playerData->player = this;
	this->vx = 0;
	this->vy = 0;
	this->SetState(new PlayerFallingState(this->playerData));
	allowJump = true;
	id = 1;

	updateCellList();
	/*id = 1;

	mAnimationStanding = new Animation("Resources/Aladdin2/Standing.png", 7, 1, 7, 0.1f);
	mAnimationJumping = new Animation("Resources/Aladdin2/Jumping.png", 9, 1, 9, 0.15f);
	mAnimationRunning = new Animation("Resources/Aladdin2/Running.png", 12, 1, 12, 0.15f);

	this->mPlayerData = new PlayerData();
	this->mPlayerData->player = this;
	this->vx = 0;
	this->vy = 0;
	this->SetState(new PlayerFallingState(this->mPlayerData));

	allowJump = true;

	updateCellList();*/
	lastFrameHeight = 0;
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	/*int dy = currentAnimation->GetCurrentFrameHeight() - lastFrameHeight;
	lastFrameHeight = currentAnimation->GetCurrentFrameHeight();*/

	currentAnimation->Update(dt);

	int t = currentAnimation->GetCurrentFrameHeight();

	if (this->playerData->state)
	{
		this->playerData->state->Update(dt);
	}
	Entity::Update(dt);
	camera->moveCamera(this, dt);
	//posY -= dy;
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (this->playerData->state)
	{
		this->playerData->state->HandleKeyboard(keys);
	}
}

void Player::OnKeyPressed(int key)
{
	if (key == VK_SPACE)
	{
		if (allowJump)
		{
			if (currentState == PlayerState::Running || currentState == PlayerState::Standing)
			{
				this->SetState(new PlayerJumpingState(this->playerData));
			}

			allowJump = false;
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
		allowJump = true;
}

void Player::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

Animation * Player::GetCurrentAnimation()
{
	return this->currentAnimation;
}

D3DXVECTOR3 Player::coodirnateTransfer(D3DXVECTOR3 cameraPos)
{
	float viewportX, viewportY;

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1.0f;
	matrix._41 = (float)-cameraPos.x;
	matrix._42 = (float)cameraPos.y;

	D3DXVECTOR3 position(posX, posY, 1);

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &matrix);

	D3DXVECTOR3 pos(vp_pos.x, -vp_pos.y, 0);

	viewportX = pos.x;
	viewportY = pos.y;

	//spriteHandler->Draw(texture, NULL, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));

	return D3DXVECTOR3(viewportX, viewportY, 0);
}

void Player::SetCamera(Camera *camera)
{
	this->camera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	currentAnimation->GetSpriteSheet()->FlipVertical(mCurrentReverse);
	currentAnimation->GetSpriteSheet()->SetPosition(/*this->coodirnateTransfer(mCamera->GetPosition())*/ this->GetPosition());

	if (getState() == PlayerState::Standing || getState() == PlayerState::Running) {
		//if(this->GetHeight() == 55)
		this->posY = standingSurface->GetPosition().y - this->currentAnimation->GetSpriteSheet()->GetHeight() - 10;
	}

	if (camera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(-camera->getX(), -camera->getY());

		currentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
	{
		currentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
	}
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;

	delete this->playerData->state;

	this->playerData->state = newState;

	this->changeAnimation(newState->GetState());

	currentState = newState->GetState();
}

void Player::OnCollision(int normalX, int normalY)
{
	this->playerData->state->OnCollision(normalX, normalY);
}

void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	//this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	this->playerData->state->OnCollision(impactor, side, data);
}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = this->posX - currentAnimation->GetSpriteSheet()->GetWidth() / 2;
	rect.right = rect.left + currentAnimation->GetSpriteSheet()->GetWidth();
	rect.top = this->posY - currentAnimation->GetSpriteSheet()->GetHeight() / 2;
	rect.bottom = rect.top + currentAnimation->GetSpriteSheet()->GetHeight();

	return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Running:
		currentAnimation = animationRunning;
		break;

	case PlayerState::Standing:
		currentAnimation = animationStanding;
		break;

	case PlayerState::Falling:
		currentAnimation = animationFalling;
		break;

	case PlayerState::Jumping:
		currentAnimation = animationJumping;
		break;

	default:
		break;
	}

	currentAnimation->SetCurrentFrameIndex(0);
	this->width = currentAnimation->GetSpriteSheet()->GetWidth();
	this->height = currentAnimation->GetSpriteSheet()->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
	if (this->vx > 0)
	{
		return MoveDirection::MoveToRight;
	}
	else if (this->vx < 0)
	{
		return MoveDirection::MoveToLeft;
	}

	return MoveDirection::None;
}

void Player::OnNoCollisionWithBottom()
{
	/*if (currentState != PlayerState::Jumping && currentState != PlayerState::Falling)
	{
		this->SetState(new PlayerFallingState(this->playerData));
	}*/
}

bool Player::GetReverse() {
	return mCurrentReverse;
}

PlayerState::StateName Player::getState()
{
	return currentState;
}
