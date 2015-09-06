#pragma once
#include "cocos2d.h"
USING_NS_CC;


class Util
{
public:
	Util();
	~Util();
	static TransitionScene * getTransitionSceneRandom(Scene *scene);
};

