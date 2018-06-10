#include "ESCScene.h"
#include "Help.h"
#include "AudioControlScene.h"
#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#pragma execution_character_set("utf-8")
USING_NS_CC;
using namespace ui;

Scene* ESCScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ESCScene::create();
	scene->addChild(layer);
	return scene;
}

//�ڡ�init()������Ҫ��ʼ�����ʵ��
bool ESCScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//��ʼ��ֵ
	num = 0;
	page[0] = true;
	page[1] = true;
	page[2] = false;
	page[3] = false;
	page[4] = false;
	have = true;

	//������ʱ��update����
	scheduleUpdate();

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


	//���ذ�ť
	auto back_button = Button::create("");
	back_button->setScale(2);
	back_button->setTitleText("������Ϸ");
	back_button->setTitleFontName("Arial");	
	back_button->setTitleFontSize(5);
	back_button->setPosition(Vec2(origin.x + visbleSize.width/2, origin.y + visbleSize.height/2 + back_button->getContentSize().height * 3));
	back_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->popScene();
		}
	});
	this->addChild(back_button, 1);
	//����
	auto help_button = Button::create("");
	help_button->setScale(2);
	help_button->setTitleText("����");
	help_button->setTitleFontName("Arial");
	help_button->setTitleFontSize(5);
	help_button->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height/2 + back_button->getContentSize().height * 1));
	help_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(2.0, HelpScene::createScene());
			Director::getInstance()->pushScene(transition);
		}
	});
	this->addChild(help_button, 1);

	//���ð�ť
	auto set_button = Button::create("����");
	set_button->setScale(2);
	set_button->setTitleText("set");
	set_button->setTitleFontName("Arial");
	set_button->setTitleFontSize(5);
	set_button->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height/2 - back_button->getContentSize().height * 1));
	set_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(2.0, AudioControl::createScene());
			Director::getInstance()->pushScene(transition);
		}
	});
	this->addChild(set_button, 1);

	//�������˵�
	auto back_button2 = Button::create("");
	back_button2->setScale(2);
	back_button2->setTitleText("�������˵�");
	back_button2->setTitleFontName("Arial");
	back_button2->setTitleFontSize(5);
	back_button2->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height/2 - back_button->getContentSize().height * 3));
	back_button2->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(2.0, HelloWorld::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(back_button2, 1);

	return true;
}
