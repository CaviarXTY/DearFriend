#ifndef __CG_SCENE_H__
#define __CG_SCENE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class CGScene : public cocos2d::Layer
{
private:
	//背景资源
	Sprite *_background;
	//对话框图片
	Sprite *_kuang;
	//对话框文本-名字
	Label *_name;
	//对话框文本-内容
	Label *_text;
	//游戏帧计数器
	int _count;
	//时延
	int _delay;
	//故事线记录器
	int _num;
	//场景值
	int _numScene;

public:
	//创建实例
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();

	//定时器
	//void update(float delta);

	//延时函数
	void delayTime(int sec,bool isRelay);

	//对话框
	void showText(std::string name, std::string said, bool visble);
	CREATE_FUNC(CGScene);
};
#endif __CG_SCENE_H__