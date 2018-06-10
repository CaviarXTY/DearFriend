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

//�ڡ�init()������Ҫ��ʼ�����ʵ��
bool CGScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//���ݳ�ʼ��
	_count = 0;
	_delay = 4;
	_num = 0;

	//��ȡ��¼�ļ�
	ifstream loadin("origin.txt");   //����
	char ch[450];
	while (!loadin.eof()) {//���û�ж�ȡ���ļ��ļ�β��
		loadin.getline(ch, 20);
		_numScene = atoi(ch);
	}
	loadin.close();

	//��ȡ·���ļ�
	string fn = (string)ch + ".txt";
	//ifstream in("tile/" + fn);   //����
	string background = "Scene/Scene" + (string)ch + ".png";
	//while (!in.eof()) {
		//���û�ж�ȡ���ļ��ļ�β��
	//	in.getline(ch, 450);			//����
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

	ifstream textin("dialog/" + fn);   //����
	string str[40];
	int i = 0;
	while (!textin.eof()) {
		//���û�ж�ȡ���ļ��ļ�β��
		textin.getline(ch, 450);			//����
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
		//����
		auto audioengine = SimpleAudioEngine::getInstance();
		audioengine->preloadBackgroundMusic("Lights Out.mp3");
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Lights Out.mp3", true);
	}

	//������ʱ��update����
	//scheduleUpdate();

	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	auto visbleSize = Director::getInstance()->getVisibleSize();
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	auto origin = Director::getInstance()->getVisibleOrigin();

	/************************************************* ���� ******************************************************/
	//��������
	_background = Sprite::create(background);
	//����λ�ã��м�
	_background->setPosition(Vec2(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));
	//�������λ���м�
	_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//��������Ӧ��С
	_background->setScaleX(visbleSize.width / _background->getTextureRect().getMaxX()); //���þ��������ű���  
	_background->setScaleY(visbleSize.height / _background->getTextureRect().getMaxY());//���þ���߶����ű���  
																			  //�������Ϊ��ǰ���ӽڵ�
	this->addChild(_background, 0);


	/************************************************* �� ******************************************************/

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

	/************************************************ ���� ******************************************************/
	Label *l5 = Label::createWithSystemFont("���ո����", "Marker Felt", 10);
	l5->setAnchorPoint(Vec2(0.5, 0.5));
	l5->setPosition(Vec2(visbleSize.width * 7 / 8 + origin.x, visbleSize.height / 10 + origin.y));
	this->addChild(l5);

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
			if (str[_num] == "end") {
				ofstream out("origin.txt");
				out << _numScene+1;
				out.close();
				if (_numScene == 14) {
					//�ر�����
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


//�Ի���
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