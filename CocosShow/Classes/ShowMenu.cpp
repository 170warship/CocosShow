//
//  ShowMenu.cpp
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//

#include "ShowMenu.h"
#include "CCBAnimationManager.h"
#include "SelectScene.h"

class ShowMenuInit{
public:
    ShowMenuInit(){
        CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader("ShowMenu", ShowMenuLoader::loader());
    }
};
static ShowMenuInit showMenuInitInstance;

CCScene* ShowMenu::scene()
{
    // 'scene' is an autorelease object
    CCNodeLoaderLibrary * ccbLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccbLib->registerCCNodeLoader("ShowMenu", ShowMenuLoader::loader());
    CCBReader *ccbReader = new CCBReader(ccbLib);
    CCScene *scene = ccbReader->createSceneWithNodeGraphFromFile("ShowMenu.ccbi");

    ccbReader->release();
    return scene;
}


bool ShowMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}

void ShowMenu::onEnter(){
//    ((CCBAnimationManager*)m_pDragon->getUserObject())->runAnimationsForSequenceNamed("Flying");
    
    CCLayer::onEnter();
    
}

bool ShowMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode){
    if ( !strcmp(pMemberVariableName, "dragon") ) {
        m_pDragon = (Dragon*)pNode;
        return true;
    }
    return true;
}

SEL_MenuHandler ShowMenu::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "playTimeLine1:", ShowMenu::playTimeLine1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "playTimeLine2:", ShowMenu::playTimeLine2);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "playTimeLine3:", ShowMenu::playTimeLine3);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "goBack:", ShowMenu::goBack);
}


SEL_CCControlHandler ShowMenu::onResolveCCBCCControlSelector(CCObject * pTarget,const char * pSelectorName){
    return NULL;
}

void ShowMenu::goBack(cocos2d::CCObject *sender){
    CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
}

void ShowMenu::playTimeLine1(cocos2d::CCObject *sender){
    ((CCBAnimationManager*)m_pDragon->getUserObject())->runAnimationsForSequenceNamed("Flying");
}

void ShowMenu::playTimeLine2(cocos2d::CCObject *sender){
    ((CCBAnimationManager*)m_pDragon->getUserObject())->runAnimationsForSequenceNamed("Hit");
}

void ShowMenu::playTimeLine3(cocos2d::CCObject *sender){
    ((CCBAnimationManager*)m_pDragon->getUserObject())->runAnimationsForSequenceNamed("Swiming");
}