#pragma once
#include "InfoLayer.h"
#include "cocos2d.h"
USING_NS_CC;

class SkillToolLayer : public InfoLayer
{
public:
	SkillToolLayer();
	~SkillToolLayer();

	CREATE_FUNC(SkillToolLayer);

	virtual bool init();
	void setLabelAttack(int attack);
	void setLabelDefence(int defence);
	void setLabelInstanceMove(int instanceMove);

private:
	Sprite * skill_attack;
	Sprite * skill_defence;
	Sprite * skill_instanceMove;
	Label * label_attack;
	Label * label_defence;
	Label * label_instanceMove;
};

