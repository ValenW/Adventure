//
//  DialogLayer.cpp
//  ModalDialogDemo
//
//  Created by Tom on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "DialogLayer.h"

DialogLayer * DialogLayer::dialogLayer = NULL;

DialogLayer::DialogLayer()
{
}

DialogLayer::~DialogLayer()
{
	DialogLayer::dialogLayer = NULL;
}

DialogLayer * DialogLayer::createLayer() {
	return DialogLayer::create();
}

bool DialogLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
        
        this->initDialog();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void DialogLayer::initDialog()
{
	m_pMenu = Menu::create(NULL);
}

void DialogLayer::onEnter()
{
    CCLayerColor::onEnter();
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority - 1, true);
}

void DialogLayer::onExit()
{
    CCLayerColor::onExit();
    //CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

bool DialogLayer::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DialogLayer::onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void DialogLayer::onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::onTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    // 点击确定就退出（拷贝的原有方法）
    //CCDirector::sharedDirector()->end();
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif
}

void DialogLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
    //this->removeFromParentAndCleanup(false);
	/*auto scene = Scene::create();
	auto *layer = Adventure::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);*/
}



void DialogLayer::showDialogLayer(Layer *layer, String title, String leftString, SEL_MenuHandler leftHandler, String rightString, SEL_MenuHandler rightHandler, DialogLayer::STATUS status) {
	if (dialogLayer != NULL) {
		dialogLayer->removeFromParentAndCleanup(true);
		//dialogLayer = NULL;
	}

	dialogLayer = DialogLayer::create();

	Size winSize = Director::getInstance()->getWinSize();

	
	
	LabelTTF *label = LabelTTF::create(title.getCString(), "", 48);
	label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
	dialogLayer->addChild(label);

	MenuItemFont *leftMenuItem;
	MenuItemFont *rightMenuItem;
	Menu * m_pMenu = dialogLayer->getMenu();

	if (leftHandler != NULL) {
		leftMenuItem = MenuItemFont::create(leftString.getCString(), dialogLayer, leftHandler);
		leftMenuItem->setPosition(Point(winSize.width / 2 - 100, winSize.height / 2 - 50));
		m_pMenu->addChild(leftMenuItem);
	}
	if (rightHandler != NULL) {
		rightMenuItem = MenuItemFont::create(rightString.getCString(), dialogLayer, rightHandler);
		rightMenuItem->setPosition(Point(winSize.width / 2 + 100, winSize.height / 2 - 50));
		m_pMenu->addChild(rightMenuItem);
	}
	m_pMenu->setPosition(Point::ZERO);
	dialogLayer->addChild(m_pMenu);
	
	Sprite *sprite_win;

	switch (status) {
	case DialogLayer::STATUS::WIN:
		sprite_win = Sprite::create("layers/win.png");
		sprite_win->setPosition(Point(winSize.width / 2, winSize.height / 2 + 200));
		dialogLayer->addChild(sprite_win, 2);
		break;
	case DialogLayer::STATUS::FAIL:
		sprite_win = Sprite::create("layers/fail.png");
		sprite_win->setPosition(Point(winSize.width / 2, winSize.height / 2 + 200));
		dialogLayer->addChild(sprite_win, 2);
		break;
	case DialogLayer::STATUS::NONE:
		break;
	default:
		break;
	}
	
	
	EventListenerTouchOneByOne * listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *, Event *)
	{
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, dialogLayer);

	layer->addChild(dialogLayer, 10);
	//layer->getKeyboardListener();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(layer);
}


Menu* DialogLayer::getMenu() {
	return m_pMenu;
}