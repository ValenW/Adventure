#pragma once
#include "InfoLayer.h"
class LifeLayer :
	public InfoLayer
{
public:
	LifeLayer();
	~LifeLayer();

	CREATE_FUNC(LifeLayer);
	virtual bool init();

	void setBloodPercentage(float percentage);
	void setLabelBlood(int blood);
	void setBloodColor(Color3B color3B);
private:
	ProgressTimer * lifeBar;
	Label *label_blood;
};

