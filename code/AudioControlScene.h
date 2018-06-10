#ifndef __AUDIO_CONTROL_SCENE_H__
#define __AUDIO_CONTROL_SCENE_H__
#include "cocos2d.h"

	class AudioControl : public cocos2d::Layer
{
public:
	//在cpp中没有'id'，所以我们推荐返回类实例点。
	static cocos2d::Scene* createScene();

	//这是一个区别。 cocos2d - x中的方法'init'返回bool，在cocos2d - iphone中返回'id'
	virtual bool init();

	//一个选择器回调
	void menuCloseCallback(cocos2d::Ref* pSender);

	//手动实施“静态create（）”方法
	CREATE_FUNC(AudioControl);
};
#endif //__TEST_SCENE_H__