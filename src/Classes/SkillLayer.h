#pragma once
#include "InfoLayer.h"
class SkillLayer :
	public InfoLayer
{
public:
	SkillLayer();
	~SkillLayer();
	static const Size SKILL_HERO;
	CREATE_FUNC(SkillLayer);

	static void showSkillLayerRandom(Layer * layer);
private:
	static SkillLayer * skillLayer;
};

