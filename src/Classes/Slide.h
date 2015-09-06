#pragma once

#include "cocos2d.h"
#include "DialogLayer.h"
#include "StatusLayer.h"
#include "Infolayer.h"
#include "WarLayer.h"
#include "SkillLayer.h"
#include "SkillToolLayer.h"
#include "LifeLayer.h"
#include "LeftTimeLayer.h"
#include "Util.h"

USING_NS_CC;

class Slide :public Layer
{
public:

	static Scene* createScene();
	static Slide* create(PhysicsWorld* world);

	bool init(PhysicsWorld* world);


	//音乐加载与播放
	void preloadMusic();
	void playBgm();
	void playEffect();


	void TouchEvent();

	void testKeyboardEvent();

	void testMouseEvent();

	void testCustomEvent();

	void testAccelerationEvent();

	void testSlide();

	bool onConcactBegan(PhysicsContact& contact);

	void cut(EventCustom* event);
	void down(EventCustom* event);

	void Schedule_(Ref *ref);
	void update(float f);
	void Slide::testOntouch();

	void Return(Ref *ref);
	void Restart(Ref *ref);
	void Exit(Ref *ref);

	//test
	EventListenerPhysicsContact * getTouchListener();

	// 修改瞬移样式
	void InstanceMove();

private:
	// 修改瞬移样式
	Sprite * instance_move_target = NULL;
	Point instanceMoveTarget;
	SkillToolLayer *skillToolLayer;
	LifeLayer * lifeLayer;
	LeftTimeLayer* leftTimeLayer;
	// test
	//static Slide *slide;
	// test
	EventListenerPhysicsContact * touchListener;
	Slide();
	~Slide();
	EventDispatcher* dispatcher;

	MotionStreak* streak;

	Vec2 touch_pos;

	bool isTouching;
	bool isCut;
	int moveTimes;
	int bleed;
	float timesNow;
	int timeLeft;
	float difficalty;
	bool defence;
	int bomb;
	int shel;

	Sprite* player;
	Sprite* apple;
	Sprite* box;
	Label *scoreLabel;
	Point oldPos;
	Sprite *brick1, *brick2, *cat1, *cat2;
	PhysicsWorld* m_world;
	//PhysicsJointPin* ropeJoint;
	Node* ropeBase;
	PhysicsJointFixed *ropeFix;
	Size visibleSize;
	// Label* bleedLabel;
	//Label* moveNumLabel;
	//Label* timeLabel;
	//Label* bombLabel;
	//Label* shelLabel;
	Vector<PhysicsBody*> enemys;

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void newEnemys(float f);
	void addEnemy(int type, Point p);
	void addBonus();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
	void bleedNew(int lose);
	void nodefence(float f);
	void escape();
	void gameOver();
};