#include "AudioControlScene.h"
#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

/*****************************音效设置场景*************************************/
Scene* AudioControl::createScene()
{
	auto scene = Scene::create();
	auto layer = AudioControl::create();
	scene->addChild(layer);

	return scene;
}

//当文件不存在时打印有用的错误消息而不是段错误。
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//在“init()”你需要初始化你的实例
bool AudioControl::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//获得设备支持得可见OpenGL视图大小
	Size visbleSize = Director::getInstance()->getVisibleSize();
	//获得可见OpenGL视图的起源点（默认0，0）
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//返回按钮
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

	//创建标签（内容，字体，字号）
	auto label = LabelTTF::create("Set", "Arial", 24);
	//设置位置，中上
	label->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height - label->getContentSize().height));
	//标签添加为当前层子节点
	this->addChild(label);

	//背景音乐
	auto music_text = Text::create("BackgroundMusic", "Arial", 15);
	music_text->setPosition(Vec2(origin.x + visbleSize.width * 0.25, origin.y + visbleSize.height * 0.7));
	this->addChild(music_text);

	//创建滑动条
	auto music_slider = Slider::create();
	//设置滑动条纹理
	music_slider->loadBarTexture("sliderTrack.png");
	//设置滑动条滚轮纹理
	music_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	//设置处理滑动条的进度条纹理
	music_slider->loadProgressBarTexture("sliderProgress.png");
	//获取之前设置的背景音乐
	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");
	//如果第一次进入设置场景，默认为100
	if (musicPercent == 0.0f) {
		musicPercent = 100.0f;
	}
	//设置背景音乐滑动条的初始值
	music_slider->setPercent(musicPercent);
	//设置滑动条位置
	music_slider->setPosition(Vec2(origin.x + visbleSize.width * 0.6, origin.y + visbleSize.height * 0.7));
	//添加事件监听
	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type)
	{
		//当滑动条发生变化时
		if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			//获得滑动条百分比
			int percent = music_slider->getPercent();
			CCLOG("percent = %d", percent);
			//设置背景音乐为滑动条的/100
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent)/100);
			CCLOG("percent2 = %f", float(percent) / 100);
			//储存设置的背景音乐值
			UserDefault::getInstance()->setFloatForKey("musicPercent", float(percent));//没保存
			CCLOG("percent3 = %f", float(percent));
			CCLOG("musicPercent = %f", UserDefault::getInstance()->getFloatForKey("musicPercent"));//输出永远是0.0000
		}
	});
	this->addChild(music_slider);

	//音效
	auto sound_text = Text::create("SoundMusic", "Arial", 15);
	sound_text->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2 - sound_text->getContentSize().height));
	//this->addChild(sound_text);

	return true;
}


void AudioControl::menuCloseCallback(Ref* pSender)
{
	//关闭cocos2d-x游戏场景并退出应用程序
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
