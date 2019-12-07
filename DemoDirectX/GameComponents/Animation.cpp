#include "Animation.h"

Animation::Animation()
{

}

int Animation::GetCurrentFrameHeight()
{
	return listAnimationInfo[currentFrameIndex]->GetHeight();
}

Animation::Animation(const char* pathSpriteSheet, const char * pathAnimationInfo, float _timePerFrame, D3DCOLOR colorKey)
{
	InitWithAnimation(pathSpriteSheet, pathAnimationInfo, _timePerFrame, colorKey);
}

void Animation::InitWithAnimation(const char* pathSpriteSheet, const char * pathAnimationInfo, float _timePerFrame, D3DCOLOR colorKey)
{
	currentTotalTime = 0;
	timePerFrame = _timePerFrame;
	totalFrame = 0;
	currentFrameIndex = lastFrameIndex = 0;

	infile.open(pathAnimationInfo);

	if (!infile.is_open()) {
		DebugOut(L"can't open animation info file.\n");
	}

	int x, y, w, h;
	while (infile >> x >> y >> w >> h) {
		listAnimationInfo.push_back(new Tile(x, y, w, h));
		++totalFrame;
	}

	infile.close();
	////GAMELOG("animation: frame: %d, row: %d, column: %d, time: %f", totalFrame, rows, columns, timePerFrame);
	//this->InitWithSprite(filePath);
	//mCurrentColumn = 0;
	//mCurrentRow = 0;
	//mTimePerFrame = timePerFrame;
	//mTotalFrame = totalFrame;
	//mRows = rows;
	//mColumns = columns;

	////width - height luc nay la cua spritesheet
	//mFrameWidth = GetWidth() / mColumns;
	//mFrameHeight = GetHeight() / mRows;

	//SetWidth(mFrameWidth);
	//SetHeight(mFrameHeight);

	//mRect.top = 0;
	//mRect.left = 0;
	//mRect.right = mFrameWidth;
	//mRect.bottom = mFrameHeight;
	//SetSourceRect(mRect);

	spriteSheet = new Sprite(pathSpriteSheet);
	spriteSheet->SetWidth(listAnimationInfo[currentFrameIndex]->GetWidth());
	spriteSheet->SetHeight(listAnimationInfo[currentFrameIndex]->GetHeight());

	rect.top = listAnimationInfo[currentFrameIndex]->GetY();
	rect.bottom = rect.top + listAnimationInfo[currentFrameIndex]->GetHeight();
	rect.left = listAnimationInfo[currentFrameIndex]->GetX();
	rect.right = rect.left + listAnimationInfo[currentFrameIndex]->GetWidth();
	spriteSheet->SetSourceRect(rect);
}

Animation::~Animation()
{

}

void Animation::Update(float dt)
{
	if (totalFrame <= 1)
		return;

	if (currentTotalTime >= timePerFrame)
	{


		/*currentTotalTime = 0;
		currentFrameIndex++;
		currentColumn++;

		if (mCurrentIndex >= mTotalFrame)
		{
			mCurrentIndex = 0;
			mCurrentColumn = 0;
			mCurrentRow = 0;
		}

		if (mCurrentColumn >= mColumns)
		{
			mCurrentColumn = 0;
			mCurrentRow++;

			if (mCurrentRow >= mRows)
				mCurrentRow = 0;
		}*/
		currentTotalTime = 0;

		currentFrame = listAnimationInfo[currentFrameIndex];


		/*if (count == 1 && currentFrameIndex != 0) {
			if (currentFrame->GetHeight() > listAnimationInfo[currentFrameIndex - 1]->GetHeight()) {
				spriteSheet->SetPosition(spriteSheet->GetPosition().x, spriteSheet->GetPosition().y - (currentFrame->GetHeight() - listAnimationInfo[currentFrameIndex - 1]->GetHeight()));
			}
			else if (currentFrame->GetHeight() < listAnimationInfo[currentFrameIndex - 1]->GetHeight()) {
				spriteSheet->SetPosition(spriteSheet->GetPosition().x, spriteSheet->GetPosition().y + listAnimationInfo[currentFrameIndex - 1]->GetHeight() - currentFrame->GetHeight());
			}
		}
		else if (count == -1 && currentFrameIndex != listAnimationInfo.size() - 1) {
			if (currentFrame->GetHeight() > listAnimationInfo[currentFrameIndex + 1]->GetHeight()) {
				spriteSheet->SetPosition(spriteSheet->GetPosition().x, spriteSheet->GetPosition().y - (currentFrame->GetHeight() - listAnimationInfo[currentFrameIndex + 1]->GetHeight()));
			}
			else if (currentFrame->GetHeight() < listAnimationInfo[currentFrameIndex - 1]->GetHeight()) {
				spriteSheet->SetPosition(spriteSheet->GetPosition().x, spriteSheet->GetPosition().y + listAnimationInfo[currentFrameIndex + 1]->GetHeight() - currentFrame->GetHeight());
			}
		}*/


		spriteSheet->SetWidth(currentFrame->GetWidth());
		spriteSheet->SetHeight(currentFrame->GetHeight());

		rect.top = currentFrame->GetY();
		rect.bottom = rect.top + currentFrame->GetHeight();
		rect.left = currentFrame->GetX();
		rect.right = rect.left + currentFrame->GetWidth();

		spriteSheet->SetSourceRect(rect);
		lastFrameIndex = currentFrameIndex;
		currentFrameIndex += count;
		currentFrameIndex %= listAnimationInfo.size();
		//(currentFrameIndex + 1) % frames.size();
		if (id == 1) { // Standing
			/*if (currentFrameIndex == listAnimationInfo.size() - 1 || currentFrameIndex == 0) {
				count *= -1;
			}*/

			if (currentFrameIndex == listAnimationInfo.size() - 1) {
				currentFrameIndex = 1;
			}
		}
	}
	else
	{
		currentTotalTime += dt;
	}
}

void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale,
	D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	spriteSheet->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::Draw(D3DXVECTOR2 translate)
{
	spriteSheet->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}

Sprite * Animation::GetSpriteSheet()
{
	return this->spriteSheet;
}

void Animation::SetCurrentFrameIndex(int index)
{
	currentFrameIndex = index;
}
