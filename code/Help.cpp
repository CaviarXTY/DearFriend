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

//在“init()”你需要初始化你的实例
bool HelpScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	//获得设备支持得可见OpenGL视图大小
	auto visbleSize = Director::getInstance()->getVisibleSize();
	//获得可见OpenGL视图的起源点（默认0，0）
	auto origin = Director::getInstance()->getVisibleOrigin();

	/************************************************* 背景 ******************************************************/
	//创建精灵
	auto _background = Sprite::create("background0.png");
	//设置位置，中间
	_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//设置描点位置中间
	_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//设置自适应大小
	_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //设置精灵宽度缩放比例  
	_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//设置精灵高度缩放比例  
																						//精灵添加为当前层子节点
	this->addChild(_background, 0);

	/********************************************** 返回按钮 ***************************************************/
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

	/************************************************* 图片 ******************************************************/
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


	/************************************************* 文字 ******************************************************/
	Label *l1 = Label::createWithSystemFont("方向", "Marker Felt", 10);
	l1->setAnchorPoint(Vec2(0.5, 0.5));
	l1->setPosition(Vec2(visbleSize.width / 5 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l1);

	Label *l2 = Label::createWithSystemFont("对话/查看/继续", "Marker Felt", 10);
	l2->setAnchorPoint(Vec2(0.5, 0.5));
	l2->setPosition(Vec2(visbleSize.width * 3 / 7 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l2);

	Label *l3 = Label::createWithSystemFont("暂停", "Marker Felt", 10);
	l3->setAnchorPoint(Vec2(0.5, 0.5));
	l3->setPosition(Vec2(visbleSize.width * 4 / 6 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l3);

	Label *l4 = Label::createWithSystemFont("背包", "Marker Felt", 10);
	l4->setAnchorPoint(Vec2(0.5, 0.5));
	l4->setPosition(Vec2(visbleSize.width * 5 / 6 + origin.x, visbleSize.height / 2 + origin.y));
	this->addChild(l4);

	return true;
}
