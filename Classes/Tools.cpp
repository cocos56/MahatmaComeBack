#include "Tools.h"

Tools* Tools::tools = NULL;

Tools* Tools::getInstance()
{
	if (tools==NULL)
	{
		tools = new Tools();
	}
	return tools;
}

void Tools::delteInstance()
{
	if (tools)
	{
		delete tools;
		tools = NULL;
	}
}

void Tools::showTip(Layer* layer, Vec2 pos, string key)
{
	auto str = getChinese(key);
	auto label = Label::create(str.c_str(), "fonts/han.ttf", 25);
	label->setTag(2145);
	label->setColor(Color3B::BLACK);
	label->setPosition(pos);
	layer->addChild(label);

	auto fadeOut = FadeOut::create(3);

	auto callfun = CallFunc::create([&]() {
		auto label = (Label*)(layer->getChildByTag(2145));
		label->removeFromParentAndCleanup(true);
	});

	label->runAction(fadeOut);

}

std::string Tools::getChinese(string key)
{
	auto dic = Dictionary::createWithContentsOfFile("text.xml");
	auto str1 = ((String*)(dic->objectForKey(key)));
	return str1->getCString();
}

Animate* Tools::getAnimate(string framename, int loops, float delay)
{
	Vector<SpriteFrame*> sp;
	int index = 1;
	while (true)
	{
		auto str = String::createWithFormat("%s%d.png", framename.c_str(), index);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		if (frame == NULL)
			break;
		index++;
		sp.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(sp, delay, loops);
	animation->setRestoreOriginalFrame(true);
	auto animate = Animate::create(animation);
	return animate;
}

string Tools::getStringFromJsonKey(string json, string key)
{
	rapidjson::Document doc;
	doc.Parse<0>(json.c_str());
	auto str =(string)( doc[key.c_str()].GetString());

	return str;
}

float Tools::getFloatFromJsonKey(string json, string key)
{
	rapidjson::Document doc;
	doc.Parse<0>(json.c_str());
	auto f = (doc[key.c_str()].GetDouble());

	return f;
}

int Tools::getIntFromJsonKey(string json, string key)
{
	rapidjson::Document doc;
	doc.Parse<0>(json.c_str());
	auto i = (doc[key.c_str()].GetInt());

	return i;
}
void Tools::showMessageToListView(ListView* list, string name, string message)
{
	auto str = String::createWithFormat("%s:%s,", name.c_str(), message.c_str());
	auto text = Text::create(str->getCString(), "fonts/han.ttf", 16);
	text->setTextColor(Color4B::RED);
	text->setTextAreaSize(Size(list->getContentSize().width, 0));
	list->pushBackCustomItem(text);
	list->jumpToBottom();

}
