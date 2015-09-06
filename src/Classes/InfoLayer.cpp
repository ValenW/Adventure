#include "InfoLayer.h"



InfoLayer::InfoLayer() {


}
InfoLayer::~InfoLayer() {

}

InfoLayer * InfoLayer::createLayer() {
	return InfoLayer::create();
}


void InfoLayer::setBackgroundStreth(String imgPath) {
	// 设置背景图之前要先设置layer层大小
	background = Sprite::create(imgPath.getCString());
	Size layerSize = this->getContentSize();
	float scaleX = layerSize.width / background->getContentSize().width;
	float scaleY = layerSize.height / background->getContentSize().height;
	background->setScaleX(scaleX);
	background->setScaleY(scaleY);
	this->addChild(background, 0);
}

void InfoLayer::setBackground(String imgPath) {
	background = Sprite::create(imgPath.getCString());
	this->addChild(background, 0);
}

Sprite * InfoLayer::getBackground() {
	return background;
}


Action* InfoLayer::runAction(Action *action) {
	background->runAction(action->clone());
	return action;
}
//
//void InfoLayer::setOpacity(GLubyte opacity) {
//	background->setOpacity(opacity);
//}