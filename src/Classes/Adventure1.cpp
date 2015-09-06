#include "Adventure1.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const float SIZE_WSAD = 100.0;
const int FONT_SIZE = 45;
const int NUM_BLACK_HOLE = 7;
const int MONSTER1_LIFE = 50;
const int MONSTER1_ATTACK = 10;
const int MONSTER1_EXP = 50;
const int MONSTER2_LIFE = 100;
const int MONSTER2_ATTACK = 20;
const int MONSTER2_EXP = 75;
const int MONSTER3_LIFE = 150;
const int MONSTER3_ATTACK = 30;
const int MONSTER3_EXP = 150;
const int expArray[15] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750};
const int attackArray[15] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};
const int lifeArray[15] = { 60, 70, 90, 110, 130, 150, 180, 220, 250, 300, 330, 360, 490, 520, 550};
//const int lifeArray[10] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };

Adventure1 * Adventure1::adventure = NULL;

// �������ֵΪ50��������Ϊ10����ֵ���Ըģ�������ֵΪ0

Scene* Adventure1::createScene()
{
	auto scene = Scene::create();
	auto *layer = Adventure1::create();
	scene->addChild(layer);

	return scene;
}

Adventure1::Adventure1() {
	/*life = Adventure::getLife;
	level = Adventure::level;
	attack = Adventure::attack;
	experience = Adventure::experience;*/
}

// ʵ���ƶ��ĺ�����ÿ���ƶ�ʱ�¼��������жϿ��Լ������
void Adventure1::move(Point direct) {
	//bool flag = true;
	Point curPos = player->getPosition();
	Point nextPos = curPos + direct;

	// ��������Χǽ�Ϳ����ƶ�
	Vector<Sprite*>::iterator it = v_wall.begin();
	for (; it != v_wall.end(); it++) {
		if ((*it)->getPosition() == nextPos)
			//flag = false;
			return;
	}

	judge("v_monster1", nextPos);
	judge("v_monster2", nextPos);
	judge("v_monster3", nextPos);
	judge("v_stone", nextPos);
	judge("v_black_hole", nextPos);
	judge("v_random", nextPos);
	judge("v_supply", nextPos);
	judge("v_destination", nextPos);

	int x = player->getPosition().x;
	int y = player->getPosition().y;

	statusLayer->setLabelLevel(level);
	statusLayer->setLabelAttack(attack);
	statusLayer->setLabelExp(experience, level);
	statusLayer->setLabelLife(life, level);

	// �ƶ�����һλ��
	if (whether_black_hole == true) {
		SimpleAudioEngine::getInstance()->playEffect("music/into_black_hole.wav");
		whether_black_hole = false;
		return;
	}
	//if (flag == true)
	SimpleAudioEngine::getInstance()->playEffect("music/player_move.wav");
	player->setPosition(nextPos);
}

void Adventure1::judge(string obj, Point nextPos) {
	if (obj == "v_monster1") {
		Vector<Sprite*>::iterator it1 = v_monster1.begin();
		for (; it1 != v_monster1.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				// ������1
				SimpleAudioEngine::getInstance()->playEffect("music/fight1.wav");
				statusLayer->setLabelInfo("A small monster");
				fightJudge((*it1), 1);
				it1 = v_monster1.erase(it1);
				break;
			}
	}

	if (obj == "v_monster2") {
		Vector<Sprite*>::iterator it = v_monster2.begin();
		for (; it != v_monster2.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight2.wav");
				statusLayer->setLabelInfo("A medium monster");
				fightJudge((*it), 2);
				it = v_monster2.erase(it);
				break;
			}
	}

	if (obj == "v_monster3") {
		Vector<Sprite*>::iterator it = v_monster3.begin();
		for (; it != v_monster3.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight3.wav");
				statusLayer->setLabelInfo("A large monster");
				fightJudge((*it), 3);
				it = v_monster3.erase(it);
				break;
			}
	}
	
	// �ж���ʯ������100Ѫ��
	if (obj == "v_stone") {
		Vector<Sprite*>::iterator it = v_stone.begin();
		for (; it != v_stone.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/meet_stone.wav");
				statusLayer->setLabelInfo("An aerolite");
				life -= 100;
				if (life <= 0)
					GameOver();
				(*it)->removeFromParentAndCleanup(true);
				it = v_stone.erase(it);
				break;
			}
	}
	// �жϲ������ָ���Ѫ
	if (obj == "v_supply") {
		Vector<Sprite*>::iterator it = v_supply.begin();
		for (; it != v_supply.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/cure.wav");
				statusLayer->setLabelInfo("A space station");
				life = lifeArray[level];
				(*it)->removeFromParentAndCleanup(true);
				it = v_supply.erase(it);
				break;
			}
	}

	// �жϺڶ�����ת����
	if (obj == "v_black_hole") {
		Vector<Sprite*>::iterator it = v_black_hole.begin();
		for (; it != v_black_hole.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				statusLayer->setLabelInfo("A black hole");
				BlackHole(nextPos, 0);
				// it = v_black_hole.erase(it);
				break;
			}
	}

	// �ж�����¼�
	if (obj == "v_random") {
		Vector<Sprite*>::iterator it = v_random.begin();
		for (; it != v_random.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/random.wav");
				JumpRandom(nextPos);
				(*it)->removeFromParentAndCleanup(true);
				it = v_random.erase(it);
				break;
			}
	}

	// ����涴�յ�
	if (obj == "v_destination")
		if (nextPos == goal->getPosition())
			ShowWin();

}


void Adventure1::BlackHole(Point nextPos, int version) {
	
	// ʵ�ֳ�����ת
	Scene * scene = Slide::createScene();
	TransitionJumpZoom * tjz = TransitionJumpZoom::create(1, scene);
	Director::getInstance()->pushScene(tjz);

	whether_black_hole = true;
	int j, i, player_id;
	i = rand() % (NUM_BLACK_HOLE-1);
	if (version == 0) {
		Vector<Sprite*>::iterator it = v_black_hole.begin();
		for (j = 0; it != v_black_hole.end(); it++, j++)
			if ((*it)->getPosition() == nextPos) {
				player_id = j;
				break;
			}
	for (j = 0, it = v_black_hole.begin(); it != v_black_hole.end(); it++, j++)
		if (j == ((player_id + 1 + i) % NUM_BLACK_HOLE)) {
			Point p = (*it)->getPosition();
			player->setPosition(p);
			experience += 50;
			levelJudge();
			break;
		}
	}
	else {
		Vector<Sprite*>::iterator it = v_black_hole.begin();
		for (j = 0, it = v_black_hole.begin(); it != v_black_hole.end(); it++, j++)
			if (j == i){
			Point p = (*it)->getPosition();
			player->setPosition(p);
			experience += 50;
			levelJudge();
			break;
		}
	}
}

	// ��������¼����ɵ�����ʾ
void Adventure1::JumpRandom(Point nextPos) {
	int i = rand() % 3;
	if (i == 0) {
		// �ڲ���Ա���ѣ�Ѫ������60
		statusLayer->setLabelInfo("Internal betray!\nDecrease 60 life value.");
		life -= 60;
		if (life <= 0)
			GameOver();
	}
	else if (i == 1) {
		// ʰ��̫��ˮ��������������5
		statusLayer->setLabelInfo("Increase 5 attack value!");
		attack += 5;
	}
	else if (i == 2) {
		// �����ڶ���������һ����
		statusLayer->setLabelInfo("A black hole!");
		BlackHole(nextPos, 1);

	}
}

void Adventure1::levelJudge() {
	if (experience >= expArray[level]) {
		experience -= expArray[level];
		int remain = attack - attackArray[level];
		level++;
		attack = attackArray[level]+remain;
		life = lifeArray[level];
	}
}

void Adventure1::fightJudge(Sprite* it_sprite, int num) {
	int _life, _attack;
	if (num == 1) {
		_life = MONSTER1_LIFE;
		_attack = MONSTER1_ATTACK;
	} else if (num == 2) {
		_life = MONSTER2_LIFE;
		_attack = MONSTER2_ATTACK;
	} else if (num == 3){
		_life = MONSTER3_LIFE;
		_attack = MONSTER3_ATTACK;
	}
	
	while (life > 0 && _life > 0) {
		life -= _attack;
		_life -= attack;
	}
	if (life <= 0)
		GameOver();
	else if (_life <= 0) {
		if (num == 1) {
			experience += MONSTER1_EXP;
			WarLayer::showWarWindow(this, "W I N", "Get 50 experience...");
		}
		else if (num == 2) {
			experience += MONSTER2_EXP;
			WarLayer::showWarWindow(this, "W I N", "Get 75 experience...");
		}
		else if (num == 3) {
			experience += MONSTER3_EXP;
			WarLayer::showWarWindow(this, "W I N", "Get 150 experience...");
		}
			
		levelJudge();
		it_sprite->removeFromParentAndCleanup(true);
	}
}


// ��tilemap�е������
Vector <Sprite *> Adventure1::loadFromMap(TMXTiledMap* tmx, string obj, string name, int DisX, int DisY) {
	//��tmx�л�ȡ�����
	TMXObjectGroup* object = tmx->getObjectGroup(obj);
	//�Ӷ�����л�ȡ��������
	ValueVector container = object->getObjects();
	//��������
	Vector<Sprite *> v;
	int x, y;
	for (auto obj : container){
		ValueMap values = obj.asValueMap();
		//��ȡ�ݺ������꣨cocos2dx���꣩
		x = values.at("x").asInt();
		y = values.at("y").asInt();
		Sprite* temp = Sprite::create(name);
		v.pushBack(temp);
		temp->setAnchorPoint(Vec2(0, 0));
		temp->setPosition(Point(x + DisX, y + DisY));
		this->addChild(temp, 1);
	}
	return v;
}

Scene* Adventure1::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto *layer = Adventure1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

/*
Adventure1::Adventure1()
{
	
}
*/

Adventure1::~Adventure1()
{

}

bool Adventure1::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	// ����ͼƬ���Ի�
	Sprite* background = Sprite::create("background2.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	initTouchEvent();
	
	loadObject();

	// �����¼�
	addKeyboardEvent();
	
	return true;
}



void Adventure1::initTouchEvent(){
	auto menu = Menu::create();
	menu->setPosition(visibleSize.width,0);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(menu,10);

	auto label_RS = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 35);
	auto button_rs = MenuItemLabel::create(label_RS, CC_CALLBACK_1(Adventure1::Restart, this));
	button_rs->setPosition(SIZE_WSAD * (-8) - 32, SIZE_WSAD * 1-15);
	button_rs->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	menu->addChild(button_rs);

	// ������һ�ŵ�ͼ�洢������ֵ
	Global * global = Global::getInstance();
	life = global->getLife();
	attack = global->getAttack();
	experience = global->getExperience();
	level = global->getLevel();
}

void Adventure1::loadObject(){
	//�����ļ�·�����ٵ�����Ƭ��ͼ
	TMXTiledMap* tmx = TMXTiledMap::create("final_map2.tmx");
	//����λ��
	tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//����ê��
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	int DisX = (visibleSize.width - tmx->getContentSize().width) / 2 - 64 * 2.5;
	int DisY = (visibleSize.height - tmx->getContentSize().height) / 2 - 64 * 4;
	//��ӵ���Ϸͼ���У�����0����Z�ᣨZ��͵Ļᱻ�ߵ��ڵ���
	this->addChild(tmx, 0);

	//��tmx�л�ȡ�����player
	TMXObjectGroup* object3 = tmx->getObjectGroup("player");
	//�Ӷ�����л�ȡ��������
	ValueVector container3 = object3->getObjects();
	//��������
	int x, y;
	for (auto obj : container3){
		ValueMap values = obj.asValueMap();
		//��ȡ�ݺ������꣨cocos2dx���꣩
		x = values.at("x").asInt();
		y = values.at("y").asInt();
		Sprite* temp = Sprite::create("player2.png");
		temp->setAnchorPoint(Vec2(0, 0));
		temp->setPosition(Point(x + DisX, y + DisY));
		player = temp;
		this->addChild(temp, 5);
	}

	TMXObjectGroup* object2 = tmx->getObjectGroup("destination");
	//�Ӷ�����л�ȡ��������
	ValueVector container2 = object2->getObjects();
	//��������
	for (auto obj : container2){
		ValueMap values = obj.asValueMap();
		//��ȡ�ݺ������꣨cocos2dx���꣩
		x = values.at("x").asInt();
		y = values.at("y").asInt();
		Sprite* temp = Sprite::create("goal.png");
		temp->setAnchorPoint(Vec2(0, 0));
		temp->setPosition(Point(x + DisX, y + DisY));
		goal = temp;
		this->addChild(temp, 1);
	}

	// ��ʾ����ֵ/������/����ֵ��ͼ��
	Sprite* label_life = Sprite::create("label_life.png");
	label_life->setPosition(55, 64 * 6 - 10);
	addChild(label_life, 7);
	Sprite* label_attack = Sprite::create("label_attack.png");
	label_attack->setPosition(55, 64 * 5);
	addChild(label_attack, 7);
	Sprite* label_level = Sprite::create("label_level.png");
	label_level->setPosition(55, 64 * 4 + 18);
	addChild(label_level, 7);
	Sprite* label_exp = Sprite::create("label_exp.png");
	label_exp->setPosition(55, 64 * 3 + 30);
	addChild(label_exp, 7);

	// ������������Ӧ��vector��
	v_wall = loadFromMap(tmx, "wall", "floor.png", DisX, DisY);
	v_stone = loadFromMap(tmx, "stone", "stone1.png", DisX, DisY);
	v_monster1 = loadFromMap(tmx, "monster1", "monster2.png", DisX, DisY);
	v_monster2 = loadFromMap(tmx, "monster2", "monster1.png", DisX, DisY);
	v_monster3 = loadFromMap(tmx, "monster3", "monster3.png", DisX, DisY);
	v_black_hole = loadFromMap(tmx, "black_hole", "black_hole.png", DisX, DisY);
	v_destination = loadFromMap(tmx, "worm_hole", "worm_stone.png", DisX, DisY);
	v_random = loadFromMap(tmx, "random", "random.png", DisX, DisY);
	v_supply = loadFromMap(tmx, "supply", "supply_space.png", DisX, DisY);
	
	statusLayer = StatusLayer::createLayer();
	statusLayer->setLabelInfo("hello");
	statusLayer->setLabelLevel(level);
	statusLayer->setLabelAttack(attack);
	statusLayer->setLabelExp(experience, level);
	statusLayer->setLabelLife(life, level);
	statusLayer->setOpacity(0.5);
	statusLayer->setContentSize(Size(300, 300));
	statusLayer->setBackground("layers/InfoLayer.png");
	statusLayer->setCascadeOpacityEnabled(true);
	statusLayer->setOpacity(255 * 0.6);
	statusLayer->setPosition(statusLayer->getContentSize().width / 2, visibleSize.height / 2);
	this->addChild(statusLayer, 5);
}

void Adventure1::onRightPressed(Ref* sender)
{
	// ���°���d���¼�ʵ��
	// �ж��Ƿ����(��ǽʱ������)
	Point direct = Vec2(64, 0);
	move(direct);
}

void Adventure1::onLeftPressed(Ref* sender)
{
	// ���°���a���¼�ʵ��
	// �ж��Ƿ����(��ǽʱ������)
	Point direct = Vec2(-64, 0);
	move(direct);
}

void Adventure1::onUpPressed(Ref* sender)
{
	//���°���w���¼�ʵ��
	// �ж��Ƿ����(��ǽʱ������)
	Point direct = Vec2(0, 64);
	move(direct);
}

void Adventure1::onDownPressed(Ref* sender)
{
	//���°���s���¼�ʵ��
	// �ж��Ƿ����(��ǽʱ������)
	Point direct = Vec2(0, -64);
	move(direct);
}

void Adventure1::Restart(Ref* sender) {

	auto scene = Scene::create();
	auto *layer = Adventure1::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

void Adventure1::ShowWin() {
	// ����ʤ���Ի��򣬿���ѡ�����¿�ʼ
	DialogLayer::showDialogLayer(this, "THE END\nHero, you save the earth!!", "Restart", menu_selector(Adventure1::playAgain1), "Quit", menu_selector(Adventure1::endGame), DialogLayer::STATUS::WIN);
}

void Adventure1::GameOver() {
	// ����ʧ�ܶԻ��򣬿���ѡ�����¿�ʼ
	DialogLayer::showDialogLayer(this, "L O S E ! ! !", "Restart", menu_selector(Adventure1::playAgain2), "Quit", menu_selector(Adventure1::endGame));
}

void Adventure1::keyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_A || keyCode == EventKeyboard::KeyCode::KEY_KP_LEFT) {
		onLeftPressed(this);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_D || keyCode == EventKeyboard::KeyCode::KEY_KP_RIGHT) {
		onRightPressed(this);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_W || keyCode == EventKeyboard::KeyCode::KEY_KP_UP) {
		onUpPressed(this);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_S || keyCode == EventKeyboard::KeyCode::KEY_KP_DOWN) {
		onDownPressed(this);
	}
}
void Adventure1::keyRelease(EventKeyboard::KeyCode keyCode, Event *event) {

}

void Adventure1::addKeyboardEvent() {
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Adventure1::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Adventure1::keyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

// �ӵ�һ�ؿ�ʼ��������Ϸʤ����
void Adventure1::playAgain1(Ref *ref) {
	Scene * scene = Adventure::scene();
	Director::getInstance()->replaceScene(scene);
}

// �ӵڶ��ؿ�ʼ��������Ϸʧ��ʱ
void Adventure1::playAgain2(Ref *ref) {
	Scene * scene = Adventure1::scene();
	Director::getInstance()->replaceScene(scene);
}

void Adventure1::endGame(Ref * ref) {
	Director::getInstance()->end();
}