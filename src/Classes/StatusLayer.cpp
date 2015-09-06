#include "StatusLayer.h"


const Size StatusLayer::STATUS = Size(300, 300);
const int StatusLayer::STATUS_SIZE = 20;
const int expArray[10] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
const int lifeArray[10] = { 60, 70, 90, 110, 130, 150, 180, 220, 250, 300 };

StatusLayer::StatusLayer()
{
}


StatusLayer::~StatusLayer()
{
}

StatusLayer* StatusLayer::createLayer() {
	return StatusLayer::create();
}

void StatusLayer::setLabelInfo(String info) {
	if (label_info != NULL) {
		label_info->setString(info.getCString());
		return;
	}
	label_info = Label::createWithTTF((String::createWithFormat("Warrior,\n forward to the unknown.")->getCString()),
		"fonts/Marker Felt.ttf", STATUS_SIZE);
	label_info->setTextColor(Color4B::WHITE);
	label_info->setPosition(-10, 110);
	this->addChild(label_info, 4);
}
void StatusLayer::setLabelLife(int life, int level) {
	if (label_life != NULL) {
		label_life->setString(String::createWithFormat("Health Value:  %d / %d", life, lifeArray[level])->getCString());
		return;
	}
	label_life = Label::createWithTTF((String::createWithFormat("Health Value:  %d / %d", life, lifeArray[level])->getCString()),
		"fonts/Marker Felt.ttf", STATUS_SIZE);
	label_life->setTextColor(Color4B::WHITE);
	label_life->setPosition(10, 50);
	this->addChild(label_life, 4);
}

void StatusLayer::setLabelAttack(int attack) {
	if (label_attack != NULL) {
		label_attack->setString(String::createWithFormat("Attack Value:  %d", attack)->getCString());
		return;
	}
	label_attack = Label::createWithTTF((String::createWithFormat("Attack Value:  %d", attack)->getCString()),
		"fonts/Marker Felt.ttf", STATUS_SIZE);
	label_attack->setTextColor(Color4B::WHITE);
	label_attack->setPosition(0, 0);
	this->addChild(label_attack, 4);
}
void StatusLayer::setLabelLevel(int level) {
	if (label_level != NULL) {
		label_level->setString(String::createWithFormat("Level:  %d", level)->getCString());
		return;
	}
	label_level = Label::createWithTTF((String::createWithFormat("Level:  %d", level)->getCString()),
		"fonts/Marker Felt.ttf", STATUS_SIZE);
	label_level->setTextColor(Color4B::WHITE);
	label_level->setPosition(-30, -50);
	this->addChild(label_level, 4);

}
void StatusLayer::setLabelExp(int exp, int level) {
	if (label_exp != NULL) {
		label_exp->setString(String::createWithFormat("Experience:  %d / %d", exp, expArray[level])->getCString());
		return;
	}
	label_exp = Label::createWithTTF((String::createWithFormat("Experience:  %d / %d", exp, expArray[level])->getCString()),
		"fonts/Marker Felt.ttf", STATUS_SIZE);
	label_exp->setTextColor(Color4B::WHITE);
	label_exp->setPosition(10, -100);
	this->addChild(label_exp, 4);
}

//void StatusLayer::setOpacity(GLubyte opacity) {
//	InfoLayer::setOpacity(opacity);
//	
//	//background->setOpacity(opacity);
//
//	label_info->setOpacity(opacity);
//	label_life->setOpacity(opacity);
//	label_attack->setOpacity(opacity);
//	label_level->setOpacity(opacity);
//	label_exp->setOpacity(opacity);
//}