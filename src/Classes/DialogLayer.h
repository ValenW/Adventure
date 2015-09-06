//
//  DialogLayer.h
//  ModalDialogDemo
//
//  Created by Tom on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ModalDialogDemo_DialogLayer_h
#define ModalDialogDemo_DialogLayer_h


#include "cocos2d.h"
#include "Adventure.h"

USING_NS_CC;

class DialogLayer: public CCLayerColor
{
	
public:
	enum STATUS{WIN,FAIL,NONE};
    DialogLayer();
    ~DialogLayer();
    
    virtual bool init();
    // 初始化对话框内容
    void initDialog();
    
	CREATE_FUNC(DialogLayer);
    
	static DialogLayer * createLayer();

    void onEnter();
    void onExit();
    
    virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void okMenuItemCallback(CCObject *pSender);
    void cancelMenuItemCallback(CCObject *pSender);
	
	Menu* getMenu();

	static void showDialogLayer(Layer *layer, String title, String leftString = "", SEL_MenuHandler leftHandler = NULL, String rightString = "", SEL_MenuHandler rightHandler = NULL, DialogLayer::STATUS status = DialogLayer::STATUS::NONE);
private:
	static DialogLayer * dialogLayer;    
	// 模态对话框菜单
	Menu *m_pMenu;
	// 记录菜单点击
	bool m_bTouchedMenu;

};

#endif
