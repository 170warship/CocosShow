//
//  ShowMove.cpp
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//
#include "ShowMove.h"
#include "SelectScene.h"
class ShowMoveInit{
public:
    ShowMoveInit(){
        CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader("ShowMove", ShowMoveLoader::loader());
    }
};
static ShowMoveInit showMoveInitInstance;

CCScene* ShowMove::scene()
{
    // 'scene' is an autorelease object
    CCNodeLoaderLibrary * ccbLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccbLib->registerCCNodeLoader("ShowMove", ShowMoveLoader::loader());
    CCBReader *ccbReader = new CCBReader(ccbLib);
    CCScene *scene = ccbReader->createSceneWithNodeGraphFromFile("ShowMove.ccbi");
    
    ccbReader->release();
    return scene;
}


bool ShowMove::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}

void ShowMove::onEnter(){
    //    ((CCBAnimationManager*)m_pDragon->getUserObject())->runAnimationsForSequenceNamed("Flying");
    
    CCLayer::onEnter();
    this->setTouchEnabled(true);
    
    showButton();
    
}

bool ShowMove::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode){
    if ( !strcmp(pMemberVariableName, "dragon") ) {
        m_pDragon = (Dragon*)pNode;
        return true;
    }
    return true;
}



SEL_MenuHandler ShowMove::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName){
    return NULL;
}


SEL_CCControlHandler ShowMove::onResolveCCBCCControlSelector(CCObject * pTarget,const char * pSelectorName){
    return NULL;
}

void ShowMove::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    
    m_startpPoint = point;
    
    m_bTouchIn = true;
    
    //    m_pDragon->setPositionX(point.x);
}
void ShowMove::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    
    if (m_bMoved) {
        float tangle = ccpDistance(m_startpPoint, point)*(m_startpPoint.x>point.x?-1:1);
        
        m_pDragon->runAction(CCRotateBy::create(0.6, tangle));
    }else{
//        m_pDragon->runAction(CCMoveTo::create(0.6,point));
        m_pDragon->runAction( CCEaseBackOut::create(CCMoveTo::create(0.6,point)) );
         printf("MoveTo: x:%f  y:%f\n", point.x, point.y);
    }

    m_bTouchIn = false;
    m_bMoved = false;
    
}
void ShowMove::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    m_bMoved = true;
}

void ShowMove::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    m_bTouchIn = false;
    m_bMoved = false;
}


void ShowMove::showButton(){
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(ShowMove::goBack));
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
}


void ShowMove::goBack(CCObject* sender){
    CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipAngular::create(0.9, SelectScene::scene()) );
}
