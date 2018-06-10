#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__
#include "cocos2d.h"
#pragma execution_character_set("utf-8")
	USING_NS_CC;
using namespace cocos2d;

class LoadingScene : public cocos2d::Layer
{
private:
	//背景资源
	Sprite * _background;
	//加载中图片
	Sprite *_loadSprite;
	//对话框文本-名字
	Label *_loadLabel;

public:
	//创建实例
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();

	CREATE_FUNC(LoadingScene);
};
#endif __LOADING_SCENE_H__