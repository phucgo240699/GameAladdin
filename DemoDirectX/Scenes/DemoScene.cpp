#include "DemoScene.h"

DemoScene::DemoScene()
{
	LoadContent();

}

void DemoScene::LoadContent()
{
	//set time counter = 0
	mTimeCounter = 0;

	//set mau backcolor cho scene o day la mau xanh
	mBackColor = 0xffffff;

	map = new GameMap();
	camera = new Camera();

	camera->setWidth(GameGlobal::GetWidth());
	camera->setHeight(GameGlobal::GetHeight());
	camera->setX(0);
	camera->setY(0);
	map->SetCamera(camera);

	player = new Player();
	player->SetPosition(150, 30);
	player->SetCamera(camera);
}

void DemoScene::Update(float dt)
{
	/*int x = camera->getX();
	int y = camera->getY();

	++x;
	++y;

	camera->setX(x);
	camera->setY(y);*/
	checkCollision(player, dt);

	player->HandleKeyboard(keys);
	player->Update(dt);
	//camera->moveCamera(player, dt);

	if (player->GetPosition().x - camera->getX() > 350 || camera->getX() - player->GetPosition().x > 350) {
		int t = 0;
	}

	string tmp = "Player: " + to_string(player->GetVx()*dt) + '\n';
	wstring t(tmp.begin(), tmp.end());
	const wchar_t* rs = t.c_str();
	DebugOut(rs);
}

void DemoScene::Draw()
{
	map->Draw();
	player->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;

	player->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;

	player->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}

float DemoScene::calEntryDistance(int x, int y, int p1, int p2, int speed, char option) {
	/*if (option == 'y') {
		return (speed < 0) ? (float)(y - (x + p1)) : (float)((y + p2) - x);
	}*/
	return (speed > 0) ? (float)(y - (x + p1)) : (float)((y + p2) - x);
}

float DemoScene::calExitDistance(int x, int y, int p1, int p2, int speed, char option) {
	return (speed > 0) ? (float)(y + p2) - x : (float)y - (x + p1);
}

float DemoScene::calEntryTime(float entryDistance, int speed) {
	return (!speed) ? -1e9 : entryDistance / speed;
}

float DemoScene::calExitTime(float exitDistance, int speed) {
	return (!speed) ? 1e9 : exitDistance / speed;
}

float DemoScene::Swept_AABB(Entity * object1, Entity * object2, int & normalX, int & normalY, float dt)
{
	float dxEntry, dyEntry, dxExit, dyExit;
	float txEntry, tyEntry, txExit, tyExit;
	float x1 = object1->GetPosition().x, moveX1 = object1->GetVx(), y1 = object1->GetPosition().y, moveY1 = object1->GetVy(), w1 = object1->GetWidth(), h1 = object1->GetHeight();
	float x2 = object2->GetPosition().x, moveX2 = object2->GetVx(), y2 = object2->GetPosition().y, moveY2 = object2->GetVy(), w2 = object2->GetWidth(), h2 = object2->GetHeight();

	dxEntry = calEntryDistance(x1, x2, w1, w2, moveX1, 'x');
	dyEntry = calEntryDistance(y1, y2, h1, h2, moveY1, 'y');

	dxExit = calExitDistance(x1, x2, w1, w2, moveX1, 'x');
	dyExit = calExitDistance(y1, y2, h1, h2, moveY1, 'y');

	txEntry = calEntryTime(dxEntry, moveX1);
	tyEntry = calEntryTime(dyEntry, moveY1);

	txExit = calExitTime(dxExit, moveX1);
	tyExit = calExitTime(dyExit, moveY1);

	if (object2->getID() == 37) {
		int tmp = 0;
	}

	float collisionEntryTime = max(txEntry, tyEntry);
	float collisionExitTime = min(txExit, tyExit);

	// if there was no collision
	if (collisionEntryTime > collisionExitTime || txEntry < 0.0f && tyEntry < 0.0f || txEntry > 1.0f || tyEntry > 1.0f) {
		normalX = 0;
		normalY = 0;

		return 1.5f;
	}
	// if there was a collision
	else {
		//calculate normal of collided surface
		if (txEntry > tyEntry) {
			if (dxEntry < 0.0f) {
				normalX = -1;
				normalY = 0;
			}
			else {
				normalX = 1;
				normalY = 0;
			}
		}
		else {
			if (dyEntry < 0.0f) {
				normalX = 0;
				normalY = 1;
			}
			else {
				normalX = 0;
				normalY = -1;
			}
		}

		return collisionEntryTime;
	}
}

Entity* DemoScene::GetSweptBroadphaseBox(Entity* object)
{
	Entity* broadphasebox = new Entity();
	D3DXVECTOR3 pos(object->GetVx() > 0 ? object->GetPosition().x : object->GetPosition().x + object->GetVx(), object->GetVy() > 0 ? object->GetPosition().y : object->GetPosition().y + object->GetVy(), 0);

	broadphasebox->SetPosition(pos);
	broadphasebox->SetWidth(object->GetVx() > 0 ? object->GetVx() + object->GetWidth() : object->GetWidth() - object->GetVx());
	broadphasebox->SetHeight(object->GetVy() > 0 ? object->GetVy() + object->GetHeight() : object->GetHeight() - object->GetVy());

	return broadphasebox;
}

bool DemoScene::AABBCheck(Entity * object1, Entity * object2)
{
	return !(object1->GetPosition().x + object1->GetWidth() < object2->GetPosition().x || object1->GetPosition().x > object2->GetPosition().x + object2->GetWidth() ||
		object1->GetPosition().y + object1->GetHeight() < object2->GetPosition().y || object1->GetPosition().y > object2->GetPosition().y + object2->GetHeight());
}

void DemoScene::checkCollision(Entity *object, float dt)
{
	/*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
	dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
	int widthBottom = 0;
	Entity* dummyObject = GetSweptBroadphaseBox(player);

	vector<Entity*> collisionableEntities;

	for (pair<int, int> cell : object->cellList) {
		vector<Entity*> tmp = map->getGrid()->getCellObject(cell.first, cell.second);

		for (Entity* object : tmp) {
			collisionableEntities.push_back(object);
		}
	}
	//mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);

	/*if (dummyObject->GetPosition().y <= 0 || dummyObject->getY() >= (SCREEN_HEIGHT - dummyObject->GetHeight())) {

	}*/

	Entity* collidedObject = NULL;
	float collisionTime = 1e9;
	int normalX, normalY;

	for (Entity* object : collisionableEntities) {
		/*if (object->getID() == 1) {
			continue;
		}*/
		/*string p = "object: " + to_string(object->getID()) + '\n';
		wstring pp(p.begin(), p.end());
		const wchar_t* r = pp.c_str();
		DebugOut(r);*/

		if (object->getID() == 39) {
			int temp = 0;
		}

		if (AABBCheck(dummyObject, object)) {
			float tmp = Swept_AABB(player, object, normalX, normalY, dt);



			if (collisionTime > tmp && tmp < dt) {
				collisionTime = tmp;
				collidedObject = object;

				break;
			}
		}
	}

	//return (AABBCheck(dummyObject, object));
	if (collidedObject) {
		/*string tmp = "Collision time: " + to_string(collisionTime) + " Object: " + to_string(collidedObject->getID()) + '\n';
		wstring t(tmp.begin(), tmp.end());
		const wchar_t* rs = t.c_str();
		DebugOut(rs);*/
		if (collidedObject->getID() == 39) {
			int tmp = 0;
		}

		player->Update(collisionTime);

		if (collisionTime <= dt) {
			player->OnCollision(normalX, normalY);

			if (player->getState() == PlayerState::Standing) {
				/*string tmp = "Standing surface: " + to_string(collidedObject->getID()) + '\n';
				wstring t(tmp.begin(), tmp.end());
				const wchar_t* rs = t.c_str();
				DebugOut(rs);*/

				player->standingSurface = collidedObject;
			}
			else if (player->getState() == PlayerState::Falling) {
				player->standingSurface = NULL;
			}
		}
	}

	if (player && player->standingSurface && player->GetPosition().x + player->GetWidth() < player->standingSurface->GetPosition().x) {
		int tmp = 0;
	}


	if (player->standingSurface && (player->getState() == PlayerState::Running || player->getState() == PlayerState::Standing)) {


		player->OnCollision();
	}

	//for (size_t i = 0; i < collisionableEntities.size(); i++)
	//{
	//	Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
	//		listCollision.at(i)->GetBound());

	//	if (r.IsCollided)
	//	{
	//		//lay phia va cham cua Entity so voi Player
	//		Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

	//		//lay phia va cham cua Player so voi Entity
	//		Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

	//		//goi den ham xu ly collision cua Player va Entity
	//		mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
	//		listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);

	//		//kiem tra neu va cham voi phia duoi cua Player 
	//		if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
	//			|| sidePlayer == Entity::BottomRight)
	//		{
	//			//kiem cha do dai ma mario tiep xuc phia duoi day
	//			int bot = r.RegionCollision.right - r.RegionCollision.left;

	//			if (bot > widthBottom)
	//				widthBottom = bot;
	//		}
	//	}
	//}

	//Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
	/*if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}*/
}