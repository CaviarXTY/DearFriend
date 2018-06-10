#ifndef __BAG_SCENE_H__
#define __BAG_SCENE_H__
#include "cocos2d.h"
#pragma execution_character_set("utf-8")
USING_NS_CC;
using namespace cocos2d;

class BagScene : public cocos2d::Layer
{
private:
	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	Size visbleSize;
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	Vec2 origin;
	//������Դ
	Sprite *_background;
	//����ֵ
	int _numScene;
	//������Ʒ
	Sprite *_s[4];

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
	//�Ƿ���ʾ
	bool _isText;
	bool page[4];
	bool have;

	//Label *label;//ȫ�ֱ���Label->��ʾ��ײ��δ��ײ(ע�ⲻ����auto�ؼ���)
public:
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();

	//�Ի���
	void showText(std::string name, std::string said, bool visble);

	CREATE_FUNC(BagScene);
};
#endif __BAG_SCENE_H__