#include "ShortestPathStep.h"


ShortestPathStep * ShortestPathStep::createWithPosition(Vec2 pos)
{
	ShortestPathStep *pRet = new ShortestPathStep();
	if (pRet && pRet->initWithPosition(pos))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete(pRet);
		pRet = nullptr;
		return nullptr;
	}
}

bool ShortestPathStep::initWithPosition(Vec2 pos)
{
	this->setPosition(pos);
	G = 0;
	return true;
}

void ShortestPathStep::setPosition(Vec2 point)
{
	this->point = point;
}

cocos2d::Vec2 ShortestPathStep::getPosition()
{
	return this->point;
}

void ShortestPathStep::setG(int g)
{
	this->G = g;
}

void ShortestPathStep::setH(int h)
{
	this->H = h;
}

int ShortestPathStep::getG()
{
	return G;
}

int ShortestPathStep::getH()
{
	return H;
}

int ShortestPathStep::getFScore()
{
	return getG() + getH();
}

void ShortestPathStep::setParent(ShortestPathStep* par)
{
	this->parent = par;
}

ShortestPathStep* ShortestPathStep::getParent()
{
	return this->parent;
}

bool ShortestPathStep::isEqual(const ShortestPathStep *other)
{
	return this->point == other->point;
}

std::string ShortestPathStep::getDescription()
{
	return StringUtils::format("pos=[%f;%f]  g=%d  h=%d  f=%d",
		this->getPosition().x, this->getPosition().y,
		this->getG(), this->getH(), this->getFScore());
}
