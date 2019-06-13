#include "LoadingScene.h"
#include "loginScene.h";
#include"Tools.h"


Scene* LoadingScene::createScene()
{
	auto scene=Scene::create();
	auto layer=LoadingScene::create();
	scene->addChild(layer);
	return scene;
}


bool LoadingScene::init()
{
	if(!Layer::init())
	    return false;

	auto size = Director::getInstance()->getVisibleSize();

	//添加进度条背景
	auto bg = Sprite::create("ui/loadingbg.png");
	bg->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bg);

	//添加正在加载动画
	auto animation = Animation::create();
	for (int i = 1; i < 5;i++)
	{
		auto str = String::createWithFormat("ui/loading_%d.png",i);
		animation->addSpriteFrameWithFile(str->getCString());
	}
	animation->setDelayPerUnit(0.4);
	animation->setLoops(-1);

	auto jiazai = Sprite::create();
	jiazai->runAction(Animate::create(animation));
	jiazai->setPosition(Vec2(size.width / 2, size.height / 2 + jiazai->getContentSize().height+30));
	addChild(jiazai);

	//添加进度条
	loadingbar = ProgressTimer::create(Sprite::create("ui/loading.png"));
	loadingbar->setType(ProgressTimer::Type::BAR);
	loadingbar->setMidpoint(Vec2(0, 1));
	loadingbar->setBarChangeRate(Vec2(1, 0));
	loadingbar->setPercentage(0);
	loadingbar->setPosition(Vec2(size.width / 2, size.height/2));
	addChild(loadingbar);

	//把所有的plist文件的名称，存入plistPath
	plistPath.push_back("player/player1");
	plistPath.push_back("player/player2");

	//把所有的单个png资源，存入pngPath
	pngPath.push_back("ui/startBG.jpg");
	pngPath.push_back("ui/1.png");
	pngPath.push_back("ui/back_Service_normal.png");
	pngPath.push_back("ui/back_Service_select.png");
	pngPath.push_back("ui/EditBox.png");
	pngPath.push_back("ui/login.png");
	pngPath.push_back("ui/login_Button_normal.png");
	pngPath.push_back("ui/login_Button_select.png");
	pngPath.push_back("ui/ok_Button_normal.png");
	pngPath.push_back("ui/ok_Button_select.png");
	pngPath.push_back("ui/selectServiceBox.png");
	pngPath.push_back("ui/selectServiceFont.png");
	pngPath.push_back("ui/selectPlayer.png");

	//初始化一些变量
	alreadynumber = 0;
	totalnumber = pngPath.size() + plistPath.size() + audioPath.size();


	//异步加载所有的png资源
	for (int i = 0; i < pngPath.size(); i++)
	{
		TextureCache::getInstance()->addImageAsync(pngPath.at(i), CC_CALLBACK_1(LoadingScene::callBack, this));
	}
	

	//异步加载plist
	for (int i = 0; i < plistPath.size(); i++)
	{
		TextureCache::getInstance()->addImageAsync(plistPath.at(i) + ".png", CC_CALLBACK_1(LoadingScene::plistCallBack, this, i));
	}

	return true;
}

void LoadingScene::callBack( Texture2D* texture )
{
	alreadynumber++;
	auto percent = (alreadynumber / totalnumber) * 100;
	loadingbar->setPercentage(percent);
	if (alreadynumber >= totalnumber)
		Director::getInstance()->replaceScene(LoginScene::createScene());
}

void LoadingScene::plistCallBack(Texture2D* texture, int i)
{
	alreadynumber++;
	auto percent = (alreadynumber / totalnumber) * 100;
	loadingbar->setPercentage(percent);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath.at(i) + ".plist",plistPath.at(i)+".png");
	if (alreadynumber >= totalnumber)
		Director::getInstance()->replaceScene(LoginScene::createScene());
}