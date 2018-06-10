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
	// 调用父类init函数
	if (!Layer::init())
	{
		return false;
	}

	//获得设备支持得可见OpenGL视图大小
	visbleSize = Director::getInstance()->getVisibleSize();
	//获得可见OpenGL视图的起源点（默认0，0）
	origin = Director::getInstance()->getVisibleOrigin();


	//this->runAction(MoveBy::create(2.0, Vec2(0, visbleSize.height)));


	//背景
	Sprite* sprite = Sprite::create("Record.png");
	//设置位置，中间
	sprite->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//设置描点位置中间
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//设置自适应大小
	sprite->setScaleX(visbleSize.width / sprite->getTextureRect().getMaxX()); //设置精灵宽度缩放比例  
	sprite->setScaleY(visbleSize.height / sprite->getTextureRect().getMaxY());//设置精灵高度缩放比例  
																			  //精灵添加为当前层子节点
	this->addChild(sprite, 0);



	auto label = Label::createWithSystemFont("是否开始新纪录", "Marker Felt", 50);
	label->setPosition(Vec2(visbleSize.width / 2 + origin.x, origin.y - visbleSize.height*0.4));
	this->addChild(label);//直接把Label显示在屏幕上


	////按钮
	//auto test_button = Button::create("R1-1.png");
	////设置描点位置中间
	//test_button->setAnchorPoint(Vec2(0, 0));
	//test_button->setPosition(Vec2(visbleSize.width * 0.368 + origin.x, visbleSize.height * 0.675 + origin.y));
	//test_button->setScaleX(visbleSize.width / sprite->getTextureRect().getMaxX()); //设置宽度缩放比例  
	//test_button->setScaleY(visbleSize.height / sprite->getTextureRect().getMaxY());//设置高度缩放比例  
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
	closeItem->setScaleX(visbleSize.width / sprite->getTextureRect().getMaxX()); //设置宽度缩放比例  
	closeItem->setScaleY(visbleSize.height / sprite->getTextureRect().getMaxY());//设置高度缩放比例  
	//this->addChild(closeItem, 1);

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	//确认按钮
	auto sure_button = Button::create("");
	sure_button->setTitleText("是");
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

	//否按钮
	auto no_button = Button::create("");
	no_button->setTitleText("否");
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


	//返回按钮
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

	//启动定时器update函数
	scheduleUpdate();

	return true;
}

void RecordScene::newRecord(Ref* pSender) {
	this->runAction(MoveBy::create(2.0, Vec2(0, visbleSize.height)));
}




void RecordScene::update(float delta) {
	//游戏每一帧都会调用的方法
	//log("a");
}

