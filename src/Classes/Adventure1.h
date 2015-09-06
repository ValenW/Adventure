#ifndef  ADVENTURE1_H_
#define  ADVENTURE1_H_

#include "cocos2d.h"
#include "Slide.h"
#include "Adventure.h"
#include "Global.h"
#include "DialogLayer.h"
#include "StatusLayer.h"
#include "Infolayer.h"
#include "WarLayer.h"
#include <string>
#include <stdio.h> 
#include <iostream> 
#include <time.h> 


using namespace std;

USING_NS_CC;

//#define database UserDefault::getInstance()

class Adventure1 :public Layer
{
public:
	Adventure1();
	~Adventure1();
	static cocos2d::Scene* scene();
	static Scene* createScene();

	CREATE_FUNC(Adventure1);

	virtual bool init();

	/*
	�洢���������vector��������
	wall������ǰ��
	stone����ʯ���ɼ�������ֵ
	monster1;����1
	monster2;����2
	black_hole;�ڶ����ɴ�����һ������ʤ���������������һ�ڶ���
	destination;�յ㣬�涴��־����������涴��һ�����ڶ���Χ����һ�����߼������Χ��
	random;����¼�
	supply;����վ
	*/
	Vector < Sprite * > v_wall;
	Vector < Sprite * > v_stone;
	Vector < Sprite * > v_monster1;
	Vector < Sprite * > v_monster2;
	Vector < Sprite * > v_monster3;
	Vector < Sprite * > v_black_hole;
	Vector < Sprite * > v_destination;
	Vector < Sprite * > v_random;
	Vector < Sprite * > v_supply;

	void initTouchEvent();

	void loadObject();

	// ���������Ĳ�����װ�����ĺ���
	Vector <Sprite *> loadFromMap(TMXTiledMap* tmx, string obj, string name, int DisX, int DisY);

	//����player�ƶ��ĺ������������ݷ�װ��move()��
	void onRightPressed(Ref* sender);
	void onLeftPressed(Ref* sender);
	void onUpPressed(Ref* sender);
	void onDownPressed(Ref* sender);
	void move(Point direct);

	void judge(string object, Point nextPos);
	void fightJudge(Sprite* s, int num);
	void JumpRandom(Point);
	void levelJudge();
	void BlackHole(Point, int);
	
	void Restart(Ref* sender);
	void ShowWin();
	void GameOver();

	bool win;

	// �����¼�
	void addKeyboardEvent();
	void keyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void keyRelease(EventKeyboard::KeyCode keyCode, Event *enent);
	static void resumeEventListener();
	// ģ̬���ں���
	void playAgain1(Ref *ref);
	void playAgain2(Ref *ref);
	void endGame(Ref * ref);

protected:
	static Adventure1 * adventure;
	Size visibleSize;
	int reach_count = 0;
	Sprite* player = NULL;
	Sprite* goal = NULL;
	Sprite* label_life = NULL;
	Sprite* label_attack = NULL;

	StatusLayer *  statusLayer;

	int life;
	int level;
	int attack;
	int experience;
	bool whether_black_hole = false;
};

#endif