#pragma once
#include "InfoLayer.h"
class LeftTimeLayer :
	public InfoLayer
{
public:
	LeftTimeLayer();
	~LeftTimeLayer();

	CREATE_FUNC(LeftTimeLayer);
	virtual bool init();

	void setLabelTime(int time);
	void stopAction();
private:
	Label *label_time;
	ProgressTimer *left_time;
	Repeat * repeat;

};

