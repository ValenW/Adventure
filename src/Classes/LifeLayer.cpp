#include "LifeLayer.h"


LifeLayer::LifeLayer()
{
}


LifeLayer::~LifeLayer()
{
}

bool LifeLayer::init() {
	if (!InfoLayer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getWinSize();

	// Ìí¼ÓÉúÃüÌõ
	Sprite *sprite_life = Sprite::create("layers/life_blood.png");
	lifeBar = ProgressTimer::create(sprite_life);
	lifeBar->setType(ProgressTimer::Type::BAR);
	lifeBar->setBarChangeRate(Point(1, 0));
	lifeBar->setMidpoint(Point(0, 0));
	//lifeBar->setPercentage(bleed);
	lifeBar->setPosition(Point(lifeBar->getContentSize().width / 2 + 90, visibleSize.height - 50));
	this->addChild(lifeBar, 5);

	Sprite *life_frame = Sprite::create("layers/frame.png");
	life_frame->setPosition(Point(56, visibleSize.height - 46));
	life_frame->setOpacity(255 * 0.6);
	this->addChild(life_frame, 4);

	label_blood = Label::createWithTTF("100", "fonts/Marker Felt.ttf", 36);
	label_blood->setColor(Color3B::GREEN);
	label_blood->setPosition(Point(50, visibleSize.height - 52));
	label_blood->setOpacity(255 * 0.6);
	this->addChild(label_blood, 5);

	return true;
}

void LifeLayer::setBloodPercentage(float percentage) {
	lifeBar->setPercentage(percentage);
}

void LifeLayer::setLabelBlood(int blood) {
	char t[30];
	sprintf(t, "%d", blood);
	label_blood->setString(t);
}
void LifeLayer::setBloodColor(Color3B color3B) {
	label_blood->setColor(color3B);
}