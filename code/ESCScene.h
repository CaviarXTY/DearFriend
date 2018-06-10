#ifndef __ESC_SCENE_H__
#define __ESC_SCENE_H__
#include "cocos2d.h"

	USING_NS_CC;
using namespace cocos2d;

class ESCScene : public cocos2d::Layer
{
private:
	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	Size visbleSize;
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	Vec2 origin;
	//������Դ
	Sprite *_background;

	Sprite *_s[5];

	//�Ի���ͼƬ
	Sprite *_kuang;
	//�Ի����ı�-����
	Label *_name;
	//�Ի����ı�-����
	Label *_text;

	//��Ϸ֡������
	int _count;
	//��λ��
	int num;
	bool page[5];
	bool have;

	//Label *label;//ȫ�ֱ���Label->��ʾ��ײ��δ��ײ(ע�ⲻ����auto�ؼ���)
public:
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();

	CREATE_FUNC(ESCScene);
};
#endif __ESC_SCENE_H__