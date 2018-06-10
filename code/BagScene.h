#ifndef __BAG_SCENE_H__
#define __BAG_SCENE_H__
#include "cocos2d.h"
#pragma execution_character_set("utf-8")
USING_NS_CC;
using namespace cocos2d;

class BagScene : public cocos2d::Layer
{
private:
	//获得设备支持得可见OpenGL视图大小
	Size visbleSize;
	//获得可见OpenGL视图的起源点（默认0，0）
	Vec2 origin;
	//背景资源
	Sprite *_background;
	//场景值
	int _numScene;
	//背包物品
	Sprite *_s[4];

	//对话框图片
	Sprite *_kuang;
	//对话框文本-名字
	Label *_name;
	//对话框文本-内容
	Label *_text;

	//游戏帧计数器
	int _count;
	//计位器
	int num;
	//是否显示
	bool _isText;
	bool page[4];
	bool have;

	//Label *label;//全局变量Label->显示碰撞与未碰撞(注意不能用auto关键字)
public:
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();

	//对话框
	void showText(std::string name, std::string said, bool visble);

	CREATE_FUNC(BagScene);
};
#endif __BAG_SCENE_H__