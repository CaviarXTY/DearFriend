#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;
class HelpScene : public cocos2d::Layer
{
public:
	//创建实例
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();
	//对话框
	void showText(std::string name, std::string said, bool visble);

	CREATE_FUNC(HelpScene);
};

#endif __HELP_SCENE_H__