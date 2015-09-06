#include "AppDelegate.h"
#include "MainMenu.h"
#include "Adventure.h"
#include "Slide.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Do Or Die");
        director->setOpenGLView(glview);
    }

	// Ô¤¼ÓÔØÒôÐ§ÒôÀÖ
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/map_music0.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/main_menu.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/main_menu_play.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/main_menu_about.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/main_menu_exit.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/fight0.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/fight1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/fight2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/fight3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/cure.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/win.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/fail.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/instance_fly.wav");
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = MainMenu::createScene();
	TransitionShrinkGrow *tsg = TransitionShrinkGrow::create(1.0f, scene);
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
