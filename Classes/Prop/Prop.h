﻿#ifndef __Porp_H__
#define __Porp_H__
#include "cocos2d.h"
using namespace cocos2d;
/*
	定义道具类型:
		Shield:防护罩
		WingAir：僚机
		ChangeBullet:子弹道具
*/
enum PropType { Shield = 1, WingAir, ChangeBullet, Health};
class Prop : public Sprite {
public:
	static Prop* create(PropType type);
	bool init();
	Prop(PropType type);
	//开启道具时显示的文字动画
	void propTextAct();
	~Prop();
	void setLive(bool isLive) {
		this->isLive = isLive;
	}
	//道具飞行调度器
	void update(float dt);
	PropType getType() {
		return type;
	}
	void magnetProp(Vec2 heroPos);//把道具吸到英雄上
private:
	//速度
	int speed;
	//飞行标志 1往右边飞  -1左边飞
	int flyFlag;
	bool isLive;
	Size size;
	PropType type;
	bool isCloseFiy;
	int showPropTextCount;
	static Sprite* textSp;
};

#endif // !__Porp_H__



