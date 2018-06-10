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

//在“init()”你需要初始化你的实例
bool LoadingScene::init()
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

	/************************************************ 文字 ******************************************************/
	Label *l5 = Label::createWithSystemFont("按空格继续", "Marker Felt", 10);
	l5->setAnchorPoint(Vec2(0.5, 0.5));
	l5->setPosition(Vec2(visbleSize.width * 7 / 8 + origin.x, visbleSize.height / 10 + origin.y));
	this->addChild(l5);

	/************************************************* 转场 ******************************************************/
	ifstream in("origin.txt");   //输入
	char ch[20];
	int a = 0;
    	while (!in.eof()) {
		//如果没有读取到文件文件尾部
		in.getline(ch, 20);
		a = atoi(ch);
	}
	in.close();


	/************************************************ 监听 ******************************************************/
	//创建事件监听器监听键盘事件
	auto myKeyListener = EventListenerKeyboard::create();
	//键盘按键按下时的响应
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		CCLOG("key is pressed, keycode is %d", keycode);
	};
	//键盘按键弹回时的响应
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
				
				//音乐
				auto audioengine = SimpleAudioEngine::getInstance();
				audioengine->preloadBackgroundMusic("Cold Feet.mp3");
				SimpleAudioEngine::getInstance()->playBackgroundMusic("Cold Feet.mp3", true);

				//创建精灵
				auto _background = Sprite::create("Scene/Scene15.png");
				//设置位置，中间
				_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
				//设置描点位置中间
				_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				//设置自适应大小
				_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //设置精灵宽度缩放比例  
				_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//设置精灵高度缩放比例  
																									//精灵添加为当前层子节点
				this->addChild(_background, 0);

				//创建标签（内容，字体，字号）
				auto label = LabelTTF::create("THE END", "Arial", 24);
				//设置位置，中上
				label->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2));
				//标签添加为当前层子节点
				this->addChild(label, 1);
				//返回主菜单
				auto back_button2 = Button::create("");
				back_button2->setScale(2);
				back_button2->setTitleText("返回主菜单");
				back_button2->setTitleFontName("Arial");
				back_button2->setTitleFontSize(5);
				back_button2->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2 - label->getContentSize().height * 2));
				back_button2->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
					if (type == Widget::TouchEventType::ENDED) {
						//关闭音乐
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
