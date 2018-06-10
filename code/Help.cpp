#include "Help.h"
#include "ESCScene.h"
#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
USING_NS_CC;
using namespace ui;
using namespace std;


Scene* HelpScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

//�ڡ�init()������Ҫ��ʼ�����ʵ��
bool HelpScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	auto visbleSize = Director::getInstance()->getVisibleSize();
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	auto origin = Director::getInstance()->getVisibleOrigin();

	/************************************************* ���� ******************************************************/
	//��������
	auto _background = Sprite::create("background0.png");
	//����λ�ã��м�
	_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//�������λ���м�
	_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//��������Ӧ��С
	_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //���þ��������ű���  
	_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//���þ���߶����ű���  
																						//�������Ϊ��ǰ���ӽڵ�
	this->addChild(_background, 0);

	/********************************************** ���ذ�ť ***************************************************/
	auto back_button = Button::create("");
	back_button->setScale(2);
	back_button->setTitleText("back");
	back_button->setTitleFontName("Arial");
	back_button->setTitleFontSize(5);
	back_button->setPosition(Vec2(origin.x + back_button->getContentSize().width * 3, origin.y + visbleSize.height - back_button->getContentSize().height * 3));
	back_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->popScene();
		}
	});
	this->addChild(back_button, 1);

	/************************************************* ͼƬ ******************************************************/
	Sprite *s1 = Sprite::create("fx.png");
	s1->setScale(0.5);
	s1->setAnchorPoint(Vec2(0.5, 0.5));
	s1->setPosition(Vec2(visbleSize.width / 5 + origin.x, visbleSize.height * 2 / 3 + origin.y));
	this->addChild(s1);

	Sprite *s2 = Sprite::create("space.png");
	s2->setScale(0.5);
	s2->setAnchorPoint(Vec2(0.5, 0.5));
	s2->setPosition(Vec2(visbleSize.width * 3 / 7 + origin.x, visbleSize.height * 2 / 3 + origin.y));
	this->addChild(s2);


	/************************************************* ���� ******************************************************/
	Label *l1 = Label::createWithSystemFont("����", "Marker Felt", 10);
	l1->setAnchorPoint(Vec2(0.5, 0.5));
	l1->setPosition(Vec2(visbleSize.width / 5 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l1);

	Label *l2 = Label::createWithSystemFont("�Ի�/�鿴/����", "Marker Felt", 10);
	l2->setAnchorPoint(Vec2(0.5, 0.5));
	l2->setPosition(Vec2(visbleSize.width * 3 / 7 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l2);

	Label *l3 = Label::createWithSystemFont("��ͣ", "Marker Felt", 10);
	l3->setAnchorPoint(Vec2(0.5, 0.5));
	l3->setPosition(Vec2(visbleSize.width * 4 / 6 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l3);

	Label *l4 = Label::createWithSystemFont("����", "Marker Felt", 10);
	l4->setAnchorPoint(Vec2(0.5, 0.5));
	l4->setPosition(Vec2(visbleSize.width * 5 / 6 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l4);

	return true;
}
