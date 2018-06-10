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

//在“init()”你需要初始化你的实例
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

	//初始化值
	DBUtil::initDB("gamedata.db");
	int *b= DBUtil::getTable("select * from gamedata");
	DBUtil::closeDB();

	//读取记录文件
	ifstream loadin("origin.txt");   //输入
	char ch[450];
	while (!loadin.eof()) {//如果没有读取到文件文件尾部
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


	//启动定时器update函数
	scheduleUpdate();

	if (_numScene == 12) {
		num = 2;
	}
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

	/************************************************* 按钮 ******************************************************/
	//左按钮
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

	//右按钮
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

	//返回按钮
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

	/************************************************* 框 ******************************************************/

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

	/************************************************* 物品 ******************************************************/
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
			if (num == 0) {
				if (!_isText) {
					showText("凶器线索", "看起来跟印象中邻居家的刀子很像", true);
					_isText = true;
				}
				else {
					showText("", "", false);
					_isText = false;
				}
			}
			else if (num == 1) {
				if (!_isText) {
					showText("妻子的日记", "老王居然和妻子有着不可描述的关系", true);
					_isText = true;
				}
				else {
					showText("", "", false);
					_isText = false;
				}
			}
			else if (num == 2) {
				if (!_isText) {
					showText("带血外套", "外套属于男主角，带有不明血迹，袋子中装着香烟", true);
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

//对话框
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




