#include "BagScene.h"
#include "TwoScene.h"
#include "DBUtil.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
USING_NS_CC;
using namespace ui;
using namespace std;

Scene* BagScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BagScene::create();
	scene->addChild(layer);
	return scene;
}

//�ڡ�init()������Ҫ��ʼ�����ʵ��
bool BagScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	num = 0;
	_numScene = 0;
	page[0] = false;
	page[1] = false;
	page[2] = false;
	page[3] = false;
	_isText = false;
	have = true;

	//��ʼ��ֵ
	DBUtil::initDB("gamedata.db");
	int *b= DBUtil::getTable("select * from gamedata");
	DBUtil::closeDB();

	//��ȡ��¼�ļ�
	ifstream loadin("origin.txt");   //����
	char ch[450];
	while (!loadin.eof()) {//���û�ж�ȡ���ļ��ļ�β��
		loadin.getline(ch, 20);
		_numScene = atoi(ch);
	}
	loadin.close();

	if (_numScene > 3) {
		page[0] = true;
	}
	if (_numScene > 8) {
		page[1] = true;
	}
	if(_numScene > 10) {
		page[2] = true;
	}


	//������ʱ��update����
	scheduleUpdate();

	if (_numScene == 12) {
		num = 2;
	}
	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	visbleSize = Director::getInstance()->getVisibleSize();
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	origin = Director::getInstance()->getVisibleOrigin();

	/************************************************* ���� ******************************************************/
	//��������
	_background = Sprite::create("background0.png");
	//����λ�ã��м�
	_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//�������λ���м�
	_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//��������Ӧ��С
	_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //���þ��������ű���  
	_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//���þ���߶����ű���  
																						//�������Ϊ��ǰ���ӽڵ�
	this->addChild(_background, 0);

	/************************************************* ��ť ******************************************************/
	//��ť
	auto left_button = Button::create("/page/left.png");
	//left_button->setScale(2);
	left_button->setAnchorPoint(Vec2(0.5, 0.5));
	left_button->setPosition(Vec2(origin.x+visbleSize.width/8,origin.y+visbleSize.height/2));
	left_button->addTouchEventListener([this](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			if (have) {
				_s[num]->setOpacity(0);
				if (num == 0) {
					for (int i = 3;i >= 0;i--)
						if (page[i]) {
							num = i;
							break;
						}
				}
				else 
					num--;
				log("%d", num);
				_s[num]->setOpacity(100);
			}
		}
	});
	this->addChild(left_button, 1);

	//�Ұ�ť
	auto right_button = Button::create("/page/right.png");
	//right_button->setScale(2);
	right_button->setAnchorPoint(Vec2(0.5, 0.5));
	right_button->setPosition(Vec2(origin.x + visbleSize.width*7 / 8, origin.y + visbleSize.height / 2));
	right_button->addTouchEventListener([this](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			if (have) {
				_s[num]->setOpacity(0);
				if (num == 3)
					num = 0;
				else {
					if (page[num + 1])
						num++;
					else
						num = 0;
				}
				log("%d", num);
				_s[num]->setOpacity(100);
			}
		}
	});
	this->addChild(right_button, 1);

	//���ذ�ť
	auto back_button = Button::create("");
	back_button->setScale(2);
	back_button->setTitleText("back");
	back_button->setTitleFontName("Arial");
	back_button->setTitleFontSize(5);
	back_button->setPosition(Vec2(origin.x + back_button->getContentSize().width * 3, origin.y + visbleSize.height - back_button->getContentSize().height * 3));
	back_button->addTouchEventListener([this](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			if (_numScene==12) {
				auto transition = TransitionFade::create(1.0, LoadingScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
			else {
				Director::getInstance()->popScene();
			}
		}
	});
	this->addChild(back_button, 1);

	/************************************************* �� ******************************************************/

	_kuang = Sprite::create("kuang.png");
	_kuang->setAnchorPoint(Vec2(0, 0));
	_kuang->setScaleX(visbleSize.width / _kuang->getTextureRect().getMaxX());
	_kuang->setScaleY((visbleSize.height*0.4) / _kuang->getTextureRect().getMaxY());
	_kuang->setOpacity(0);
	this->addChild(_kuang, 3);

	_name = Label::createWithSystemFont("", "Marker Felt", 10);
	_name->setAnchorPoint(Vec2(0, 0));
	_name->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.35));
	this->addChild(_name, 2);

	_text = Label::createWithSystemFont("", "Marker Felt", 10);
	_text->setAnchorPoint(Vec2(0, 0));
	_text->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.30));
	this->addChild(_text, 2);

	/************************************************* ��Ʒ ******************************************************/
	_s[0] = Sprite::create("/bag/dao.png");
	_s[0]->setOpacity(100);
	_s[0]->setScale(0.5);
	_s[0]->setAnchorPoint(Vec2(0.5, 0.5));
	_s[0]->setPosition(Vec2(origin.x + visbleSize.width/2, origin.y + visbleSize.height / 2));
	this->addChild(_s[0]);

	_s[1] = Sprite::create("/bag/book.png");
	_s[1]->setOpacity(0);
	_s[1]->setScale(0.5);
	_s[1]->setAnchorPoint(Vec2(0.5, 0.5));
	_s[1]->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2));
	this->addChild(_s[1]);
	
	_s[2] = Sprite::create("/bag/clother.png");
	_s[2]->setOpacity(0);
	_s[2]->setScale(0.5);
	_s[2]->setAnchorPoint(Vec2(0.5, 0.5));
	_s[2]->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2));
	this->addChild(_s[2]);

	_s[3] = Sprite::create("/bag/tongji.png");
	_s[3]->setOpacity(0);
	_s[3]->setScale(0.5);
	_s[3]->setAnchorPoint(Vec2(0.5, 0.5));
	_s[3]->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2));
	this->addChild(_s[3]);

	/************************************************ ���� ******************************************************/
	//�����¼����������������¼�
	auto myKeyListener = EventListenerKeyboard::create();
	//���̰�������ʱ����Ӧ
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		CCLOG("key is pressed, keycode is %d", keycode);

	};
	//���̰�������ʱ����Ӧ
	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
			if (num == 0) {
				if (!_isText) {
					showText("��������", "��������ӡ�����ھӼҵĵ��Ӻ���", true);
					_isText = true;
				}
				else {
					showText("", "", false);
					_isText = false;
				}
			}
			else if (num == 1) {
				if (!_isText) {
					showText("���ӵ��ռ�", "������Ȼ���������Ų��������Ĺ�ϵ", true);
					_isText = true;
				}
				else {
					showText("", "", false);
					_isText = false;
				}
			}
			else if (num == 2) {
				if (!_isText) {
					showText("��Ѫ����", "�������������ǣ����в���Ѫ����������װ������", true);
					_isText = true;
				}
				else {
					showText("", "", false);
					_isText = false;
				}
			}
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	return true;
}

//�Ի���
void BagScene::showText(std::string name, std::string said, bool visble) {
	if (visble) {
		log("true");
		_kuang->setOpacity(70);
		_name->setString(name);
		_text->setString(said);
	}
	else {
		_kuang->setOpacity(0);
		_name->setString("");
		_text->setString("");
	}
}




