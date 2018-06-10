#include "JinJuScene.h"
#include "HomeScene.h"
#include "BagScene.h"
#include "Player.h"
#include "ESCScene.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
USING_NS_CC;
using namespace ui;
using namespace std;

Scene* JinJuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = JinJuScene::create();
	scene->addChild(layer);
	return scene;
}


//�ڡ�init()������Ҫ��ʼ�����ʵ��
bool JinJuScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//����
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->preloadBackgroundMusic("Lights Out.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Lights Out.mp3", true);

	//��ʼ��ֵ
	b_up = false;
	b_down = false;
	b_left = false;
	b_right = false;
	_isText = false;
	_isFlash = false;
	_count = 0;
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
	ifstream textin("dialog/" + fn);   //����

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

	//������ʱ��update����
	scheduleUpdate();

	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	visbleSize = Director::getInstance()->getVisibleSize();
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	origin = Director::getInstance()->getVisibleOrigin();
	this->runAction(MoveTo::create(0.0f, Vec2(0, 25)));


	/************************************************* ��ͼ *****************************************************/
	//����TMXTiledMap�ú�����ȡTest.tmx
	_tileMap2 = TMXTiledMap::create("/test/jingju.tmx");
	//��ͼ����λ�ö�����Ϊԭ�㣬ʹ��ͼ���½�����Ļ����
	_tileMap2->setAnchorPoint(Vec2::ZERO);//���
	_tileMap2->setPosition(Vec2::ZERO);//��origin����
	//��ͼ���Ϊ��ǰ���ӽڵ�
	this->addChild(_tileMap2, -1);

	//��ȡ�ϰ���
	_collidable = _tileMap2->getLayer("collidable");
	_collidable->setVisible(false);

	/************************************************* ��� *****************************************************/
	_player = Player::create("player0.png");
	_player->setPosition(getObjectByName("ObjectLayer", "player"));
	_player->setAnchorPoint(Vec2(0.5, 0));
	_tileMap2->addChild(_player, 0);

	/************************************************* NPC ******************************************************/
	auto pinfo2 = AutoPolygon::generatePolygon("npc2.png");
	//bindPhysicsBody(this, "Player.png", 1, 0);
	_npc = Sprite::create(pinfo2);
	_npc->setAnchorPoint(Vec2::ZERO);
	_npc->setPosition(getObjectByName("ObjectLayer", "npc"));
	//_npc->setScale(2);//��С
	_tileMap2->addChild(_npc, 0);

	/************************************************* ������ ******************************************************/
	_get = Sprite::create("4-get.png");
	_get->setPosition(getObjectByName("ObjectLayer", "get"));
	//_get->setScale(2);//��С
	_get->setOpacity(0);
	this->addChild(_get);

	_To = Sprite::create("4-2.png");
	//_2To1->setAnchorPoint(Vec2(0, 0));
	_To->setPosition(getObjectByName("ObjectLayer", "to"));
	_To->setOpacity(0);
	//_2To1->setScale(2);//��С
	this->addChild(_To);

	/************************************************* �� ******************************************************/

	_kuang = Sprite::create("kuang.png");
	_kuang->setAnchorPoint(Vec2(0, 0));
	_kuang->setScaleX(visbleSize.width / _kuang->getTextureRect().getMaxX());
	_kuang->setScaleY((visbleSize.height*0.4) / _kuang->getTextureRect().getMaxY());
	//_kuang->setOpacity(0);
	this->addChild(_kuang, 3);

	_name = Label::createWithSystemFont("123", "Marker Felt", 10);
	_name->setAnchorPoint(Vec2(0, 0));
	this->addChild(_name, 4);

	_text = Label::createWithSystemFont("123", "Marker Felt", 10);
	_text->setAnchorPoint(Vec2(0, 0));
	this->addChild(_text, 4);

	/************************************************ ���� ******************************************************/
	//�����¼����������������¼�
	auto myKeyListener = EventListenerKeyboard::create();
	//���̰�������ʱ����Ӧ
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		CCLOG("key is pressed, keycode is %d", keycode);
		if (!_isText) {//�ǶԻ���
			keyListener(keycode, true);
		}
	};
	//���̰�������ʱ����Ӧ
	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		this->stopAllActions();//ֹͣ��Ļ�ƶ�
		_player->stopAllActions();//ֹͣ���鶯
		//_player->setMove(false);//�ɶ�������
		_isFlash = false;
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
				if (onContactBegin(_npc)) {
					if (_numScene == 4) {
						if (str[_num] == "end") {
							showText("", "", false);
							_isText = false;
							//����+1=5
							_numScene = _numScene + 1;
							ofstream out("origin.txt");
							out << _numScene;
							out.close();
						}
						else {
							//������ֿ�
							_isText = true;
							showText(str[_num], str[_num + 1], true);
							_num = _num + 2;
						}
					}
				}

 				//if (onContactBegin(_get)&& _numScene == 4) {
				//	showText("", "�������,�򿪱������Բ鿴", true);
				//}
		}
		if (!_isText) {//�ǶԻ���
					   //����
			if (keycode == EventKeyboard::KeyCode::KEY_B) {
				auto transition = TransitionFade::create(2.0, BagScene::createScene());
				Director::getInstance()->pushScene(transition);
			}
			if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
				auto transition = TransitionFade::create(2.0, ESCScene::createScene());
				Director::getInstance()->pushScene(transition);
			}
			keyListener(keycode, false);

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	return true;
}

//��Ϸÿһ֡������õķ���
void JinJuScene::update(float delta) {
	//onContactBegin(_npc);
	_count++;

	if (_count > moveDelay) {
		if (b_up || b_down || b_left || b_right) {
			playerFlash();
			//�����ƶ�
			if (b_up)
				playerMove(1);
			if (b_down)
				playerMove(2);
			if (b_left)
				playerMove(3);
			if (b_right)
				playerMove(4);
		}
		//���ü�����
		_count = 0;
	}
	if (onContactBegin(_To)) {
		if (_numScene <= 4) {
			showText("����", "�ȿ�����û��ʲô�����ɡ�", true);
		}
		else {
			//�ر�����
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
			auto transition = TransitionFade::create(1.0, HomeScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	}
	else {
		if (!_isText)//�ǶԻ���
			showText("", "", false);
	}
}

//��OPenGL����ת����TileMap����
Vec2 JinJuScene::tileCoordForPosition(Vec2 position) {
	Size mapSize = _tileMap2->getMapSize();
	Size tileSize = _tileMap2->getTileSize();
	int x = position.x / (tileSize.width / CC_CONTENT_SCALE_FACTOR());
	float pointHeight = _tileMap2->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (mapSize.height * pointHeight - position.y) / pointHeight;
	return Vec2(x, y);
}

//������ҽ��ƶ�λ��
Vec2 JinJuScene::willMove(int tag) {
	int x = _player->getPosition().x;
	int y = _player->getPosition().y;

	Point  tilrCoord = tileCoordForPosition(_player->getPosition());
	int tileGid = _collidable->getTileGIDAt(tilrCoord);

	if (tileGid != 0) {

	}
	//����
	if (tag == 1) {
		y = y + distance;//���㽫�����yλ��

	}
	//����
	if (tag == 2) {
		y = y - distance;//���㽫�����yλ��
	}
	//����
	if (tag == 3) {
		x = x - distance;//���㽫�����xλ��
	}
	//����
	if (tag == 4) {
		x = x + distance;//���㽫�����xλ��
	}

	if (_collidable->getTileGIDAt(tileCoordForPosition(Vec2(x, y))) == 0) {//�ڿ���������
		return Vec2(x, y);
	}

	return _player->getPosition();//�ڲ�����������
}

//���㾵ͷλ��
Vec2 JinJuScene::getPositionNow(Vec2 position) {
	//��ͼ�澫���ƶ�������һ��ʱ�ƶ����ƶ�λ����Сֵ��
	int x = MAX(position.x, visbleSize.width / 2);
	int y = MAX(position.y, visbleSize.height *0.3);
	//������ʾ��������ͼ�߽�(�ƶ�λ�����ֵ��
	x = MIN(x, (_tileMap2->getMapSize().width * 7.5 - visbleSize.width / 2));
	y = MIN(y, (_tileMap2->getMapSize().height * 7.5 - visbleSize.height *0.7));

	//ʵ��λ������
	Point actualPosition = Vec2(x, y);
	//��Ļ��������
	Point centerOfView = Vec2(visbleSize.width / 2, visbleSize.height *0.3);
	//��������λ�ú�ʵ���ƶ���λ��֮���ֵ
	Point viewPoint = centerOfView - actualPosition;
	x = visbleSize.width / 2 - x;
	y = visbleSize.height *0.3 - y;
	return Vec2(x, y + 25);
}

//��ȡObject��������
Vec2 JinJuScene::getObjectByName(std::string Layername, std::string name) {
	//��ȡ�����
	auto objects = _tileMap2->getObjectGroup(Layername);
	//��ȡ������Ϣ
	ValueMap map = objects->getObject(name);
	//���ص�ͼ������ֵ
	return Vec2(map.at("x").asInt(), map.at("y").asInt());
}

//�Ի���
void JinJuScene::showText(std::string name, std::string said, bool visble) {
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

//������Ӧ�¼�
void JinJuScene::keyListener(EventKeyboard::KeyCode keycode, bool set) {
	CCLOG("key is released, keycode is %d", keycode);
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		b_up = set;
		//b_down = false;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		b_down = set;
		//b_up = false;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		b_left = set;
		//b_right = false;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		b_right = set;
		//b_left = false;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
		;
		//_isText = set;
	}
}

//��ö��� animName����֡���� delay���ʱ�� animNum����֡����
Animate* JinJuScene::getAnimateByName(std::string animName, float delay, int animNum) {
	Animation* animation = Animation::create();
	//ѭ���Ӿ���֡�����л�ȡ��ͼƬ����Ӧ�Ķ���
	for (unsigned int i = 0; i < animNum;i++) {
		//��ȡ����ͼƬ����,��plane0.png
		std::string frameName = animName;
		frameName.append(StringUtils::format("%d", i)).append(".png");
		//����ͼƬ���Ϊ����֡
		animation->addSpriteFrameWithFile(frameName.c_str());
	}
	//���ö�����������
	animation->setDelayPerUnit(delay);
	//����ѭ��ִ��
	animation->setRestoreOriginalFrame(true);
	//���ض�������
	Animate* animate = Animate::create(animation);
	return animate;
}

//����
void JinJuScene::playerFlash() {
	if (!_isFlash) {
		log("aaa%d", _isFlash);
		//�򿪶���
		_isFlash = true;
		log("bbb%d", _isFlash);
		//��ö���
		auto animate = getAnimateByName("player", 0.15f, 3);
		//����������ִ�ж���
		auto repeatanimate = RepeatForever::create(animate);
		//�����ظ�ִ�ж���
		_player->runAction(repeatanimate);
	}
}
//���+��ͼ����
void JinJuScene::playerMove(int tag) {

	//���ͼ��ת��������
	if (b_left) {
		if (_player->isFlippedX())
			_player->setFlippedX(false);
	}
	else {
		if (!_player->isFlippedX())
			_player->setFlippedX(true);
	}
	//�����ƶ�
	_player->runAction(MoveTo::create(0.5, willMove(tag)));
	//��ͼ�ƶ�
	this->runAction(MoveTo::create(0.5, getPositionNow(_player->getPosition())));
	_kuang->setPosition(Vec2::ZERO - getPositionNow(_player->getPosition()));
	_name->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.35) - getPositionNow(_player->getPosition()));
	_text->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.30) - getPositionNow(_player->getPosition()));
}

//��ײ������
bool JinJuScene::onContactBegin(Sprite* s) {
	//��ײ��⣬������ײ    
	if ((_player->boundingBox()).intersectsRect(s->boundingBox()))
	{
		return true;
		this->unscheduleUpdate();
	}
	else
	{
		return false;
	}
	return false;
}

