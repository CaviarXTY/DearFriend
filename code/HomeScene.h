#ifndef __HOMESCENE_SCENE_H__
#define __HOMESCENE_SCENE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"

	USING_NS_CC;
using namespace cocos2d;
using namespace std;

class HomeScene : public cocos2d::Layer
{
	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	Size visbleSize;
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	Vec2 origin;
	//��Ϸ֡������
	int _count;
	//�н����루���ã�
	int distance = 10;
	//�н���������ã�
	int moveDelay = 10;
	//��ť����
	bool b_up, b_down, b_left, b_right;
	bool _isText;//�Ƿ�Ի���
	bool _isFlash;//������
				  //��ͼ
	TMXTiledMap *_tileMap2;
	//�ϰ���
	TMXLayer *_collidable;
	//��Ҿ���
	Sprite *_player;
	Sprite *_npc;
	Sprite *_get;
	Sprite *_get2;
	Sprite *_To;
	//����
	Sprite _backgroundC;

	//�Ի���ͼƬ
	Sprite *_kuang;
	//�Ի����ı�-����
	Label *_name;
	//�Ի����ı�-����
	Label *_text;
	//�����߼�¼��
	int _num;
	//����ֵ
	int _numScene;
	//�Ի�����
	string str[40];

public:
	//����ʵ��
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();

	//��ʱ��
	void update(float delta);

	//��OPenGL����ת����TileMap����
	Vec2 tileCoordForPosition(Vec2 position);

	//������ҽ��ƶ�λ��
	Vec2 willMove(int Tag);
	//���㾵ͷλ��
	Vec2 getPositionNow(Vec2 position);
	//����
	void playerFlash();
	//���+��ͼ����
	void playerMove(int tag);
	//�Ի���
	void showText(std::string name, std::string said, bool visble);
	//��ȡObject��������
	Vec2 getObjectByName(std::string Layername, std::string name);

	//������Ӧ�¼�
	void keyListener(EventKeyboard::KeyCode keycode, bool set);

	Animate* getAnimateByName(std::string animName, float delay, int animNum);

	//��ײ������
	bool onContactBegin(Sprite* s);

	bool onTouch(Vec2 posistion);


	CREATE_FUNC(HomeScene);
};
#endif __HOMESCENE_SCENE_H__