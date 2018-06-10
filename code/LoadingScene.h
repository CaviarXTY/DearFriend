#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__
#include "cocos2d.h"
#pragma execution_character_set("utf-8")
	USING_NS_CC;
using namespace cocos2d;

class LoadingScene : public cocos2d::Layer
{
private:
	//������Դ
	Sprite * _background;
	//������ͼƬ
	Sprite *_loadSprite;
	//�Ի����ı�-����
	Label *_loadLabel;

public:
	//����ʵ��
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();

	CREATE_FUNC(LoadingScene);
};
#endif __LOADING_SCENE_H__