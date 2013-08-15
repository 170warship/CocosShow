//
//  SelectScene.cpp
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//
#include "SelectScene.h"
#include "ShowMenu.h"
#include "ShowMove.h"
#include "GameScene.h"
class SelectSceneInit{
public:
    SelectSceneInit(){
        CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader("SelectScene", SelectSceneLoader::loader());
    }
};
static SelectSceneInit selectSceneInitInstance;

CCScene* SelectScene::scene()
{
    // 'scene' is an autorelease object
    CCNodeLoaderLibrary * ccbLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccbLib->registerCCNodeLoader("SelectScene", ShowMenuLoader::loader());
    CCBReader *ccbReader = new CCBReader(ccbLib);
    CCScene *scene = ccbReader->createSceneWithNodeGraphFromFile("SelectScene.ccbi");
    
    ccbReader->release();
    return scene;
}


bool SelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}

void SelectScene::onEnter(){
    //    ((CCBAnimationManager*)m_pDragon->getUserObject())->runAnimationsForSequenceNamed("Flying");
    
    CCLayer::onEnter();
    
}

bool SelectScene::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode){
    return false;
}



SEL_MenuHandler SelectScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "sceneAction:", SelectScene::sceneAction);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "sceneTransition:", SelectScene::sceneTransition);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "sceneTimeLine:", SelectScene::sceneTimeLine);
}


SEL_CCControlHandler SelectScene::onResolveCCBCCControlSelector(CCObject * pTarget,const char * pSelectorName){
    return NULL;
}

void SelectScene::sceneTimeLine(CCObject* sender){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(0.6, ShowMenu::scene()) );
}
void SelectScene::sceneAction(CCObject* sender){
    CCDirector::sharedDirector()->replaceScene( CCTransitionJumpZoom::create(0.6,ShowMove::scene()) );
}
void SelectScene::sceneTransition(CCObject* sender){
    CCDirector::sharedDirector()->replaceScene( CCTransitionMoveInL::create(0.8, GameScene::scene() ) );
}

