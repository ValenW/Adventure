#include "LeftTimeLayer.h"


LeftTimeLayer::LeftTimeLayer()
{
}


LeftTimeLayer::~LeftTimeLayer()
{
}


bool LeftTimeLayer::init() {
	if (!InfoLayer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getWinSize();

	Sprite * sprite_time = Sprite::create("layers/left_time.png");
	left_time = ProgressTimer::create(sprite_time);
	left_time->setType(ProgressTimer::Type::RADIAL);
	left_time->setReverseDirection(true);
	//left_time->setReverseProgress(false);
	left_time->setOpacity(255 * 0.6);
	repeat = Repeat::create(ProgressFromTo::create(30, 100, 0), 1);
	left_time->runAction(repeat);
	left_time->setPosition(Point(visibleSize.width - 64, visibleSize.height - 54));
	this->addChild(left_time, 4);
	
	// Ìí¼ÓÊ±¼ä
	Sprite * frame = Sprite::create("layers/frame.png");
	frame->setPosition(visibleSize.width - 56, visibleSize.height - 50);
	this->addChild(frame, 4);

	label_time = Label::create("30", "fonts/Marker Felt.ttf", 36);
	label_time->setPosition(visibleSize.width - 61, visibleSize.height - 56);
	label_time->setColor(Color3B::BLUE);
	this->addChild(label_time, 5);

	return true;
}

void LeftTimeLayer::setLabelTime(int time) {
	char t[40];
	sprintf(t, "%d", time);
	label_time->setString(t);
}

void LeftTimeLayer::stopAction() {
	left_time->stopAction(repeat);
}