#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ShortestPathStep :public Ref
{
public:
	static ShortestPathStep *createWithPosition(Vec2 pos);
	bool initWithPosition(Vec2 pos);
	void setPosition(Vec2 point);
	Vec2 getPosition();
	void setG(int g);
	void setH(int h);
	int getG();
	int getH();
	int getFScore();
	void setParent(ShortestPathStep* par);
	ShortestPathStep* getParent();
	bool isEqual(const ShortestPathStep *other);
	std::string getDescription();
private:
	int G;
	int H;
	Vec2 point;
	ShortestPathStep* parent;
};

