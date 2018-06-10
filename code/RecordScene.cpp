#include "RecordScene.h"
#include "LoadingScene.h"
#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
USING_NS_CC;
using namespace ui;
using namespace std;
Scene* RecordScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RecordScene::create();
	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool RecordScene::init()
{
	//////////////////////////////
	// 1. super init first
	// ���ø���init����
	if (!Layer::init())
	{
		return false;
	}

	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	visbleSize = Director::getInstance()->getVisibleSize();
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	origin = Director::getInstance()->getVisibleOrigin();


	//this->runAction(MoveBy::create(2.0, Vec2(0, visbleSize.height)));


	//����
	Sprite* sprite = Sprite::create("Record.png");
	//����λ�ã��м�
	sprite->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//�������λ���м�
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//��������Ӧ��С
	sprite->setScaleX(visbleSize.width / sprite->getTextureRect().getMaxX()); //���þ��������ű���  
	sprite->setScaleY(visbleSize.height / sprite->getTextureRect().getMaxY());//���þ���߶����ű���  
																			  //�������Ϊ��ǰ���ӽڵ�
	this->addChild(sprite, 0);



	auto label = Label::createWithSystemFont("�Ƿ�ʼ�¼�¼", "Marker Felt", 50);
	label->setPosition(Vec2(visbleSize.width / 2 + origin.x, origin.y - visbleSize.height*0.4));
	this->addChild(label);//ֱ�Ӱ�Label��ʾ����Ļ��


	////��ť
	//auto test_button = Button::create("R1-1.png");
	////�������λ���м�
	//test_button->setAnchorPoint(Vec2(0, 0));
	//test_button->setPosition(Vec2(visbleSize.width * 0.368 + origin.x, visbleSize.height * 0.675 + origin.y));
	//test_button->setScaleX(visbleSize.width / sprite->getTextureRect().getMaxX()); //���ÿ�����ű���  
	//test_button->setScaleY(visbleSize.height / sprite->getTextureRect().getMaxY());//���ø߶����ű���  
	//test_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
	//	if (type == Widget::TouchEventType::ENDED) {
	//		auto transition = TransitionFade::create(1.0, TwoScene::createScene());
	//		Director::getInstance()->replaceScene(transition);
	//	}
	//});
	//this->addChild(test_button, 1);

	auto closeItem = MenuItemImage::create("R1-1.png", "R1-1.png", CC_CALLBACK_1(RecordScene::newRecord, this));


	closeItem->setAnchorPoint(Vec2::ZERO);
	closeItem->setPosition(Vec2(visbleSize.width * 0.368 + origin.x, visbleSize.height * 0.675 + origin.y));
	closeItem->setScaleX(visbleSize.width / sprite->getTextureRect().getMaxX()); //���ÿ�����ű���  
	closeItem->setScaleY(visbleSize.height / sprite->getTextureRect().getMaxY());//���ø߶����ű���  
	//this->addChild(closeItem, 1);

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	//ȷ�ϰ�ť
	auto sure_button = Button::create("");
	sure_button->setTitleText("��");
	sure_button->setTitleFontName("Arial");
	sure_button->setTitleFontSize(15);
	sure_button->setPosition(Vec2(visbleSize.width / 2 + origin.x, origin.y - visbleSize.height*0.6));
	sure_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			ofstream out("origin.txt");
			out << 1;
			out.close();
			auto transition = TransitionFade::create(1.0, LoadingScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(sure_button, 1);

	//��ť
	auto no_button = Button::create("");
	no_button->setTitleText("��");
	no_button->setTitleFontName("Arial");
	no_button->setTitleFontSize(15);
	no_button->setPosition(Vec2(visbleSize.width / 2 + origin.x, origin.y - visbleSize.height*0.68));
	no_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(1.0, LoadingScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(no_button, 1);


	//���ذ�ť
	auto back_button = Button::create("");
	back_button->setScale(2);
	back_button->setTitleText("back");
	back_button->setTitleFontName("Arial");
	back_button->setTitleFontSize(5);
	back_button->setPosition(Vec2(origin.x + back_button->getContentSize().width * 3, origin.y + visbleSize.height - back_button->getContentSize().height * 3));
	back_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(2.0, HelloWorld::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(back_button, 1);

	//������ʱ��update����
	scheduleUpdate();

	return true;
}

void RecordScene::newRecord(Ref* pSender) {
	this->runAction(MoveBy::create(2.0, Vec2(0, visbleSize.height)));
}




void RecordScene::update(float delta) {
	//��Ϸÿһ֡������õķ���
	//log("a");
}

