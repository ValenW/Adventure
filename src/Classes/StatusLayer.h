#pragma once
#include "InfoLayer.h"
#include "cocos2d.h"
USING_NS_CC;

class StatusLayer :
	public InfoLayer
{
public:

	static const Size STATUS;
	static const int STATUS_SIZE;

	CREATE_FUNC(StatusLayer);
	static StatusLayer * createLayer();

	StatusLayer();
	~StatusLayer();
	// ×´Ì¬À¸
	void setLabelInfo(String info);
	void setLabelLife(int life, int level);
	void setLabelAttack(int attack);
	void setLabelLevel(int level);
	void setLabelExp(int exp, int level);
	//void setOpacity(GLubyte opacity);
private:

	// ×´Ì¬À¸
	Label* label_info = NULL;
	Label* label_life = NULL;
	Label* label_attack = NULL;
	Label* label_level = NULL;
	Label* label_exp = NULL;
};

