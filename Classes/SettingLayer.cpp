﻿#include "SettingLayer.h"
#include "StartSence.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
using namespace experimental;
using namespace cocos2d::ui;
SettingLayer* SettingLayer::create(StartSence* startSence) {
	SettingLayer *ret = new (std::nothrow)SettingLayer(startSence);
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	} else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

SettingLayer::SettingLayer(StartSence* startSence):startSence(startSence) {

}
SettingLayer::~SettingLayer() {
}

bool SettingLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();

	//背景
	Sprite* bgSp = Sprite::create("image/ui/setting_bg.png");
	bgSp->setPosition(Vec2(size.width / 2, size.height / 2 + 80));
	this->addChild(bgSp, 0);

	//关闭按钮
	Button* closeBtn = Button::create("image/ui/close_normal.png", "image/ui/close_pressed.png");
	closeBtn->setPosition(Vec2(size.width / 2 + bgSp->getContentSize().width / 2 - 20
		, size.height / 2 + bgSp->getContentSize().height / 2 + 10));
	this->addChild(closeBtn, 1);
	Button* startBtn = (Button*)startSence->getChildByTag(1);
	Button* settingBtn = (Button*)startSence->getChildByTag(2);
	Button* helpBtn = (Button*)startSence->getChildByTag(3);
	Button* aboutBtn = (Button*)startSence->getChildByTag(4);
	closeBtn->addClickEventListener([this, startBtn, settingBtn, helpBtn, aboutBtn](Ref*) {
		clickMenuSound();
		//移出暂停层
		removeAllChildren();

		//显示开始游戏按钮
		startBtn->setVisible(true);

		//显示设置按钮
		settingBtn->setVisible(true);

		//显示帮助按钮
		helpBtn->setVisible(true);

		//显示关于我们按钮
		aboutBtn->setVisible(true);
	});

	//开启或关闭声音精灵
	openCloseSoundSp = Sprite::create("image/ui/open_close_sound.png");
	openCloseSoundSp->setPosition(Vec2(size.width / 2 - 60, size.height / 2 + 80));
	this->addChild(openCloseSoundSp, 1);

	//开启或关闭音效精灵
	openCloseSoundEffSp = Sprite::create("image/ui/open_close_sound_eff.png");
	openCloseSoundEffSp->setPosition(Vec2(size.width / 2 - 60, size.height / 2));
	this->addChild(openCloseSoundEffSp, 1);

	initSoundEff();
	initBGMusic();

	

	return true;
}

/*
	初始化音效
*/
void SettingLayer::initSoundEff() {
	Size size = Director::getInstance()->getVisibleSize();
	//音效开按钮
	Button* soundEffOpenBtn = Button::create("image/ui/musicOn.png");
	soundEffOpenBtn->setPosition(Vec2(size.width / 2 + openCloseSoundEffSp->getContentSize().width - 90,
		size.height / 2));
	this->addChild(soundEffOpenBtn, 1);

	//音效关按钮
	Button* soundEffCloseBtn = Button::create("image/ui/musicOff.png");
	soundEffCloseBtn->setPosition(Vec2(size.width / 2 + openCloseSoundEffSp->getContentSize().width - 90,
		size.height / 2));
	this->addChild(soundEffCloseBtn, 1);
	//默认是开启音效
	soundEffCloseBtn->setVisible(false);

	//开启音效按钮事件
	soundEffOpenBtn->addClickEventListener([this, soundEffOpenBtn, soundEffCloseBtn](Ref*) {
		clickMenuSound();
		//隐藏开始音效按钮
		soundEffOpenBtn->setVisible(false);
		//显示关闭音效按钮
		soundEffCloseBtn->setVisible(true);
		//关闭所有音效
		AudioEngine::stopAll();
	});

	//关闭音效按钮事件
	soundEffCloseBtn->addClickEventListener([this, soundEffCloseBtn, soundEffOpenBtn](Ref*) {
		clickMenuSound();
		//显示开始音效按钮
		soundEffOpenBtn->setVisible(true);
		//隐藏关闭音效按钮
		soundEffCloseBtn->setVisible(false);
		//关闭所有音效
		AudioEngine::resumeAll();
	});
}

/*
	初始化背景音乐
*/
void SettingLayer::initBGMusic() {
	Size size = Director::getInstance()->getVisibleSize();

	//背景音乐开按钮
	Button* soundOpenBtn = Button::create("image/ui/soundOn.png");
	soundOpenBtn->setPosition(Vec2(size.width / 2 + openCloseSoundSp->getContentSize().width - 90,
		size.height / 2 + 80));
	this->addChild(soundOpenBtn, 1);
	
	//背景音乐关按钮
	Button* soundCloseBtn = Button::create("image/ui/soundOff.png");
	soundCloseBtn->setPosition(Vec2(size.width / 2 + openCloseSoundSp->getContentSize().width - 90,
		size.height / 2 + 80));
	soundCloseBtn->setVisible(false);
	this->addChild(soundCloseBtn, 1);

	//开启音效按钮事件
	soundOpenBtn->addClickEventListener([this, soundOpenBtn, soundCloseBtn](Ref*) {
		clickMenuSound();
		//隐藏开始音效按钮
		soundOpenBtn->setVisible(false);
		//显示关闭音效按钮
		soundCloseBtn->setVisible(true);
	});

	//关闭音效按钮事件
	soundCloseBtn->addClickEventListener([this, soundCloseBtn, soundOpenBtn](Ref*) {
		clickMenuSound();
		//显示开始音效按钮
		soundOpenBtn->setVisible(true);
		//隐藏关闭音效按钮
		soundCloseBtn->setVisible(false);
	});
}

/*
	点击按钮时声音
*/
void SettingLayer::clickMenuSound() {
	AudioEngine::play2d("sound/button.mp3");
}