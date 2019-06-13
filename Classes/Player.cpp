#include "Player.h"


Player* Player::create(int type)
{
	Player* player = new Player();
	if (player&&player->init(type))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

Player* Player::createWithjson(string json)
{
	Player* player = new Player();
	if (player&&player->initWithJson(json))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player::init(int type)
{
	if (!Sprite::init())
		return false;

	if (type == 1)
	{
		freeTextureFileName = "nas";
		attackTextureFileName = "nza";
		walkTextureFileName = "nz";
		grade = 1;
	}
	else if (type == 2)
	{
		freeTextureFileName = "qks";
		attackTextureFileName = "qka";
		walkTextureFileName = "qk";
		grade = 1;
	}
	playerState = Player::state::FREE;
	playerDirection = 1;
	this->setAnchorPoint(Vec2(0.5,0.5));
	this->freeAction();
	this->setScale(5);
	return true;
}

bool Player::initWithJson(string json)
{
	//通过json文件初始化角色
	if (!Sprite::init())
		return false;

	playername = Tools::getInstance()->getStringFromJsonKey(json, "playerName");
	playerType = Tools::getInstance()->getStringFromJsonKey(json, "playerType");
	Xpoint = Tools::getInstance()->getFloatFromJsonKey(json, "XPoint");
	Ypoint = Tools::getInstance()->getFloatFromJsonKey(json, "YPoint");
	grade = Tools::getInstance()->getIntFromJsonKey(json, "grade");
	blood = Tools::getInstance()->getFloatFromJsonKey(json, "blood");
	auto direction= Tools::getInstance()->getIntFromJsonKey(json, "direction");


	if (playerType == "1")
	{
		freeTextureFileName = "nas";
		attackTextureFileName = "nza";
		walkTextureFileName = "nz";
		grade = 1;
	}
	else if (playerType == "2")
	{
		freeTextureFileName = "qks";
		attackTextureFileName = "qka";
		walkTextureFileName = "qk";
		grade = 1;
	}
	playerState = Player::state::FREE;
	playerDirection = direction;
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->freeAction();
	this->setScale(1.5);
	this->setPosition(Vec2(Xpoint, Ypoint));

	nameLabel = Label::create(playername.c_str(), "fonts/han.ttf", 15);
	nameLabel->setPosition(Vec2(50, 150));
	nameLabel->setColor(Color3B::BLACK);
	this->addChild(nameLabel);


	return true;
}

void Player::setDirection(int direction)
{
	playerDirection = direction;
}

int Player::getDirection()
{
	return playerDirection;
}

void Player::freeAction()
{
	this->stopAllActions();
	playerState = state::FREE;
	auto str = String::createWithFormat("%s_%d_00", freeTextureFileName.c_str(), playerDirection)->getCString();
	auto animate = RepeatForever::create(Tools::getInstance()->getAnimate(str, 1, 0.3));
	this->runAction(animate);
}

void Player::walkAction()
{
	this->stopAllActions();
	playerState = state::WALK;
	auto str = String::createWithFormat("%s_%d_00", walkTextureFileName.c_str(), playerDirection)->getCString();
	auto animate = RepeatForever::create(Tools::getInstance()->getAnimate(str, 1, 0.1));
	this->runAction(animate);
}

void Player::attackAction()
{
	this->stopAllActions();
	playerState = state::ATTACK;
	auto str = String::createWithFormat("%s_%d_00", attackTextureFileName.c_str(), playerDirection)->getCString();
	auto animate = RepeatForever::create(Tools::getInstance()->getAnimate(str, 1, 0.04));
	this->runAction(animate);
}

std::string Player::getPlayerName()
{
	return playername;
}
