#include "AudioControlScene.h"
#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

/*****************************��Ч���ó���*************************************/
Scene* AudioControl::createScene()
{
	auto scene = Scene::create();
	auto layer = AudioControl::create();
	scene->addChild(layer);

	return scene;
}

//���ļ�������ʱ��ӡ���õĴ�����Ϣ�����Ƕδ���
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//�ڡ�init()������Ҫ��ʼ�����ʵ��
bool AudioControl::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//����豸֧�ֵÿɼ�OpenGL��ͼ��С
	Size visbleSize = Director::getInstance()->getVisibleSize();
	//��ÿɼ�OpenGL��ͼ����Դ�㣨Ĭ��0��0��
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ذ�ť
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

	//������ǩ�����ݣ����壬�ֺţ�
	auto label = LabelTTF::create("Set", "Arial", 24);
	//����λ�ã�����
	label->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height - label->getContentSize().height));
	//��ǩ���Ϊ��ǰ���ӽڵ�
	this->addChild(label);

	//��������
	auto music_text = Text::create("BackgroundMusic", "Arial", 15);
	music_text->setPosition(Vec2(origin.x + visbleSize.width * 0.25, origin.y + visbleSize.height * 0.7));
	this->addChild(music_text);

	//����������
	auto music_slider = Slider::create();
	//���û���������
	music_slider->loadBarTexture("sliderTrack.png");
	//���û�������������
	music_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	//���ô��������Ľ���������
	music_slider->loadProgressBarTexture("sliderProgress.png");
	//��ȡ֮ǰ���õı�������
	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");
	//�����һ�ν������ó�����Ĭ��Ϊ100
	if (musicPercent == 0.0f) {
		musicPercent = 100.0f;
	}
	//���ñ������ֻ������ĳ�ʼֵ
	music_slider->setPercent(musicPercent);
	//���û�����λ��
	music_slider->setPosition(Vec2(origin.x + visbleSize.width * 0.6, origin.y + visbleSize.height * 0.7));
	//����¼�����
	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type)
	{
		//�������������仯ʱ
		if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			//��û������ٷֱ�
			int percent = music_slider->getPercent();
			CCLOG("percent = %d", percent);
			//���ñ�������Ϊ��������/100
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent)/100);
			CCLOG("percent2 = %f", float(percent) / 100);
			//�������õı�������ֵ
			UserDefault::getInstance()->setFloatForKey("musicPercent", float(percent));//û����
			CCLOG("percent3 = %f", float(percent));
			CCLOG("musicPercent = %f", UserDefault::getInstance()->getFloatForKey("musicPercent"));//�����Զ��0.0000
		}
	});
	this->addChild(music_slider);

	//��Ч
	auto sound_text = Text::create("SoundMusic", "Arial", 15);
	sound_text->setPosition(Vec2(origin.x + visbleSize.width / 2, origin.y + visbleSize.height / 2 - sound_text->getContentSize().height));
	//this->addChild(sound_text);

	return true;
}


void AudioControl::menuCloseCallback(Ref* pSender)
{
	//�ر�cocos2d-x��Ϸ�������˳�Ӧ�ó���
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
