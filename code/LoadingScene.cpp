#include "LoadingScene.h"
#include "CGScene.h"
#include "HomeScene.h"
#include "TwoScene.h"
#include "HelloWorldScene.h"
#include "HouseScene.h"
#include "JinJuScene.h"
#include "SuSeScene.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
USING_NS_CC;
using namespace ui;
using namespace std;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

//�ڡ�init()������Ҫ��ʼ�����ʵ��
bool LoadingScene::init()
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

	/************************************************ ���� ******************************************************/
	Label *l5 = Label::createWithSystemFont("���ո����", "Marker Felt", 10);
	l5->setAnchorPoint(Vec2(0.5, 0.5));
	l5->setPosition(Vec2(visbleSize.width * 7 / 8 + origin.x, visbleSize.height / 10 + origin.y));
	this->addChild(l5);

	/************************************************* ת�� ******************************************************/
	ifstream in("origin.txt");   //����
	char ch[20];
	int a = 0;
    	while (!in.eof()) {
		//���û�ж�ȡ���ļ��ļ�β��
		in.getline(ch, 20);
		a = atoi(ch);
	}
	in.close();


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
			if (a == 1 || a == 3 || a == 6 || a == 10 || a == 12 || a == 13 || a == 14 ) {
				auto transition = TransitionFade::create(1.0, CGScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
			else if(a == 2 || a == 11){
				auto transition = TransitionFade::create(1.0, SuSeScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
			else if (a == 4) {
				auto transition = TransitionFade::create(1.0, JinJuScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
			else if (a == 5 || a == 7 ) {
				auto transition = TransitionFade::create(1.0, HomeScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
			else if (a == 15) {
				
				//����
				auto audioengine = SimpleAudioEngine::getInstance();
				audioengine->preloadBackgroundMusic("Cold Feet.mp3");
				SimpleAudioEngine::getInstance()->playBackgroundMusic("Cold Feet.mp3", true);

				//��������
				auto _background = Sprite::create("Scene/Scene15.png");
				//����λ�ã��м�
				_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
				//�������λ���м�
				_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				//��������Ӧ��С
				_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //���þ��������ű���  
				_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//���þ���߶����ű���  
																									//�������Ϊ��ǰ���ӽڵ�
				this->addChild(_background, 0);

				//������ǩ�����ݣ����壬�ֺţ�
				auto label = LabelTTF::create("THE END", "Arial", 24);
				//����λ�ã�����
				label->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2));
				//��ǩ���Ϊ��ǰ���ӽڵ�
				this->addChild(label, 1);
				//�������˵�
				auto back_button2 = Button::create("");
				back_button2->setScale(2);
				back_button2->setTitleText("�������˵�");
				back_button2->setTitleFontName("Arial");
				back_button2->setTitleFontSize(5);
				back_button2->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2 - label->getContentSize().height * 2));
				back_button2->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
					if (type == Widget::TouchEventType::ENDED) {
						//�ر�����
						SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
						auto transition = TransitionFade::create(2.0, HelloWorld::createScene());
						Director::getInstance()->replaceScene(transition);
					}
				});
				this->addChild(back_button2, 1);
			}
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	//CCScene *psecond = CGScene::createScene();
	//CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(3.0f, psecond));
	return true;
}
