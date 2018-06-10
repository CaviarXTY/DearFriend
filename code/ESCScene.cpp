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

//在“init()”你需要初始化你的实例
bool ESCScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//初始化值
	num = 0;
	page[0] = true;
	page[1] = true;
	page[2] = false;
	page[3] = false;
	page[4] = false;
	have = true;

	//启动定时器update函数
	scheduleUpdate();

	//获得设备支持得可见OpenGL视图大小
	visbleSize = Director::getInstance()->getVisibleSize();
	//获得可见OpenGL视图的起源点（默认0，0）
	origin = Director::getInstance()->getVisibleOrigin();

	/************************************************* 背景 ******************************************************/
	//创建精灵
	_background = Sprite::create("background0.png");
	//设置位置，中间
	_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//设置描点位置中间
	_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//设置自适应大小
	_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //设置精灵宽度缩放比例  
	_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//设置精灵高度缩放比例  
																						//精灵添加为当前层子节点
	this->addChild(_background, 0);


	//返回按钮
	auto back_button = Button::create("");
	back_button->setScale(2);
	back_button->setTitleText("返回游戏");
	back_button->setTitleFontName("Arial");	
	back_button->setTitleFontSize(5);
	back_button->setPosition(Vec2(origin.x + visbleSize.width/2, origin.y + visbleSize.height/2 + back_button->getContentSize().height * 3));
	back_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->popScene();
		}
	});
	this->addChild(back_button, 1);
	//帮助
	auto help_button = Button::create("");
	help_button->setScale(2);
	help_button->setTitleText("帮助");
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

	//设置按钮
	auto set_button = Button::create("设置");
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

	//返回主菜单
	auto back_button2 = Button::create("");
	back_button2->setScale(2);
	back_button2->setTitleText("返回主菜单");
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
