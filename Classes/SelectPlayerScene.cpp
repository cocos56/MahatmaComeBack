#include "SelectPlayerScene.h"


SelectPlayerScene* SelectPlayerScene::create(int type)
{
	SelectPlayerScene *pRet = new(std::nothrow) SelectPlayerScene(); \
		if (pRet && pRet->init(type)) \
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

Scene* SelectPlayerScene::createScene(int type)
{
	auto scene = Scene::create();
	auto layer = SelectPlayerScene::create(type);
	scene->addChild(layer);
	return scene;
}

bool SelectPlayerScene::init(int type)
{
	if (!Layer::init())
		return false;

	winSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("ui/selectPlayer.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	name = "";

	createLayer = Layer::create();

	selectLayer = Layer::create();

	this->addChild(createLayer);
	this->addChild(selectLayer);

	if (type == 1)
	{
		createPlayerLayer();
	}
	else
	{
		selectPlayerLayer();
	}

	


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* t,Event* e) {
		if (selectLayer->isVisible())
			return false;
		if (player1HeadUnselect->getBoundingBox().containsPoint(t->getLocation()))
		{
			player1HeadSelect->setVisible(true);
			player1HeadUnselect->setVisible(false);
			player2HeadSelect->setVisible(false);
			player2HeadUnselect->setVisible(true);

			player1->setVisible(true);
			player2->setVisible(false);
			playerType = 1;
		}
		if (player2HeadUnselect->getBoundingBox().containsPoint(t->getLocation()))
		{
			player1HeadSelect->setVisible(false);
			player1HeadUnselect->setVisible(true);
			player2HeadSelect->setVisible(true);
			player2HeadUnselect->setVisible(false);

			player1->setVisible(false);
			player2->setVisible(true);
			playerType = 2;
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();
	return true;
}

void SelectPlayerScene::createPlayerLayer()
{
	createLayer->setVisible(true);
	selectLayer->setVisible(false);

	auto font = Sprite::create("ui/createPlayerFont.png");
	font->setPosition(Vec2(winSize.width / 2, winSize.height -font->getContentSize().height+20));
	createLayer->addChild(font);

	player1 = Player::create(1);
	createLayer->addChild(player1);
	player1->setScale(3.5);
	player1->setPosition(Vec2(winSize.width / 3+100, winSize.height / 2));

	player2 = Player::create(2);
	createLayer->addChild(player2);
	player2->setScale(3.5);
	player2->setPosition(Vec2(winSize.width / 3+100, winSize.height / 2));
	player2->setVisible(false);

	playerType = 1;

	player1HeadSelect = Sprite::create("ui/player1Select.png");
	player1HeadSelect->setScale(0.5);
	player1HeadSelect->setPosition(Vec2(winSize.width * 2.7 / 4, winSize.height * 2 / 3));
	createLayer->addChild(player1HeadSelect);

	player1HeadUnselect = Sprite::create("ui/player1Unselect.png");
	player1HeadUnselect->setScale(0.5);
	player1HeadUnselect->setPosition(Vec2(winSize.width * 2.7 / 4, winSize.height * 2 / 3));
	createLayer->addChild(player1HeadUnselect);
	player1HeadUnselect->setVisible(false);

	player2HeadSelect = Sprite::create("ui/player2Select.png");
	player2HeadSelect->setScale(0.4);
	player2HeadSelect->setPosition(Vec2(player1HeadSelect->getPositionX()+ player1HeadSelect->getContentSize().width+15, player1HeadSelect->getPositionY()));
	createLayer->addChild(player2HeadSelect);
	player2HeadSelect->setVisible(false);

	player2HeadUnselect = Sprite::create("ui/player2Unselect.png");
	player2HeadUnselect->setScale(0.5);
	player2HeadUnselect->setPosition(Vec2(player1HeadSelect->getPositionX() + player1HeadSelect->getContentSize().width + 15, player1HeadSelect->getPositionY()));
	createLayer->addChild(player2HeadUnselect);

	auto playerNameFont = Sprite::create("ui/playerNameFont.png");
	playerNameFont->setPosition(Vec2(winSize.width / 2 - 150, 80));
	createLayer->addChild(playerNameFont);

	auto playerNameEdit = Sprite::create("ui/playerNameEdit.png");
	playerNameEdit->setPosition(Vec2(playerNameFont->getPositionX() + playerNameEdit->getContentSize().width + 5, playerNameFont->getPositionY()));
	createLayer->addChild(playerNameEdit);


	auto edit = EditBox::create(Size(141, 33), "");
	edit->setDelegate(this);
	edit->setFontColor(Color3B::RED);
	edit->setFontSize(13);
	edit->setInputMode(EditBox::InputMode::SINGLE_LINE);
	edit->setMaxLength(10);
	edit->setAnchorPoint(Vec2::ZERO);
	edit->setPosition(Vec2(3, 3));
	playerNameEdit->addChild(edit);


	auto createPlayerButton = Button::create("ui/createPlayerButton_normal.png", "ui/createPlayerButton_select.png");
	createPlayerButton->setPosition(Vec2(playerNameEdit->getPositionX() + playerNameEdit->getContentSize().width, playerNameEdit->getPositionY()));
	createPlayerButton->addTouchEventListener(CC_CALLBACK_2(SelectPlayerScene::callBack, this));
	createPlayerButton->setTag(10);
	createLayer->addChild(createPlayerButton);
}

void SelectPlayerScene::selectPlayerLayer()
{
	createLayer->setVisible(false);
	selectLayer->setVisible(true);

	int type = 1;
	if (SocketService::getInstance()->getPlayerType() == "2")
		type = 2;
	
	
	auto pl = Player::create(type);
	pl->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	selectLayer->addChild(pl);

	auto loginButton = Button::create("ui/loginGameScene_normal.png", "ui/loginGameScene_select.png");
	loginButton->setPosition(Vec2(winSize.width / 2, 100));
	loginButton->addTouchEventListener(CC_CALLBACK_2(SelectPlayerScene::callBack, this));
	loginButton->setTag(20);
	selectLayer->addChild(loginButton);
}

void SelectPlayerScene::update(float delta)
{
	auto str = SocketService::getInstance()->getMessage();
	if (str != "")
	{
		SocketService::getInstance()->setMessage("");
		auto messagetype = Tools::getInstance()->getStringFromJsonKey(str, "type");

		if (messagetype == "craetePlayerResult")
		{
			auto result = Tools::getInstance()->getStringFromJsonKey(str, "ifSuccess");
			if (result == "true")
			{
				//创建成功角色
				auto type = Tools::getInstance()->getStringFromJsonKey(str, "playerType");
				SocketService::getInstance()->setPlayerType(type);

				//跳转登录界面
				selectPlayerLayer();
			}
			else
			{
				//创建失败角色
				Tools::getInstance()->showTip(createLayer, Vec2(winSize.width / 2, 130), "playerNameError");
			}
		}
		if (messagetype == "playerInformation")
		{
			Director::getInstance()->replaceScene(GameScene::createScene(str));
		}
	}
}

void SelectPlayerScene::callBack(Ref* r, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto tag = ((Button*)r)->getTag();
		if (tag == 10)
		{
			//创建角色
			auto str = String::createWithFormat("{\"type\":\"createPlayer\",\"secretKey\":\"%s\",\"playerName\":\"%s\",\"playerType\":\"%d\" }",SocketService::getInstance()->getPrivatePassword().c_str() ,name.c_str(), playerType)->getCString();
			SocketService::getInstance()->sendMessage(str);
		}
		else
		{
			//登陆游戏
			auto str = String::createWithFormat("{\"type\":\"loginGameScene\",\"secretKey\":\"%s\" }", SocketService::getInstance()->getPrivatePassword().c_str())->getCString();
			SocketService::getInstance()->sendMessage(str);
		}
	}
}

void SelectPlayerScene::editBoxReturn(EditBox* editBox)
{

}

void SelectPlayerScene::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	name = text;
}
