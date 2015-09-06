#ifndef  GLOBAL_H_
#define  GLOBAL_H_

//#pragma once
#include "cocos2d.h"
#include <string>

using namespace std;

USING_NS_CC;


class Global
{
public:
	~Global();
	static Global * getInstance();

	//void setInfo(string info_);
	//String getInfo();
	void setLevel(int level_);
	int getLevel();
	void setAttack(int attack_);
	int getAttack();
	void setExperience(int experience_);
	int getExperience();
	void setLife(int life_);
	int getLife();
private:
	Global();
	static Global *global;

	//String info;
	int life;
	int level;
	int attack;
	int experience;

};

#endif