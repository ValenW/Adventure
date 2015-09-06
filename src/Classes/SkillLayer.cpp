#include "SkillLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

const Size SkillLayer::SKILL_HERO = Size(200, 150);
SkillLayer * SkillLayer::skillLayer = NULL;

SkillLayer::SkillLayer()
{
}


SkillLayer::~SkillLayer()
{
	SkillLayer::skillLayer = NULL;
}


void SkillLayer::showSkillLayerRandom(Layer * layer) {
	if (skillLayer != NULL) {
		skillLayer->removeFromParentAndCleanup(true);
		//skillLayer = NULL;
	}

	skillLayer = SkillLayer::create();

	int skill_num = rand() % 3;
	String *hero = String::createWithFormat("/layers/skill_hero%d.png", skill_num);
	String *voice = String::createWithFormat("/music/skill_voice%d.wav", skill_num);
	skillLayer->setContentSize(SkillLayer::SKILL_HERO);
	skillLayer->setBackground(*hero);

	// 发出音效-不循环
	SimpleAudioEngine::getInstance()->playEffect(voice->getCString(), false);

	// 定位
	Size size = layer->getContentSize();
	Point point;
	point.x = size.width + skillLayer->getContentSize().width / 2;
	point.y = skillLayer->getContentSize().height / 2;
	skillLayer->setPosition(point);
	layer->addChild(skillLayer, 5);
	
	// 出现
	MoveBy *moveBy = MoveBy::create(0.5f, Point(-200, 0));
	MoveBy *moveBy2 = MoveBy::create(0.5f, Point(0, 0));
	Sequence *sequence = Sequence::create(moveBy->clone(),moveBy2->clone(), moveBy->reverse(), NULL);
	skillLayer->runAction(sequence);


}