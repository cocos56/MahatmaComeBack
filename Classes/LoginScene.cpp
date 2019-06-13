#include "LoginScene.h"

Scene* LoginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}


bool LoginScene::init()
{
	if (!Layer::init())
		return false;

	accountStr = "";
	passwordStr = "";

    size = Director::getInstance()->getVisibleSize();

	//Ìí¼Ó±³¾°
	auto bg = Sprite::create("ui/startBG.jpg");
	bg->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bg);

	initSelectServiceLayer();//³õÊ¼»¯Ñ¡Ôñ·þÎñÆ÷²ã
	initLoginLayer();//³õÊ¼»¯µÇÂ½²ã£»
	initRegisterLayer();//³õÊ¼»¯×¢²á²ã£»

	scheduleUpdate();

	return true;
}

void LoginScene::initLoginLayer()
{
	loginLayer = Layer::create();
	loginLayer->setAnchorPoint(Vec2::ZERO);
	loginLayer->setPosition(Vec2(0, size.height));
	addChild(loginLayer);

	auto login_bg = Sprite::create("ui/login.png");
	login_bg->setPosition(Vec2(443, 425));
	loginLayer->addChild(login_bg);

	//Ìí¼ÓÕËºÅ±à¼­¿ò
	accountEdit = EditBox::create(Size(183, 22), "EditBox.png");
	accountEdit->setDelegate(this);
	accountEdit->setFontColor(Color3B::BLACK);
	accountEdit->setFontSize(17);
	accountEdit->setInputMode(EditBox::InputMode::SINGLE_LINE);
	accountEdit->setMaxLength(12);
	accountEdit->setTag(101);
	accountEdit->setAnchorPoint(Vec2::ZERO);
	accountEdit->setPosition(Vec2(152, 99));
	login_bg->addChild(accountEdit);

	//Ìí¼ÓÃÜÂë±à¼­¿ò
	passwordEdit = EditBox::create(Size(183, 22), "EditBox.png");
	passwordEdit->setDelegate(this);
	passwordEdit->setFontColor(Color3B::BLACK);
	passwordEdit->setTag(102);
	passwordEdit->setInputMode(EditBox::InputMode::SINGLE_LINE);
	passwordEdit->setInputFlag(EditBox::InputFlag::PASSWORD);
	passwordEdit->setMaxLength(12);
	passwordEdit->setAnchorPoint(Vec2::ZERO);
	passwordEdit->setPosition(Vec2(152, 74));
	login_bg->addChild(passwordEdit);



	auto regi = Button::create("ui/register_normal.png", "ui/register_select.png");
	regi->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBack, this));
	regi->setTag(6);
	regi->setAnchorPoint(Vec2::ZERO);
	regi->setScale9Enabled(true);
	regi->setScale(0.6);
	regi->setPosition(Vec2(338,88));
	login_bg->addChild(regi);


	auto login_Button = Button::create("ui/login_Button_normal.png", "ui/login_Button_select.png");
	login_Button->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBack, this));
	login_Button->setPosition(Vec2(login_bg->getPositionX()+login_Button->getContentSize().width/2, login_bg->getPositionY() - login_bg->getContentSize().height / 2));
	login_Button->setTag(1);
	loginLayer->addChild(login_Button);

	auto back_Button = Button::create("ui/back_Service_normal.png", "ui/back_Service_select.png");
	back_Button->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBack, this));
	back_Button->setPosition(Vec2(login_bg->getPositionX() - login_bg->getContentSize().width / 4, login_Button->getPositionY()));
	back_Button->setTag(3);
	loginLayer->addChild(back_Button);
}

void LoginScene::initSelectServiceLayer()
{
	SelectServiceLayer = Layer::create();
	SelectServiceLayer->setAnchorPoint(Vec2::ZERO);
	addChild(SelectServiceLayer);

	auto selectbg = Sprite::create("ui/selectServiceBox.png");
	selectbg->setPosition(Vec2(size.width / 2 , size.height / 2 + selectbg->getContentSize().height / 7));
	SelectServiceLayer->addChild(selectbg);

	auto selectFont = Sprite::create("ui/selectServiceFont.png");
	selectFont->setPosition(Vec2(selectbg->getPositionX()+10, selectbg->getPositionY() + selectbg->getContentSize().height / 2 + selectFont->getContentSize().height / 2));
	SelectServiceLayer->addChild(selectFont);


	auto s = Button::create("ui/1.png");
	s->setPosition(Vec2(80, 250));
	selectbg->addChild(s);

	auto okButton = Button::create("ui/ok_Button_normal.png", "ui/ok_Button_select.png");
	okButton->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBack, this));
	okButton->setTag(2);
	okButton->setScale(1.3);
	okButton->setPosition(Vec2(selectbg->getPositionX(), selectbg->getPositionY() - selectbg->getContentSize().height / 2-okButton->getContentSize().height));
	SelectServiceLayer->addChild(okButton);


}

void LoginScene::initRegisterLayer()
{
	registerLayer = Layer::create();
	registerLayer->setAnchorPoint(Vec2::ZERO);
	registerLayer->setPosition(Vec2(0, size.height));
	addChild(registerLayer);

	auto bg = Sprite::create("ui/register_bg.png");
	bg->setPosition(Vec2(443, 425));
	registerLayer->addChild(bg);

	//Ìí¼ÓÕËºÅ±à¼­¿ò
	accountEdit = EditBox::create(Size(183, 22), "EditBox.png");
	accountEdit->setDelegate(this);
	accountEdit->setFontColor(Color3B::BLACK);
	accountEdit->setFontSize(17);
	accountEdit->setInputMode(EditBox::InputMode::SINGLE_LINE);
	accountEdit->setMaxLength(12);
	accountEdit->setTag(103);
	accountEdit->setAnchorPoint(Vec2::ZERO);
	accountEdit->setPosition(Vec2(152, 99));
	bg->addChild(accountEdit);

	//Ìí¼ÓÃÜÂë±à¼­¿ò
	passwordEdit = EditBox::create(Size(183, 22), "EditBox.png");
	passwordEdit->setDelegate(this);
	passwordEdit->setFontColor(Color3B::BLACK);
	passwordEdit->setTag(104);
	passwordEdit->setInputMode(EditBox::InputMode::SINGLE_LINE);
	passwordEdit->setInputFlag(EditBox::InputFlag::PASSWORD);
	passwordEdit->setMaxLength(12);
	passwordEdit->setAnchorPoint(Vec2::ZERO);
	passwordEdit->setPosition(Vec2(152, 74));
	bg->addChild(passwordEdit);

	auto register_Button = Button::create("ui/register_normal.png", "ui/register_select.png");
	register_Button->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBack, this));
	register_Button->setPosition(Vec2(bg->getPositionX() + register_Button->getContentSize().width / 2, bg->getPositionY() - bg->getContentSize().height / 2));
	register_Button->setTag(5);
	registerLayer->addChild(register_Button);

	auto back_Button = Button::create("ui/back_normal.png", "ui/back_select.png");
	back_Button->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBack, this));
	back_Button->setPosition(Vec2(bg->getPositionX() - bg->getContentSize().width / 4, register_Button->getPositionY()));
	back_Button->setTag(4);
	registerLayer->addChild(back_Button);
}

void LoginScene::update(float delta)
{
	auto str = SocketService::getInstance()->getMessage();
	if (str!= "")
	{
		SocketService::getInstance()->setMessage("");
		auto messagetype = Tools::getInstance()->getStringFromJsonKey(str, "type");

		if (messagetype == "registerResult")
		{
			auto result = Tools::getInstance()->getStringFromJsonKey(str, "reason");
			if (result == "true")
			{
				//×¢²á³É¹¦
				Tools::getInstance()->showTip(this, Vec2(size.width / 2 - 30, size.height / 2 + 5), "registerTrue");
			}
			else
			{
				//×¢²áÊ§°Ü
				Tools::getInstance()->showTip(this, Vec2(size.width / 2 - 30, size.height / 2 + 5), "registerFalse");
			}
		}

		if(messagetype=="loginResult")
		{
			auto result = Tools::getInstance()->getStringFromJsonKey(str, "ifloginSuccess");
			if (result == "true")
			{
				//µÇÂ½³É¹¦
				auto privatePass = Tools::getInstance()->getStringFromJsonKey(str, "privatePassword");
				SocketService::getInstance()->setPrivatePassword(privatePass);

				SocketService::getInstance()->setAccount(accountStr);

				auto name= Tools::getInstance()->getStringFromJsonKey(str, "playerName");
				if (name == "")
				{

					Director::getInstance()->replaceScene(SelectPlayerScene::createScene(1));
				}
				else
				{
					SocketService::getInstance()->setPlayerType(Tools::getInstance()->getStringFromJsonKey(str, "playerType"));
					Director::getInstance()->replaceScene(SelectPlayerScene::createScene(2));
				}
			}
			if (result == "false")
			{
				//µÇÂ¼Ê§°Ü
				if (Tools::getInstance()->getStringFromJsonKey(str, "reason") == "NoAccount")
				{
					//ÕËºÅ²»´æÔÚ
					Tools::getInstance()->showTip(this, Vec2(size.width / 2 - 30, size.height / 2 + 5), "NoAccount");
				}
				else if (Tools::getInstance()->getStringFromJsonKey(str, "reason") == "PasswordError")
				{
					//ÃÜÂë´íÎó
					Tools::getInstance()->showTip(this, Vec2(size.width / 2 - 30, size.height / 2 + 5), "PasswordError");
				}
			}
		}
	}
}

void LoginScene::editBoxReturn(EditBox* editBox)
{

}

void LoginScene::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	auto tag = editBox->getTag();
	if (tag == 101)
	{
		accountStr = text;
	}
	else if (tag == 102)
	{
		passwordStr = text;
	}
	else if (tag == 103)
	{
		accountStr = text;
	}
	else if (tag == 104)
	{
		passwordStr = text;
	}
}

void LoginScene::callBack(Ref* r, Widget::TouchEventType type)
{
	if (type==Widget::TouchEventType::ENDED)
	{
		auto tag = ((Button*)r)->getTag();
		if (tag == 1)//µÇÂ¼°´Å¥
		{
			if (accountStr==""||passwordStr=="")
			{
				Tools::getInstance()->showTip(this, Vec2(size.width / 2-30, size.height / 2+5), "isempty");
			}
			auto str = String::createWithFormat("{\"type\":\"login\",\"account\":\"%s\",\"password\":\"%s\"}", accountStr.c_str(), passwordStr.c_str())->getCString();
			SocketService::getInstance()->sendMessage(str);
			
		}
		if (tag == 2)//È·¶¨µÇÂ½·þÎñÆ÷
		{
			SocketService::getInstance()->initSocket();
			auto moveby1 = MoveBy::create(0.3, Vec2(0, 0 - size.height));
			auto moveby2 = MoveBy::create(0.3, Vec2(0, 0 - size.height));

			loginLayer->setPosition(Vec2(0, size.height));

			SelectServiceLayer->runAction(moveby1);
			loginLayer->runAction(moveby2);
		}
		if (tag == 3)//·µ»Ø·þÎñÆ÷ÁÐ±í
		{
			SocketService::getInstance()->delteInstance();
			auto moveby1 = MoveBy::create(0.3, Vec2(0, 0 - size.height));
			auto moveby2 = MoveBy::create(0.3, Vec2(0, 0 - size.height));

			SelectServiceLayer->setPosition(Vec2(0, size.height));

			SelectServiceLayer->runAction(moveby1);
			loginLayer->runAction(moveby2);
		}
		if (tag == 4)//·µ»ØµÇÂ¼´°¿Ú
		{

			auto moveby1 = MoveBy::create(0.3, Vec2(0, 0 - size.height));
			auto moveby2 = MoveBy::create(0.3, Vec2(0, 0 - size.height));

			loginLayer->setPosition(Vec2(0, size.height));

			registerLayer->runAction(moveby1);
			loginLayer->runAction(moveby2);

			accountStr = "";
			passwordStr = "";
		}
		if (tag == 5)//Á¢¼´×¢²á°´Å¥
		{
			if (accountStr == "" || passwordStr == "")
				Tools::getInstance()->showTip(this, Vec2(size.width / 2 - 30, size.height / 2 + 5), "isempty");
			else
			{
				auto str = String::createWithFormat("{\"type\":\"register\",\"account\":\"%s\",\"password\":\"%s\"}", accountStr.c_str(), passwordStr.c_str())->getCString();
				SocketService::getInstance()->sendMessage(str);
			}
		}
		if (tag == 6)//½øÈëÔÚ×¢²á²ã
		{
			accountStr = "";
			passwordStr = "";

			auto moveby1 = MoveBy::create(0.3, Vec2(0, 0 - size.height));
			auto moveby2 = MoveBy::create(0.3, Vec2(0, 0 - size.height));

			registerLayer->setPosition(Vec2(0, size.height));

			registerLayer->runAction(moveby1);
			loginLayer->runAction(moveby2);
		}
	}
}
