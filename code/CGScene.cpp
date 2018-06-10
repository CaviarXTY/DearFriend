#include "CGScene.h"
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


Scene* CGScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CGScene::create();
	scene->addChild(layer);
	return scene;
}

//在“init()”你需要初始化你的实例
bool CGScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//数据初始化
	_count = 0;
	_delay = 4;
	_num = 0;

	//读取记录文件
	ifstream loadin("origin.txt");   //输入
	char ch[450];
	while (!loadin.eof()) {//如果没有读取到文件文件尾部
		loadin.getline(ch, 20);
		_numScene = atoi(ch);
	}
	loadin.close();

	//读取路径文件
	string fn = (string)ch + ".txt";
	//ifstream in("tile/" + fn);   //输入
	string background = "Scene/Scene" + (string)ch + ".png";
	//while (!in.eof()) {
		//如果没有读取到文件文件尾部
	//	in.getline(ch, 450);			//读行
	//	char *p;
	//	boolean b = true;
	//	p = strtok(ch, ":");
	//	while (p)
	//	{
	//		if (b == true) {
	//			b = false;
	//		}
	//		else {
	//			background = p;//Content
	//			b = true;
	//		}
	//		//i++;
	//		p = strtok(NULL, ":");
	//	}
	//}
	//in.close();

	ifstream textin("dialog/" + fn);   //输入
	string str[40];
	int i = 0;
	while (!textin.eof()) {
		//如果没有读取到文件文件尾部
		textin.getline(ch, 450);			//读行
		char *p;
		bool b = true;
		p = strtok(ch, ":");
		while (p)
		{
			if (b == true) {
				str[i] = p;//Name
				b = false;
			}
			else {
				str[i] = p;//Content
				b = true;
			}
			i++;
			p = strtok(NULL, ":");
		}
	}
	textin.close();
	str[i] = "end";

	if(_numScene == 14){
		//音乐
		auto audioengine = SimpleAudioEngine::getInstance();
		audioengine->preloadBackgroundMusic("Lights Out.mp3");
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Lights Out.mp3", true);
	}

	//启动定时器update函数
	//scheduleUpdate();

	//获得设备支持得可见OpenGL视图大小
	auto visbleSize = Director::getInstance()->getVisibleSize();
	//获得可见OpenGL视图的起源点（默认0，0）
	auto origin = Director::getInstance()->getVisibleOrigin();

	/************************************************* 背景 ******************************************************/
	//创建精灵
	_background = Sprite::create(background);
	//设置位置，中间
	_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//设置描点位置中间
	_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//设置自适应大小
	_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //设置精灵宽度缩放比例  
	_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//设置精灵高度缩放比例  
																			  //精灵添加为当前层子节点
	this->addChild(_background, 0);


	/************************************************* 框 ******************************************************/

	_kuang = Sprite::create("kuang.png");
	_kuang->setAnchorPoint(Vec2(0, 0));
	_kuang->setScaleX(visbleSize.width / _kuang->getTextureRect().getMaxX());
	_kuang->setScaleY((visbleSize.height*0.4) / _kuang->getTextureRect().getMaxY());
	_kuang->setPosition(Vec2::ZERO);
	_kuang->setOpacity(70);
	this->addChild(_kuang, 1);

	_name = Label::createWithSystemFont(str[_num], "Marker Felt", 10);
	_name->setAnchorPoint(Vec2(0, 0));
	_name->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.35));
	this->addChild(_name, 2);

	_text = Label::createWithSystemFont(str[_num+1], "Marker Felt", 10);
	_text->setAnchorPoint(Vec2(0, 0));
	_text->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.30));
	this->addChild(_text, 2);

	_num = _num + 2;

	/************************************************ 文字 ******************************************************/
	Label *l5 = Label::createWithSystemFont("按空格继续", "Marker Felt", 10);
	l5->setAnchorPoint(Vec2(0.5, 0.5));
	l5->setPosition(Vec2(visbleSize.width * 7 / 8 + origin.x, visbleSize.height / 10 + origin.y));
	this->addChild(l5);

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
			if (str[_num] == "end") {
				ofstream out("origin.txt");
				out << _numScene+1;
				out.close();
				if (_numScene == 14) {
					//关闭音乐
					SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
				}
				auto transition = TransitionFade::create(1.0, LoadingScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
			else {
				showText(str[_num], str[_num + 1], true);
				_num = _num + 2;
			}
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	return true;
}


//对话框
void CGScene::showText(std::string name, std::string said, bool visble) {
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