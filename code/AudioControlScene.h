#ifndef __AUDIO_CONTROL_SCENE_H__
#define __AUDIO_CONTROL_SCENE_H__
#include "cocos2d.h"

	class AudioControl : public cocos2d::Layer
{
public:
	//��cpp��û��'id'�����������Ƽ�������ʵ���㡣
	static cocos2d::Scene* createScene();

	//����һ������ cocos2d - x�еķ���'init'����bool����cocos2d - iphone�з���'id'
	virtual bool init();

	//һ��ѡ�����ص�
	void menuCloseCallback(cocos2d::Ref* pSender);

	//�ֶ�ʵʩ����̬create����������
	CREATE_FUNC(AudioControl);
};
#endif //__TEST_SCENE_H__