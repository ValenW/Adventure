#include "HelloWorldScene.h"
#include "Adventure.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
#pragma execution_character_set("utf-8") 
USING_NS_CC;

const int FONT_SIZE = 45;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	totalTime = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	auto label = Label::createWithTTF("Adventure", "fonts/Marker Felt.ttf", FONT_SIZE * 2);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    // add the label as a child to this layer
    this->addChild(label, 1);

	auto item1 = MenuItemLabel::create(Label::createWithTTF("Play\n", "fonts/Marker Felt.ttf", FONT_SIZE), CC_CALLBACK_1(HelloWorld::PlayMenu, this));
	auto item2 = MenuItemLabel::create(Label::createWithTTF("Game Background\n", "fonts/Marker Felt.ttf", FONT_SIZE), CC_CALLBACK_1(HelloWorld::About, this));
	auto item3 = MenuItemLabel::create(Label::createWithTTF("Exit\n", "fonts/Marker Felt.ttf", FONT_SIZE), CC_CALLBACK_1(HelloWorld::Exit, this));

	// create menu, it's an autorelease object
	auto menu = Menu::create(item1, item2, item3, NULL);
	menu->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	menu->alignItemsVerticallyWithPadding(label->getContentSize().height/2);
	this->addChild(menu, 2);


    // add bg
	/*auto bgsprite = Sprite::create("background.jpg");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds = bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1 / odds);
	bgsprite->setPosition(Vec2(visibleSize / 2) + origin);
	this->addChild(bgsprite, 0);*/

	// Ìí¼ÓÁ£×Ó±³¾°
	ParticleSystemQuad * leaveStorm = ParticleSystemQuad::create("LeaveStorm.plist");
	leaveStorm->setPosition(visibleSize / 2);
	this->addChild(leaveStorm);

	// ²¥·ÅÒôÀÖ
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/main_menu.mp3", true);

	//
	//
    return true;
}

void HelloWorld::PlayMenu(Ref *ref){
	SimpleAudioEngine::getInstance()->playEffect("music/main_menu_play.wav");
	Scene * scene = Adventure::scene();
	TransitionShrinkGrow *tsg = TransitionShrinkGrow::create(1.0f, scene);
	Director::getInstance()->pushScene(tsg);
	Director::getInstance()->replaceScene(tsg);
}

void HelloWorld::About(Ref *ref){
	SimpleAudioEngine::getInstance()->playEffect("music/main_menu_about.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("In the year of 2500, the earth is surrounded by Santi Anamy.\nThe enemy are so powerful that human faced with a destroyed fate.\n You are a warrior that human has selected to find a new planet.\nYou should beat the monsters and go through the wormstone in order to go farther.\nDon't be afraid.Good luck!", "fonts/Marker Felt.ttf", FONT_SIZE / 2);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height - 450));
	this->addChild(label, 1);
}

void HelloWorld::Exit(Ref *ref){
	SimpleAudioEngine::getInstance()->playEffect("music/main_menu_exit.wav");
	//schedule(schedule_selector(HelloWorld::updateTime), 0.1f);
	//Adventure::resumeEventListener();
	Director::getInstance()->end();
}

void HelloWorld::updateTime(float dt){
	totalTime += dt;
	char t[10];
	sprintf(t, "%.1f", totalTime);
	timerStr->setString(t);
}