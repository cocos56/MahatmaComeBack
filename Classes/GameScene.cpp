#include "GameScene.h"


GameScene* GameScene::create(string json)
{
	GameScene *pRet = new(std::nothrow) GameScene(); \
		if (pRet && pRet->init(json)) \
		{ \
			pRet->autorelease(); \
			return pRet; \
		} \
		else \
		{ \
			delete pRet; \
			pRet = nullptr; \
			return nullptr; \
		} \
}

Scene* GameScene::createScene(string json)
{
	auto scene = Scene::create();
	auto layer = GameScene::create(json);
	scene->addChild(layer);
	return scene;
}

bool GameScene::init(string json)
{
	if (!Layer::init())
		return false;

	auto size = Director::getInstance()->getVisibleSize();

	map = TMXTiledMap::create("map.tmx");
	map->setPosition(Vec2::ZERO);
	map->setAnchorPoint(Vec2::ZERO);
	this->addChild(map);

	player = Player::createWithjson(json);
	map->addChild(player);

	this->setPosition(moveMap(player->getPosition()));


	SocketService::getInstance()->sendMessage(String::createWithFormat("{\"type\":\"nearPlayers\",\"secretKey\":\"%s\"}", SocketService::getInstance()->getPrivatePassword().c_str())->getCString());


	//添加聊天窗口
	messageNode = CSLoader::createNode("Layer.csb");
	messageNode->setPosition(Vec2(0 - this->getPositionX(), 0 - this->getPositionY()));
	this->addChild(messageNode);
	listview = (ListView*)(messageNode->getChildByTag(5));
	auto messageEdit = EditBox::create(Size(210, 36), "edit.png");
	messageEdit->setDelegate(this);
	messageEdit->setFontColor(Color3B::RED);
	messageEdit->setFontSize(17);
	messageEdit->setMaxLength(15);
	messageEdit->setInputMode(EditBox::InputMode::SINGLE_LINE);
	messageEdit->setAnchorPoint(Vec2::ZERO);
	messageEdit->setPosition(Vec2(20,70));
	messageNode->addChild(messageEdit);


	auto sendButton = (Button*)(messageNode->getChildByTag(8));
	sendButton->addTouchEventListener(CC_CALLBACK_2(GameScene::sendMessageCallBack, this));

	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	listen->onTouchEnded = [&](Touch* touch, Event* event) {


		moveTowardPoint(map->convertToNodeSpace(touch->getLocation()));

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);

	scheduleUpdate();
	return true;
}

void GameScene::updatePlayerDirection(Vec2 point)
{
	//判断英雄的朝向
	auto  angle= atan2(player->getPositionX()-point.x, player->getPositionY()-point.y);
	angle = angle*(180.0 / 3.1415926);
		if (angle < 0) {
			//在左边  
			if (angle > -15) {
				player->setDirection(1);//面向上  
			}
			if (angle <= -15 && angle >= -75) {
				player->setDirection(6);//面向右上  
			}
			if (angle < -75 && angle >= -105) {
				player->setDirection(7);//面向右  
			}
			if (angle < -105 && angle >= -165) {
				player->setDirection(8);//面向右下  
			}
			if (angle < -165) {
				player->setDirection(5);//面向下  
			}
		}
		else {
			//在右边     
			if (angle >= 75 && angle <= 105) {
				player->setDirection(3);//面向左边  
			}
			if (angle >= 15 && angle < 75) {
				player->setDirection(4);//面向左上  
			}
			if (angle < 15) {
				player->setDirection(1);//面向上  
			}
			if (angle > 105 && angle < 165) {
				player->setDirection(2);//面向左下  
			}
			if (angle > 165) {
				player->setDirection(5);//面向下  
			}
		}
}

void GameScene::moveTowardPoint(Vec2 point)
{
	auto startTileCoorrd = tileCoordForPosition(player->getPosition() + Vec2(0, 64));
	auto targetTileCoord = tileCoordForPosition(point);
	if (startTileCoorrd == targetTileCoord)
		return;
	if (isWallAtTileCoord(tileCoordForPosition(point)))
		return;
	log("From:%f,%f", startTileCoorrd.x, startTileCoorrd.y);
	log("To:%f,%f", targetTileCoord.x, targetTileCoord.y);

	bool pathfound = false;
	openSteps.clear();
	closeSteps.clear();
	insertInOpenSteps(ShortestPathStep::createWithPosition(startTileCoorrd));
	do
	{
		ShortestPathStep* temp = openSteps.at(0);
		closeSteps.pushBack(temp);
		openSteps.erase(0);
		openSteps.clear();
		if (temp->getPosition() == targetTileCoord)
		{
			pathfound = true;
			break;
		}

		auto points = walkableAdjacentTilesCoordForTileCoord(temp->getPosition());
		for (int j = 0; j < points.size(); j++)
		{
			auto step = ShortestPathStep::createWithPosition(points.at(j));
			if (getStepIndex(closeSteps, step) != -1)
				continue;
			int moveconst = costToMoveFromStepToAdjacentStep(temp, step);
			auto index = getStepIndex(openSteps, step);
			if (index == -1)
			{
				step->setParent(temp);
				step->setG(temp->getG() + moveconst);
				step->setH(computeHScoreFromCoordToCoord(step->getPosition(), targetTileCoord));
				insertInOpenSteps(step);
			}
			else
			{
				step = openSteps.at(index);
				if ((temp->getG() + moveconst) < step->getG())
				{
					step->setG(temp->getG() + moveconst);
					step->setH(computeHScoreFromCoordToCoord(step->getPosition(), targetTileCoord));
					step->retain();
					openSteps.erase(index);
					insertInOpenSteps(step);
				}
			}
		}

	} while (openSteps.size() > 0);

	if (pathfound)
	{
		closeSteps.erase(0);
		player->stopAllActions();
		playAnimate();
	}

	for (int i = 0; i < closeSteps.size(); i++)
	{
		log("%s", closeSteps.at(i)->getDescription().c_str());
	}
}

cocos2d::Vec2 GameScene::tileCoordForPosition(Vec2 point)
{
	int x = ((int)point.x) / ((int)map->getTileSize().width);
	int y = ((int)((map->getTileSize().height*map->getMapSize().height) - point.y)) / ((int)map->getTileSize().height);
	return Vec2(x, y);
}

bool GameScene::isWallAtTileCoord(Vec2 tilecoord)
{
	auto gid = map->getLayer("collision")->getTileGIDAt(tilecoord);
	if (gid)
	{
		return true;
	}
	return false;
}

cocos2d::Vec2 GameScene::moveMap(Vec2 point)
{
	int x = MAX(point.x, Director::getInstance()->getVisibleSize().width / 2);
	int y = MAX(point.y, Director::getInstance()->getVisibleSize().height / 2);
	x = MIN(x, map->getMapSize().width*map->getTileSize().width - Director::getInstance()->getVisibleSize().width / 2);
	y = MIN(y, map->getMapSize().height*map->getTileSize().height - Director::getInstance()->getVisibleSize().height / 2);

	auto centPoint = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	return Vec2(centPoint - Vec2(x, y));
}

void GameScene::insertInOpenSteps(ShortestPathStep* step)
{
	//将一个点插入到open表中
	int f = step->getFScore();
	int count = openSteps.size();
	int i = 0;
	for (; i < count; i++)
	{
		if (f <= openSteps.at(i)->getFScore())
			break;
	}
	openSteps.insert(i, step);
}

int GameScene::computeHScoreFromCoordToCoord(Vec2 fromCoord, Vec2 toCoord)
{
	//使用曼哈顿最短路径，计算两个块之间的最短路径
	return abs(fromCoord.x - toCoord.x) + abs(fromCoord.y - toCoord.y);
}

int GameScene::costToMoveFromStepToAdjacentStep(ShortestPathStep *fromStep, ShortestPathStep *toStep)
{
	return 1;
}

std::vector<cocos2d::Vec2> GameScene::walkableAdjacentTilesCoordForTileCoord(Vec2 tileCoord)
{
	vector<Vec2> points;
	Vec2 p(tileCoord.x, tileCoord.y - 1);
	//上
	if (!this->isWallAtTileCoord(p))
	{
		points.push_back(p);
	}
	//左
	p.setPoint(tileCoord.x - 1, tileCoord.y);
	if (!this->isWallAtTileCoord(p))
	{
		points.push_back(p);
	}
	// 下
	p.setPoint(tileCoord.x, tileCoord.y + 1);
	if (!this->isWallAtTileCoord(p))
	{
		points.push_back(p);
	}
	// 右
	p.setPoint(tileCoord.x + 1, tileCoord.y);
	if (!this->isWallAtTileCoord(p))
	{
		points.push_back(p);
	}
	return points;
}

int GameScene::getStepIndex(Vector<ShortestPathStep*> steps, ShortestPathStep* step)
{
	for (int i = 0; i < steps.size(); i++)
	{
		if (steps.at(i)->isEqual(step))
			return i;
	}
	return -1;
}

void GameScene::playAnimate()
{
	if (closeSteps.size() == 0)
	{
		player->freeAction();
		//向客户端发送处于空闲状态
		auto json = String::createWithFormat("{\"type\":\"position\",\"secretKey\":\"%s\",\"state\":\"free\"}", SocketService::getInstance()->getPrivatePassword().c_str())->getCString();
		SocketService::getInstance()->sendMessage(json);
		return;
	}
		

	auto point = map->getLayer("collision")->getPositionAt(closeSteps.at(0)->getPosition());
	updatePlayerDirection(point);
	player->walkAction();
	//向服务器发送人物坐标
	auto json = String::createWithFormat("{\"type\":\"position\",\"secretKey\":\"%s\",\"state\":\"walk\",\"XPoint\":%f,\"YPoint\":%f,\"direction\":%d}",SocketService::getInstance()->getPrivatePassword().c_str(), point.x, point.y,player->getDirection())->getCString();
	SocketService::getInstance()->sendMessage(json);

	auto move = MoveTo::create(0.4,point);
	auto call = CallFunc::create([&]() {
		playAnimate();
	});

	closeSteps.erase(0);

	player->runAction(Sequence::create(move, call, NULL));
}

void GameScene::editBoxReturn(EditBox* editBox)
{

}

void GameScene::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	message = text;
}

void GameScene::sendMessageCallBack(Ref* r, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Tools::getInstance()->showMessageToListView(listview, player->getPlayerName(), message);
		auto json = String::createWithFormat("{\"type\":\"message\",\"secretKey\":\"%s\",\"message\":\"%s\",\"playerName\":\"%s\"}", SocketService::getInstance()->getPrivatePassword().c_str(),message.c_str(),player->getPlayerName().c_str())->getCString();
		SocketService::getInstance()->sendMessage(json);
	}
}

void GameScene::update(float delta)
{
	//处理地图视角
	if (player->playerState == Player::state::WALK)
	{
		auto pos = moveMap(player->getPosition());
		this->setPosition(pos);
		messageNode->setPosition(Vec2(0-pos.x,0-pos.y));
	}
	//处理从服务器接收到的数据
	auto str = SocketService::getInstance()->getMessage();
	if (str != "")
	{
		SocketService::getInstance()->setMessage("");
		auto messagetype = Tools::getInstance()->getStringFromJsonKey(str, "type");
		if (messagetype == "nearPlayer")//当要更新周围玩家的信息的时候
		{
			auto name = Tools::getInstance()->getStringFromJsonKey(str, "playerName");
			for (int i = 0; i < nearplayers.size(); i++)
			{
				auto nearPlayer = (Player*)(nearplayers.at(i));
				if (name == nearPlayer->getPlayerName())
				{
					auto nearState = Tools::getInstance()->getStringFromJsonKey(str, "state");

					//当前玩家退出游戏的时候
					if (nearState == "remove")
					{
						nearPlayer->removeFromParentAndCleanup(true);
						nearplayers.eraseObject(nearPlayer);
						return;
					}

					//没有退出游戏的时候
					auto nearDirection = Tools::getInstance()->getIntFromJsonKey(str, "direction");
					auto XPoint = Tools::getInstance()->getFloatFromJsonKey(str, "XPoint");
					auto YPoint = Tools::getInstance()->getFloatFromJsonKey(str, "YPoint");


					if (nearState == "free")
					{
						nearPlayer->freeAction();
					}
					else
					{
						nearPlayer->setDirection(nearDirection);
						nearPlayer->walkAction();
						nearPlayer->runAction(MoveTo::create(0.4, Vec2(XPoint, YPoint)));
					}

				}
				return;
			}
			auto nearState = Tools::getInstance()->getStringFromJsonKey(str, "state");
			auto n = Player::createWithjson(str);
			if (nearState == "walk")
			{
				n->walkAction();
			}
			else
			{
				n->freeAction();
			}
			this->addChild(n);
			nearplayers.pushBack(n);
		}

		if (messagetype == "message")//当接收到要显示的消息的时候
		{
			auto name = Tools::getInstance()->getStringFromJsonKey(str, "playerName");
			auto message = Tools::getInstance()->getStringFromJsonKey(str, "message");
			Tools::getInstance()->showMessageToListView(listview, name, message);
		}
	}
}