#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "SocketService.h"
#include "ui/CocosGUI.h"
#include "string.h"
#include "GameScene.h"

USING_NS_CC;
using namespace ui;
using namespace std;
class SelectPlayerScene :public Layer,public EditBoxDelegate
{
public:
	static SelectPlayerScene* create(int type);

	static Scene* createScene(int type);

	bool init(int type);

	void createPlayerLayer();

	void selectPlayerLayer();

	void update(float delta);

	void callBack(Ref* r, Widget::TouchEventType type);

	virtual void editBoxReturn(EditBox* editBox);

	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);

public:
	Size winSize;

	string name;

	Layer* createLayer;

	Layer* selectLayer;

	int playerType;

	Sprite* player1;
	Sprite* player2;
	
	Sprite* player1HeadUnselect;
	Sprite* player2HeadUnselect;
	Sprite* player1HeadSelect;
	Sprite* player2HeadSelect;
};

