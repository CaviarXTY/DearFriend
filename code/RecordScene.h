#ifndef __RECORD_SCENE_H__
#define __RECORD_SCENE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"
USING_NS_CC;
using namespace ui;
class RecordScene : public cocos2d::Layer
{
private:
	//获得设备支持得可见OpenGL视图大小
	Size visbleSize;
	//获得可见OpenGL视图的起源点（默认0，0）
	Vec2 origin;
public:
	//there's no 'id' in cpp ,so we recomend returning the class instance point.
	static cocos2d::Scene* createScene();

	//Here's a difference. Method  'init' in cocos2d-x returns bool ,intead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void update(float delta);

	void newRecord(Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(RecordScene);
};

#endif  __RECORD_SCENE_H__
