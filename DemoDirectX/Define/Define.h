#pragma once
namespace Define
{
	const float PLAYER_MAX_JUMP_VELOCITY = 380.0f; //van toc nhay lon nhat
	const float PLAYER_MIN_JUMP_VELOCITY = -380.0f; //van toc nhay thap nhat
	const float PLAYER_MAX_RUNNING_SPEED = 200.0f; //toc do chay nhanh nhat cua player
	const float PLAYER_BOTTOM_RANGE_FALLING = 6.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
}

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CELL_WIDTH (SCREEN_WIDTH/4)
#define CELL_HEIGHT (SCREEN_HEIGHT/4)
#define CELL_MAX_COLUMN (2272/CELL_WIDTH+1)
#define CELL_MAX_ROW (1120/CELL_HEIGHT+1)