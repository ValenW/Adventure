#pragma once
#include "InfoLayer.h"
class WarLayer :
	public InfoLayer
{
public:
	WarLayer();
	~WarLayer();

	CREATE_FUNC(WarLayer);

	static WarLayer * getInstanceFrom(Layer * layer);

	static const Size WAR;
	static const int WAR_TITLE_SIZE;
	static const int WAR_CONTENT_SIZE;

	virtual Action* runAction(Action *action);

	// 战斗结束栏
	void setLabelWarTitle(String title);
	void setLabelWarContent(String content);

	static void showWarWindow(Layer * layer, String title, String content);
private:
	static WarLayer * createLayer();
	static WarLayer *warLayer;
	// 战斗结束栏
	Label* label_war_title = NULL;
	Label* label_war_content = NULL;
};

