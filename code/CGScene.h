#ifndef __CG_SCENE_H__
#define __CG_SCENE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class CGScene : public cocos2d::Layer
{
private:
	//������Դ
	Sprite *_background;
	//�Ի���ͼƬ
	Sprite *_kuang;
	//�Ի����ı�-����
	Label *_name;
	//�Ի����ı�-����
	Label *_text;
	//��Ϸ֡������
	int _count;
	//ʱ��
	int _delay;
	//�����߼�¼��
	int _num;
	//����ֵ
	int _numScene;

public:
	//����ʵ��
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();

	//��ʱ��
	//void update(float delta);

	//��ʱ����
	void delayTime(int sec,bool isRelay);

	//�Ի���
	void showText(std::string name, std::string said, bool visble);
	CREATE_FUNC(CGScene);
};
#endif __CG_SCENE_H__