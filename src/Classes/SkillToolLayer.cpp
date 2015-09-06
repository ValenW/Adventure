#include "SkillToolLayer.h"


SkillToolLayer::SkillToolLayer()
{
}


SkillToolLayer::~SkillToolLayer()
{
}


bool SkillToolLayer::init() {
	if (!InfoLayer::init()) {
		return false;
	}

	float width = 130;
	float height = 120;
	const int FONT_SIZE = 24;

	this->setContentSize(Size(390, 120));
	
	skill_attack = Sprite::create("layers/skill_attack.png");
	skill_attack->setPosition(width / 2, height / 2);
	this->addChild(skill_attack, 0);
	skill_defence = Sprite::create("layers/skill_defence.png");
	skill_defence->setPosition(width*1.5, height / 2);
	this->addChild(skill_defence, 0);
	skill_instanceMove = Sprite::create("layers/skill_instance_move.png");
	skill_instanceMove->setPosition(width*2.5, height / 2);
	this->addChild(skill_instanceMove, 0);

	label_attack = Label::create("0", "fonts/Marker Felt.ttf", FONT_SIZE);
	label_attack->setTextColor(Color4B::GREEN);
	label_attack->setPosition(100, 88);
	this->addChild(label_attack, 1);

	label_defence = Label::create("0", "fonts/Marker Felt.ttf", FONT_SIZE);
	label_defence->setTextColor(Color4B::GREEN);
	label_defence->setPosition(227, 88);
	this->addChild(label_defence, 1);

	label_instanceMove = Label::create("0", "fonts/Marker Felt.ttf", FONT_SIZE);
	label_instanceMove->setTextColor(Color4B::ORANGE);
	label_instanceMove->setPosition(357, 88);
	this->addChild(label_instanceMove, 1);

	return true;
}
void SkillToolLayer::setLabelAttack(int attack) {
	label_attack->setString(String::createWithFormat("%d", attack)->getCString());
}
void SkillToolLayer::setLabelDefence(int defence) {
	label_defence->setString(String::createWithFormat("%d", defence)->getCString());
}
void SkillToolLayer::setLabelInstanceMove(int instanceMove) {
	label_instanceMove->setString(String::createWithFormat("%d", instanceMove)->getCString());
}