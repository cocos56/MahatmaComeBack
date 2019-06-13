#pragma once
#include "cocos2d.h"
#include <string.h>
#include "Tools.h"
USING_NS_CC;
using namespace std;
class Player :public Sprite
{
public:
	enum class state
	{
		FREE = 0,
		WALK,
		ATTACK,
		DEAD
	};
	static Player* create(int type);

	static Player* createWithjson(string json);

	bool init(int type);

	bool initWithJson(string json);

	void setDirection(int direction);

	int getDirection();

	void freeAction();

	void walkAction();

	void attackAction();

	string getPlayerName();
public:
	string freeTextureFileName;
	string walkTextureFileName;
	string attackTextureFileName;
	state playerState;
	int playerDirection;
	Label* nameLabel;

	string playername;
	string playerType;
	float Xpoint;
	float Ypoint;
	int grade;
	float blood;
};

