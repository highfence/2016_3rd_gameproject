#include "pch.h"
#include "ManageMove.h"
#include "ManageMap.h"
#include "TemporaryDefine.h"


auto backgroundPosition = Vec2(0.f,0.f);

bool ManageMove::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	scheduleUpdate();
	return true;
}



Vec2 ManageMove::update(Vec2 position,Vec2 background, Vec2 unitVec,TMXTiledMap* map)
{
	m_manageMap = ManageMap::create();
	
	auto movable = false;
	auto checkChangeMap =  false;
	backgroundPosition = background;

	checkChangeMap = m_manageMap->checkChangeMap(position -(map->getMapSize()), map);
	if (checkChangeMap == true)
	{
		return position;
	}


	movable = m_manageMap->checkWall(position + unitVec * 16,map);
	
	if (movable == true)
	{
		position = setCharacterPosition(position, unitVec,map);
	}

	map->setPosition(background);

	return position;

}

Vec2 ManageMove::setCharacterPosition(Vec2 position, Vec2 unitVec,TMXTiledMap* map)
{
	
	auto backgroundMovable = false;

	backgroundMovable = checkBackgroundMovable(position, unitVec,map);
	
	if (backgroundMovable == true)
	{
		return position;
	}
	return position + unitVec*(map->getTileSize().width/2);
}

bool ManageMove::checkBackgroundMovable(Vec2 position, Vec2 unitVec,TMXTiledMap* map)
{
	auto backgroundXMovable = false;
	auto backgroundYMovable = false;

	auto winSize = Director::getInstance()->getWinSize();

	if (unitVec.x < 0)
	{
		if (backgroundPosition.x < 0 && position.x <= winSize.width / 2)
		{
			backgroundPosition.x += TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundXMovable = true;
		}
		else
		{
			if (backgroundPosition.x > 0)
			{
				backgroundPosition.x = 0;
			}
			unitVec + Vec2(-TEMP_DEFINE::CHACRACTER_MOVE_SPEED, 0);
			if (position.x - TEMP_DEFINE::CHACRACTER_MOVE_SPEED < 16)
			{
				unitVec.x = 0;
			}
		}
	}
	else if (unitVec.x > 0)
	{
		if (backgroundPosition.x > -(map->getMapSize().width * 32 - winSize.width) && position.x >= winSize.width / 2)
		{
			backgroundPosition.x -= TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundXMovable = true;
		}
		else
		{
			if (backgroundPosition.x <= -(map->getMapSize().width * 32 - winSize.width))
			{
				backgroundPosition.x = -(map->getMapSize().width * 32 - winSize.width);
			}
			unitVec + Vec2(TEMP_DEFINE::CHACRACTER_MOVE_SPEED, 0);
			if (position.x + TEMP_DEFINE::CHACRACTER_MOVE_SPEED >= winSize.width)
			{
				unitVec.x = 0;
			}
		}
	}

	if (unitVec.y < 0)
	{
		if (backgroundPosition.y < 0 && position.y <= winSize.height / 2)
		{
			backgroundPosition.y += TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundYMovable = true;
		}
		else
		{
			if (backgroundPosition.y > 0)
			{
				backgroundPosition.y = 0;
			}
			unitVec + Vec2(0,-TEMP_DEFINE::CHACRACTER_MOVE_SPEED);
			if (position.y - TEMP_DEFINE::CHACRACTER_MOVE_SPEED < 16)
			{
				unitVec.y = 0;
			}
		}
	}
	else if (unitVec.y > 0)
	{
		if (backgroundPosition.y > -(map->getMapSize().height * 32 - winSize.height) && position.y >= winSize.height / 2)
		{
			backgroundPosition.y -= TEMP_DEFINE::MAP_MOVE_SPEED;
			backgroundYMovable = true;
		}
		else
		{
			if (backgroundPosition.y <= -(map->getMapSize().height * 32 - winSize.height))
			{
				backgroundPosition.y = -(map->getMapSize().height * 32 - winSize.height);
			}
			unitVec + Vec2(0,TEMP_DEFINE::CHACRACTER_MOVE_SPEED);
			if (position.y + TEMP_DEFINE::CHACRACTER_MOVE_SPEED >= winSize.height)
			{
				unitVec.y = 0;
			}
		}
	}


	if (backgroundXMovable && backgroundYMovable)
	{
		return true;
	}

	return false;
}