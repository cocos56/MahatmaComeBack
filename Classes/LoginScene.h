#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tools.h"
#include "SocketService.h"
#include "SelectPlayerScene.h"

USING_NS_CC;
using namespace ui;
class LoginScene :public Layer,public EditBoxDelegate
{
public:
	CREATE_FUNC(LoginScene);

	static Scene* createScene();

	bool init();

	void initLoginLayer();//³õÊ¼»¯µÇÂ¼´°¿Ú

	void initSelectServiceLayer();//³õÊ¼»¯Ñ¡Ôñ·şÎñÆ÷´°¿Ú

	void initRegisterLayer();  //³õÊ¼»¯×¢²á²ã

	void update(float delta);

	virtual void editBoxReturn(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);

	void callBack(Ref* r, Widget::TouchEventType type);
public:
	Size size;
	EditBox* accountEdit;//ÕËºÅÊäÈë¿ò
	EditBox* passwordEdit;//ÃÜÂëÊäÈë¿ò
	Layer* loginLayer;    //µÇÂ½²ã
	Layer* SelectServiceLayer;//Ñ¡Ôñ·şÎñÆ÷²ã
	Layer* registerLayer;   //×¢²á²ã
	string accountStr;    //´æ´¢ÕËºÅ×Ö·û´®
	string passwordStr;   //´æ´¢ÃÜÂë×Ö·û´®

};

