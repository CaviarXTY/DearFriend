#include "TwoScene.h"
#include "BagScene.h"
#include "HomeScene.h"
#include "LoadingScene.h"
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

Scene* TwoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TwoScene::create();
	scene->addChild(layer);
	return scene;
}

//在“init()”你需要初始化你的实例
bool TwoScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//音乐
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->preloadBackgroundMusic("Birds, Forest Reverb.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Birds, Forest Reverb.mp3", true);

	//初始化值
	b_up = false;
	b_down = false;
	b_left = false;
	b_right = false;
	_isFlash = false;
	_isText = false;
	_num = 0;
	_count = 0;

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
	ifstream textin("dialog/" + fn);   //输入

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

	//启动定时器update函数
	scheduleUpdate();

	//获得设备支持得可见OpenGL视图大小
	visbleSize = Director::getInstance()->getVisibleSize();
	//获得可见OpenGL视图的起源点（默认0，0）
	origin = Director::getInstance()->getVisibleOrigin();
	this->runAction(MoveTo::create(0.0f, Vec2(0, 25)));


	/************************************************* 地图 *****************************************************/
	//调用TMXTiledMap得函数读取Test.tmx
	_tileMap2 = TMXTiledMap::create("/test/title.tmx");
	//地图描点和位置都设置为原点，使地图左下角与屏幕对齐
	_tileMap2->setAnchorPoint(Vec2::ZERO);//描点
	_tileMap2->setPosition(Vec2::ZERO);//与origin对齐
	//地图添加为当前层子节点
	this->addChild(_tileMap2, -1);

	//获取障碍层
	_collidable = _tileMap2->getLayer("collidable");
	_collidable->setVisible(false);

	/************************************************* 玩家 *****************************************************/
	_player = Player::create("player0.png");
	_player->setPosition(getObjectByName("ObjectLayer", "player"));
	_player->setAnchorPoint(Vec2(0.5, 0));
	//_player->setScale(2);//大小
	_tileMap2->addChild(_player, 1);

	/************************************************* NPC ******************************************************/
	auto pinfo2 = AutoPolygon::generatePolygon("npc0.png");
	//bindPhysicsBody(this, "Player.png", 1, 0);
	_npc = Sprite::create(pinfo2);
	_npc->setAnchorPoint(Vec2::ZERO);
	_npc->setPosition(getObjectByName("ObjectLayer", "npc_ts"));
	//_npc->setScale(2);//大小
	_tileMap2->addChild(_npc,0);

	/************************************************* 触发点 ******************************************************/
	_To = Sprite::create("1-2.png");
	//_1To2->setAnchorPoint(Vec2(0, 0));
	_To->setPosition(getObjectByName("ObjectLayer", "to"));
	_To->setOpacity(0);
	//_1To2->setScale(2);//大小
	this->addChild(_To);

	/************************************************* 框 ******************************************************/

	_kuang = Sprite::create("kuang.png");
	_kuang->setAnchorPoint(Vec2(0, 0));
	_kuang->setScaleX(visbleSize.width / _kuang->getTextureRect().getMaxX());
	_kuang->setScaleY((visbleSize.height*0.4) / _kuang->getTextureRect().getMaxY());
	_kuang->setOpacity(0);
	this->addChild(_kuang, 0);

	_name = Label::createWithSystemFont("", "Marker Felt", 10);
	_name->setAnchorPoint(Vec2(0, 0));
	this->addChild(_name, 1);

	_text = Label::createWithSystemFont("", "Marker Felt", 10);
	_text->setAnchorPoint(Vec2(0, 0));
	this->addChild(_text, 1);

	/************************************************ 监听 ******************************************************/
	//创建事件监听器监听键盘事件
	auto myKeyListener = EventListenerKeyboard::create();
	//键盘按键按下时的响应
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		CCLOG("key is pressed, keycode is %d", keycode);
		if (!_isText) {//非对话中
			keyListener(keycode, true);
		}
	};
	//键盘按键弹回时的响应
	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		this->stopAllActions();//停止屏幕移动
		_player->stopAllActions();//停止精灵动作
		//_player->setMove(false);//可动画开关
		_isFlash = false;
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
			if (onContactBegin(_npc)) {

				if (_numScene == 2) {
					if (str[_num] == "end") {
						showText("", "", false);
						_isText = false;
						//场景+1=3
						_numScene = _numScene + 1;
						ofstream out("origin.txt");
						out << _numScene;
						out.close();
					}
					else {
						//输出文字框
						_isText = true;
						showText(str[_num], str[_num + 1], true);
						_num = _num + 2;
					}
				}

				if (_numScene == 9) {
					if (str[_num] == "end") {
						showText("", "", false);
						_isText = false;
						//场景+1=10
						_numScene = _numScene + 1;
						ofstream out("origin.txt");
						out << _numScene;
						out.close();
						//关闭音乐
						SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
						auto transition = TransitionFade::create(1.0, LoadingScene::createScene());
						Director::getInstance()->replaceScene(transition);
					}
					else {
						//输出文字框
						_isText = true;
						showText(str[_num], str[_num + 1], true);
						_num = _num + 2;
					}
				}

			}
		}

		if (!_isText) {//非对话中
			 //背包
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

//游戏每一帧都会调用的方法
void TwoScene::update(float delta) {
	onContactBegin(_npc);
	_count++;

	if (_count > moveDelay) {
		if (b_up || b_down || b_left || b_right) {
			playerFlash();
			//人物移动
			if (b_up)
				playerMove(1);
			if (b_down)
				playerMove(2);
			if (b_left)
				playerMove(3);
			if (b_right)
				playerMove(4);
		}
		//重置计数器
		_count = 0;
	}

	if (onContactBegin(_To)) {//与右通路接触
		if (_numScene == 2) {
			showText("男主", "去找老王一起回家吧。",true);
		}
		else if (_numScene == 3) {
			//关闭音乐
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
			auto transition = TransitionFade::create(1.0, LoadingScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
		else if (_numScene == 9) {
			showText("男主", "一定要找老王算账。", true);
		}
		else {
			//关闭音乐
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
			auto transition = TransitionFade::create(1.0, HomeScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	}else {
		if(!_isText)//非对话中
		showText("", "", false);
	}

	
}

//将OPenGL坐标转换成TileMap坐标
Vec2 TwoScene::tileCoordForPosition(Vec2 position) {
	//CC_CONTENT_SCALE_FACTOR Retina返回2，否则返回1
	//玩家位置的x坐标除以地图的宽，得到地图横向第几个格子（tile）
	//地图宽计算：26[格子]*64[图块宽]=1680[地图宽]
	//假设精灵x坐标为640，则所在格子计算640[精灵位置]/64[图块宽]=10[格子]
	//int x = (int)(position.x / (_tileMap2->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	//玩家位置y坐标除以地图的高，得到纵向第几个格子（tile）
	//因为ccoos2d-x的y轴（左下角）和TileMap的y轴（左上角）相反，所以使用地图高度-玩家y坐标
	//float pointHeight = _tileMap2->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	//int y = (int)((_tileMap2->getMapSize().height * pointHeight - position.y) / pointHeight);
	//return Vec2(x, y);
	Size mapSize = _tileMap2->getMapSize();
	Size tileSize = _tileMap2->getTileSize();
	int x = position.x / (tileSize.width / CC_CONTENT_SCALE_FACTOR());
	float pointHeight = _tileMap2->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (mapSize.height * pointHeight - position.y) / pointHeight;
	return Vec2(x, y);
}

//计算玩家将移动位置
Vec2 TwoScene::willMove(int tag) {
	int x = _player->getPosition().x;
	int y = _player->getPosition().y;

	Point  tilrCoord = tileCoordForPosition(_player->getPosition());
	int tileGid = _collidable->getTileGIDAt(tilrCoord);

	if (tileGid != 0) {

	}
	//向上
	if (tag == 1) {
		y = y + distance;//计算将到达的y位置
		if (y + _player->getContentSize().height > visbleSize.height - 10)//超出上边界
			y = visbleSize.height - _player->getContentSize().height;//上最值
	}
	//向下
	if (tag == 2) {
		y = y - distance;//计算将到达的y位置
		if (y < 10)//超出下边界
			y = _player->getContentSize().height;//下最值
	}
	//向左
	if (tag == 3) {
		x = x - distance;//计算将到达的x位置
		//if (x - _player->getContentSize().width < 10)//超出左边界
			//x = _player->getContentSize().width;//左最值
	}
	//向右
	if (tag == 4) {
		x = x + distance;//计算将到达的x位置
		//if (x + _player->getContentSize().width > visbleSize.width - 10)//超出右边界
			//x = visbleSize.width - _player->getContentSize().width;//右最值
	}

	if (_collidable->getTileGIDAt(tileCoordForPosition(Vec2(x, y))) == 0) {//在可行区域内
		return Vec2(x, y);
	}

	return _player->getPosition();//在不可行区域内
}

//计算镜头位置
Vec2 TwoScene::getPositionNow(Vec2 position) {
	//地图随精灵移动，超过一半时移动（移动位置最小值）
	int x = MAX(position.x, visbleSize.width / 2);
	int y = MAX(position.y, visbleSize.height *0.3);
	//不让显示区超出地图边界(移动位置最大值）
	x = MIN(x, (_tileMap2->getMapSize().width * 7.5 - visbleSize.width / 2));
	y = MIN(y, (_tileMap2->getMapSize().height * 7.5 - visbleSize.height *0.7));

	//实际位移坐标
	Point actualPosition = Vec2(x, y);
	//屏幕中心坐标
	Point centerOfView = Vec2(visbleSize.width / 2, visbleSize.height *0.3);
	//计算中心位置和实际移动的位置之间差值
	Point viewPoint = centerOfView - actualPosition;
	x = visbleSize.width / 2 - x;
	y = visbleSize.height *0.3 - y;
	return Vec2(x, y + 25);
}

//获取Object对象坐标
Vec2 TwoScene::getObjectByName(std::string Layername, std::string name) {
	//获取对象层
	auto objects = _tileMap2->getObjectGroup(Layername);
	//获取对象信息
	ValueMap map = objects->getObject(name);
	//返回地图中坐标值
	return Vec2(map.at("x").asInt(), map.at("y").asInt());
}

//对话框
void TwoScene::showText(std::string name, std::string said, bool visble) {
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


//键盘响应事件
void TwoScene::keyListener(EventKeyboard::KeyCode keycode, bool set) {
	CCLOG("key is released, keycode is %d", keycode);
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		b_up = set;
		b_down = false;
	}
		
	if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		b_down = set;
		b_up = false;
	}
		
	if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		b_left = set;
		b_right = false;
	}
		
	if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		b_right = set;
		b_left = false;
	}
		
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
		;
		//_isText = set;
	}
		
}

//获得动画 animName动画帧名字 delay间隔时间 animNum动画帧数量
Animate* TwoScene::getAnimateByName(std::string animName, float delay, int animNum) {
	Animation* animation = Animation::create();
	//循环从精灵帧缓存中获取与图片名对应的动画
	for (unsigned int i = 0; i < animNum;i++) {
		//获取动画图片名称,如plane0.png
		std::string frameName = animName;
		frameName.append(StringUtils::format("%d", i)).append(".png");
		//单张图片添加为动画帧
		animation->addSpriteFrameWithFile(frameName.c_str());
	}
	//设置动画播放属性
	animation->setDelayPerUnit(delay);
	//设置循环执行
	animation->setRestoreOriginalFrame(true);
	//返回动画对象
	Animate* animate = Animate::create(animation);
	return animate;
}

//动画
void TwoScene::playerFlash() {
	if (!_isFlash) {
		log("aaa%d", _isFlash);
		//打开动画
		_isFlash = true;
		log("bbb%d", _isFlash);
		//获得动画
		auto animate = getAnimateByName("player", 0.15f, 3);
		//创建动作，执行动画
		auto repeatanimate = RepeatForever::create(animate);
		//精灵重复执行动作
		_player->runAction(repeatanimate);
	}
}
//玩家+地图动作
void TwoScene::playerMove(int tag) {

	//玩家图像反转，面向方向
	if (b_left) {
		if (_player->isFlippedX())
			_player->setFlippedX(false);
	}
	else {
		if (!_player->isFlippedX())
			_player->setFlippedX(true);
	}
	//人物移动
	_player->runAction(MoveTo::create(0.5, willMove(tag)));
	//地图移动
	this->runAction(MoveTo::create(0.5, getPositionNow(_player->getPosition())));
	_kuang->setPosition(Vec2::ZERO - getPositionNow(_player->getPosition()));
	_name->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.35) - getPositionNow(_player->getPosition()));
	_text->setPosition(Vec2(visbleSize.width *0.1, origin.x + visbleSize.height*0.30) - getPositionNow(_player->getPosition()));
}

//碰撞处理函数
bool TwoScene::onContactBegin(Sprite* s) {
	//碰撞检测，矩形碰撞    
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

