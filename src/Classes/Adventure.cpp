#include "Adventure.h"
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
// add
const float MOVE_TIME = 0.3f;
const int expArray[10] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
const int attackArray[10] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
const int lifeArray[10] = { 60, 70, 90, 110, 130, 150, 180, 220, 250, 300};
//const int lifeArray[10] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };

Adventure * Adventure::adventure = NULL;

// 实现移动的函数。每次移动时事件触发的判断可以加在这里。
void Adventure::move(Point direct) {
	//bool flag = true;
	Point curPos = player->getPosition();
	Point nextPos = curPos + direct;

	// 不是三体围墙就可以移动
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
	judge("v_destination", nextPos);
	judge("v_random", nextPos);
	judge("v_supply", nextPos);

	int x = player->getPosition().x;
	int y = player->getPosition().y;

	statusLayer->setLabelLevel(level);
	statusLayer->setLabelAttack(attack);
	statusLayer->setLabelExp(experience, level);
	statusLayer->setLabelLife(life, level);

	// 移动到下一位置
	if (whether_black_hole == true) {
		SimpleAudioEngine::getInstance()->playEffect("music/into_black_hole.wav");
		whether_black_hole = false;
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("music/player_move.wav");
	player->setPosition(nextPos);
}

void Adventure::judge(string obj, Point nextPos) {
	if (obj == "v_monster1") {
		Vector<Sprite*>::iterator it1 = v_monster1.begin();
		for (; it1 != v_monster1.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				// 遇见怪1
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
	
	// 判断陨石，减少100血量
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
	// 判断补给，恢复满血
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

	// 判断黑洞，跳转场景
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

	// 判断随机事件
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

	// 到达虫洞终点
	if (obj == "v_destination") {
		Vector<Sprite*>::iterator it = v_destination.begin();
		for (; it != v_destination.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				NextMap();
				// it = v_destination.erase(it);
				break;
			}
	}
}


void Adventure::BlackHole(Point nextPos, int version) {
	
	// 实现场景跳转
	Scene * scene = Slide::createScene();/*
	TransitionJumpZoom * tjz = TransitionJumpZoom::create(1, scene);*/
	//Director::getInstance()->pushScene(tjz);
	Director::getInstance()->pushScene(Util::getTransitionSceneRandom(scene));
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

	// 以下随机事件均可弹窗显示
void Adventure::JumpRandom(Point nextPos) {
	int i = rand() % 3;
	if (i == 0) {
		// 内部成员背叛，血量减少60
		statusLayer->setLabelInfo("Internal betray!\nDecrease 60 life value.");
		life -= 60;
		if (life <= 0)
			GameOver();
	}
	else if (i == 1) {
		// 拾获太空水晶，攻击力增加5
		statusLayer->setLabelInfo("Increase 5 attack value!");
		attack += 5;
	}
	else if (i == 2) {
		// 遭遇黑洞，进入另一场景
		statusLayer->setLabelInfo("A black hole!");
		BlackHole(nextPos, 1);

	}
}

void Adventure::levelJudge() {
	if (experience >= expArray[level]) {
		experience -= expArray[level];
		int remain = attack - attackArray[level];
		level++;
		attack = attackArray[level] + remain;
		life = lifeArray[level];
	}
}

void Adventure::fightJudge(Sprite* it_sprite, int num) {
	int _life, _attack;
	if (num == 1) {
		_life = MONSTER1_LIFE;
		_attack = MONSTER1_ATTACK;
	} else if (num == 2) {
		_life = MONSTER2_LIFE;
		_attack = MONSTER2_ATTACK;
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


// 从tilemap中导入对象
Vector <Sprite *> Adventure::loadFromMap(TMXTiledMap* tmx, string obj, string name, int DisX, int DisY) {
	//从tmx中获取对象层
	TMXObjectGroup* object = tmx->getObjectGroup(obj);
	//从对象层中获取对象数组
	ValueVector container = object->getObjects();
	//遍历对象
	Vector<Sprite *> v;
	int x, y;
	for (auto obj : container){
		ValueMap values = obj.asValueMap();
		//获取纵横轴坐标（cocos2dx坐标）
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

Scene* Adventure::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	Adventure::adventure = Adventure::create();
	
	// add layer as a child to scene
	scene->addChild(Adventure::adventure);

	// return the scene
	return scene;
}

Adventure::Adventure()
{
	
}

Adventure::~Adventure()
{

}

bool Adventure::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	// 背景图片可以换
	//Sprite* background = Sprite::create("background2.jpg");
	//background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//addChild(background, 0);

	initTouchEvent();
	
	loadObject();

	// 键盘事件
	addKeyboardEvent();
	
	// 添加银河背景 添加.plist时记得保证有textureFileName或textureImageData标签，添加了就要设置，且值不能为空
	auto galaxy = ParticleSystemQuad::create("Galaxy.plist");
	galaxy->setPosition(visibleSize / 2);
	this->addChild(galaxy, 0);

	// 添加背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/map_music0.mp3", true);

	return true;
}



void Adventure::initTouchEvent(){
	/*auto menu = Menu::create();
	menu->setPosition(visibleSize.width,0);
	menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(menu,10);

	auto label_RS = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 35);
	auto button_rs = MenuItemLabel::create(label_RS, CC_CALLBACK_1(Adventure::Restart, this));
	button_rs->setPosition(SIZE_WSAD * (-8) - 32, SIZE_WSAD * 1-15);
	button_rs->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	menu->addChild(button_rs);*/
}

void Adventure::loadObject(){
	//根据文件路径快速导入瓦片地图
	TMXTiledMap* tmx = TMXTiledMap::create("final_map1.tmx");
	//设置位置
	tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//设置锚点
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	int DisX = (visibleSize.width - tmx->getContentSize().width) / 2 - 64 * 2.5;
	int DisY = (visibleSize.height - tmx->getContentSize().height) / 2 - 64 * 4;
	//添加到游戏图层中，其中0代表Z轴（Z轴低的会被高的遮挡）
	this->addChild(tmx, 0);

	//从tmx中获取对象层player
	TMXObjectGroup* object3 = tmx->getObjectGroup("player");
	//从对象层中获取对象数组
	ValueVector container3 = object3->getObjects();
	//遍历对象
	int x, y;
	for (auto obj : container3){
		ValueMap values = obj.asValueMap();
		//获取纵横轴坐标（cocos2dx坐标）
		x = values.at("x").asInt();
		y = values.at("y").asInt();
		Sprite* temp = Sprite::create("player2.png");
		temp->setAnchorPoint(Vec2(0, 0));
		temp->setPosition(Point(x + DisX, y + DisY));
		player = temp;
		this->addChild(temp, 5);
	}

	// 显示生命值/攻击力/经验值的图像
	Sprite* label_life = Sprite::create("label_life.png");
	label_life->setPosition(55, 64*6-10);
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
	

	// 导入对象后存入对应的vector中
	v_wall = loadFromMap(tmx, "wall", "floor.png", DisX, DisY);
	v_stone = loadFromMap(tmx, "stone", "stone1.png", DisX, DisY);
	v_monster1 = loadFromMap(tmx, "monster1", "monster2.png", DisX, DisY);
	v_monster2 = loadFromMap(tmx, "monster2", "monster1.png", DisX, DisY);
	//v_monster3 = loadFromMap(tmx, "monster3", "monster3.png", DisX, DisY);
	v_black_hole = loadFromMap(tmx, "black_hole", "black_hole.png", DisX, DisY);
	v_destination = loadFromMap(tmx, "worm_hole", "worm_stone.png", DisX, DisY);
	v_random = loadFromMap(tmx, "random", "random.png", DisX, DisY);
	v_supply = loadFromMap(tmx, "supply", "supply_space.png", DisX, DisY);

	statusLayer = StatusLayer::createLayer();
	statusLayer->setLabelInfo("hello");
	statusLayer->setLabelLevel(level);
	statusLayer->setLabelAttack(attack);
	statusLayer->setLabelExp(experience,level);
	statusLayer->setLabelLife(life, level);
	statusLayer->setContentSize(Size(300, 300));
	statusLayer->setBackground("layers/InfoLayer.png");
	statusLayer->setCascadeOpacityEnabled(true);
	statusLayer->setOpacity(255 * 0.6);
	//statusLayer->setOpacity(255*0.8);
	statusLayer->setPosition(statusLayer->getContentSize().width / 2, visibleSize.height / 2);
	this->addChild(statusLayer, 5);



}

void Adventure::onRightPressed(Ref* sender)
{
	// 按下按键d的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(64, 0);
	move(direct);
}

void Adventure::onLeftPressed(Ref* sender)
{
	// 按下按键a的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(-64, 0);
	move(direct);
}

void Adventure::onUpPressed(Ref* sender)
{
	//按下按键w的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(0, 64);
	move(direct);
}

void Adventure::onDownPressed(Ref* sender)
{
	//按下按键s的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(0, -64);
	move(direct);
}

void Adventure::Restart(Ref* sender) {

	auto scene = Scene::create();
	auto *layer = Adventure::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

void Adventure::NextMap() {
	
	// 暂存各项属性值
	Global * global = Global::getInstance();
	global->setLife(life);
	global->setLevel(level);
	global->setExperience(experience);
	global->setAttack(attack);
	// 简单存取
	// 实现场景跳转
	Scene * scene = Adventure1::createScene();
	//TransitionJumpZoom * tjz = TransitionJumpZoom::create(1, scene);
	TransitionShrinkGrow *tsg = TransitionShrinkGrow::create(1.0f, scene);
	//Director::getInstance()->pushScene(tsg);
	Director::getInstance()->replaceScene(tsg);
	/*Director::getInstance()->pushScene(tjz);*/
}

void Adventure::GameOver() {
	// 弹出失败对话框，可以选择重新开始
	//WarLayer::showWarWindow(this, "L O S E", "Who can save the earth?...");
	//DialogLayer *dia = DialogLayer::create();
	//this->addChild(dia, 6);
	DialogLayer::showDialogLayer(this, "L O S E ! ! !", "Restart", menu_selector(Adventure::playAgain), "Quit", menu_selector(Adventure::endGame));
}

void Adventure::keyPressed(EventKeyboard::KeyCode keyCode, Event *event) {

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

void Adventure::keyRelease(EventKeyboard::KeyCode keyCode, Event *event) {

}

void Adventure::addKeyboardEvent() {
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Adventure::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Adventure::keyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Adventure::playAgain(Ref *ref) {
	Adventure::resumeEventListener();
	Scene * scene = Adventure::scene();
	Director::getInstance()->replaceScene(scene);
}

void Adventure::endGame(Ref * ref) {
	Adventure::resumeEventListener();
	Director::getInstance()->end();
}

//EventListenerKeyboard * Adventure::getKeyboardListener() {
//	return keyboardListener;
//}

void Adventure::resumeEventListener() {
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(Adventure::adventure);
}