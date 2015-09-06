#include "Global.h"

Global * Global::global = NULL;

Global::Global() :
level(0),
attack(0),
experience(0)
{
}


Global::~Global()
{
}

Global * Global::getInstance() {
	if (global == NULL) {
		global = new Global();
	}
	return global;
}

/*void Global::setInfo(String info_) {
	info = info_;
}
String Global::getInfo() {
	return info;
}*/
void Global::setLevel(int level_) {
	level = level_;
}
int Global::getLevel() {
	return level;
}
void Global::setAttack(int attack_) {
	attack = attack_;
}
int Global::getAttack() {
	return attack;
}
void Global::setExperience(int experience_) {
	experience = experience_;
}
int Global::getExperience() {
	return experience;
}
void Global::setLife(int life_) {
	life = life_;
}
int Global::getLife() {
	return life;
}