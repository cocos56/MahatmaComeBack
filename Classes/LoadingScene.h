#ifndef ____LOADINGSCENE_____
#define ____LOADINGSCENE_____

#include "cocos2d.h"
#include <iostream>
#include <vector>
#include "ui/CocosGUI.h"
using namespace std;
USING_NS_CC;
using namespace ui;
class LoadingScene :public Layer
{
public:
	float totalnumber;        //总共要加载的资源数目
	float alreadynumber;      //已经加载的资源数目
	vector<string> audioPath; //存放声音资源的数目
	vector<string> plistPath;  //存放plist资源路径的容器
	vector<string> pngPath;    //存放png资源路径的容器
	ProgressTimer* loadingbar; //进度条变量
public:
	CREATE_FUNC(LoadingScene);

	static Scene* createScene();

	bool init();

	void callBack(Texture2D* texture);

	void plistCallBack(Texture2D* texture, int i);
	
};

#endif // ____LOADINGSCENE_____