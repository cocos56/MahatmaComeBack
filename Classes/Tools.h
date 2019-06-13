#pragma once

#include "cocos2d.h"
#include <string.h>
#include "json/document.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace std;


class Tools
{
public:
	
	static Tools* tools;

	static Tools* getInstance();

	static void delteInstance();

public:

	void showTip(Layer* layer, Vec2 pos, string key);

	string getChinese(string key);

	Animate* getAnimate(string framename, int loops, float delay);

	string getStringFromJsonKey(string json, string key);

	float getFloatFromJsonKey(string json, string key);

	int getIntFromJsonKey(string json, string key);

	void showMessageToListView(ListView* list,string name, string message);
};

