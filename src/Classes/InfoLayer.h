#pragma once

#include "cocos2d.h"

USING_NS_CC;

class InfoLayer : public Layer {
public:
	InfoLayer();
	~InfoLayer();


	CREATE_FUNC(InfoLayer);

	static InfoLayer * createLayer();

	void setBackgroundStreth(String imgPath);
	void setBackground(String imgPath);
	Sprite * getBackground();

	virtual Action* runAction(Action *action);
	//void setOpacity(GLubyte opacity);
protected:
	Sprite *background;
};
