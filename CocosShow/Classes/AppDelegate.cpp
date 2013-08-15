//
//  CocosShowAppDelegate.cpp
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ShowMenu.h"
#include "SelectScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize lsSize = CCSize(320, 480);//CCDirector::sharedDirector()->getWinSize();
    
    float scaleX = (float) frameSize.width / lsSize.width;
    float scaleY = (float) frameSize.height / lsSize.height;
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize( 320, 480,
                                                           kResolutionExactFit);

    // create a scene. it's an autorelease object
    CCScene *pScene = SelectScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
