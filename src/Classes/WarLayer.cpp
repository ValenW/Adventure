#include "WarLayer.h"

const Size WarLayer::WAR = Size(300, 300);
const int WarLayer::WAR_TITLE_SIZE = 25;
const int WarLayer::WAR_CONTENT_SIZE = 20;
WarLayer * WarLayer::warLayer = NULL;

WarLayer::WarLayer()
{
}


WarLayer::~WarLayer()
{
	WarLayer::warLayer = NULL;
}

WarLayer* WarLayer::createLayer() {
	return WarLayer::create();
}

void WarLayer::setLabelWarTitle(String title) {
	if (label_war_title != NULL) {
		label_war_title->setString(title.getCString());
		return;
	}
	//label_war_title = Label::createWithTTF(title, "fonts/Marker Felt.ttf", WAR_SIZE);
	label_war_title = Label::createWithTTF(title.getCString(), "fonts/Marker Felt.ttf", WAR_TITLE_SIZE);
	label_war_title->setTextColor(Color4B::ORANGE);
	label_war_title->setPosition(Point(0, 30));
	this->addChild(label_war_title, 2);
}

void WarLayer::setLabelWarContent(String content) {
	if (label_war_content != NULL) {
		label_war_content->setString(content.getCString());
		return;
	}
	label_war_content = Label::createWithTTF(content.getCString(), "fonts/Marker Felt.ttf", WAR_CONTENT_SIZE);
	label_war_content->setTextColor(Color4B::WHITE);
	label_war_content->setPosition(0, -10);
	this->addChild(label_war_content, 2);
}

void WarLayer::showWarWindow(Layer * layer, String title, String content) {
	Size visibleSize = Director::getInstance()->getWinSize();
	WarLayer * wl = WarLayer::getInstanceFrom(layer);
	wl->setLabelWarTitle(title);
	wl->setLabelWarContent(content);
	wl->setBackground("layers/WarLayer.png");
	wl->setPosition(visibleSize.width / 2 + 64 * 2, visibleSize.height / 2);
	FadeOut * fadeOutFirst = FadeOut::create(0.0f);
	FadeIn * fadeIn = FadeIn::create(0.5f);
	FadeOut * fadeOut = FadeOut::create(0.5f);
	//Sequence * sequence = Sequence::create(fadeOutFirst, fadeIn, fadeOut, NULL);
	ScaleTo * scaleToFirst = ScaleTo::create(0.0f,0.0f);
	ScaleTo * scaleToBig = ScaleTo::create(0.5f,1.0f);
	ScaleTo * hold = ScaleTo::create(0.5f, 1.0f);
	ScaleTo * scaleToSmall = ScaleTo::create(0.5f, 0.0f);
	Spawn * spawnFirst = Spawn::create(fadeOutFirst,scaleToFirst,NULL);
	Spawn * spawnIn = Spawn::create(fadeIn, scaleToBig, NULL);
	Spawn * spawnOut = Spawn::create(fadeOut, scaleToSmall, NULL);
	//Sequence * sequence = Sequence::create(scaleToFirst, hold, scaleToBig, scaleToSmall, NULL);
	Sequence * sequence = Sequence::create(spawnFirst, spawnIn, hold, spawnOut, NULL);
	wl->runAction(sequence->clone());

}

Action * WarLayer::runAction(Action *action) {
	InfoLayer::runAction(action->clone());
	label_war_title->runAction(action->clone());
	label_war_content->runAction(action->clone());
	return action;
}

WarLayer * WarLayer::getInstanceFrom(Layer* layer) {
	if (warLayer == NULL) {
		//warLayer->removeAllChildrenWithCleanup(true);
		warLayer = WarLayer::create();
		layer->addChild(warLayer, 10);
	}
	//warLayer = WarLayer::create();
	return warLayer;
}