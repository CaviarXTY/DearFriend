#ifndef __TWOSCENE_SCENE_H__
#define __TWOSCENE_SCENE_H__
#pragma execution_character_set("utf-8")
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;
using namespace cocos2d;
using namespace std;

class TwoScene : public cocos2d::Layer
{
private:

	//获得设备支持得可见OpenGL视图大小
	Size visbleSize;
	//获得可见OpenGL视图的起源点（默认0，0）
	Vec2 origin;
	//游戏帧计数器
	int _count;
	//行进距离（设置）
	int distance = 10;
	//行进间隔（设置）
	int moveDelay = 10;
	//按钮开关
	bool b_up, b_down, b_left, b_right;
	bool _isText;//是否对话中
	bool _isFlash;//动画中
	//boolean b_space;
	//地图
	TMXTiledMap *_tileMap2;
	//障碍层
	TMXLayer *_collidable;
	//玩家精灵
	Player *_player;
	Sprite* _npc;
	Sprite* _To;

	//对话框图片
	Sprite *_kuang;
	//对话框文本-名字
	Label *_name;
	//对话框文本-内容
	Label *_text;
	//故事线记录器
	int _num;
	//场景值
	int _numScene;
	//对话内容
	string str[40];

public:
	//创建实例
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();

	//定时器
	void update(float delta);

	//将OPenGL坐标转换成TileMap坐标
	Vec2 tileCoordForPosition(Vec2 position);

	//计算玩家将移动位置
	Vec2 willMove(int Tag);
	//计算镜头位置
	Vec2 getPositionNow(Vec2 position);
	//动画
	void playerFlash();
	//玩家+地图动作
	void playerMove(int tag);
	//对话框
	void showText(std::string name, std::string said, bool visble);
	//获取Object对象坐标
	Vec2 getObjectByName(std::string Layername, std::string name);

	//键盘响应事件
	void keyListener(EventKeyboard::KeyCode keycode, bool set);
	//获取图层信息
	Animate* getAnimateByName(std::string animName, float delay, int animNum);

	//碰撞处理函数
	bool onContactBegin(Sprite* s);

	bool onTouch(Vec2 posistion);



	CREATE_FUNC(TwoScene);
};
#endif __TWOSCENE_SCENE_H__