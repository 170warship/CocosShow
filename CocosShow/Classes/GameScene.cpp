//
//  GameScene.cpp
//  CocosShow
//
//  Created by 170warship on 8/8/13.
//
//

#include "GameScene.h"
#include "Bomb.h"
#include "Explosion.h"
CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    
    GameScene* game = new GameScene();
    game->setPosition(0, 0);
    game->setContentSize(CCDirector::sharedDirector()->getWinSize());
    
    CCScene *scene = new CCScene();
    scene->addChild(game);
    
    return scene;
}

GameScene::GameScene(){
    init();
    m_pAemoArray = new CCArray(1);
    m_pEnimyArray = new CCArray(1);
    
    m_winSize = CCDirector::sharedDirector()->getWinSize();
}

GameScene::~GameScene(){
    m_pAemoArray->release();
    m_pEnimyArray->release();
    m_pDragon->release();
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}


void GameScene::onEnter(){
    CCLayer::onEnter();
    m_pDragon = (Dragon*)Dragon::node();
    this->addChild(m_pDragon);
    m_pDragon->setPosition(10, 20);
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    m_iOldFrame = 0;
    m_iOldFireFrame = 0;
    m_iFrame = 0;
}


void GameScene::fire(){
    CCSprite* pFire = CCSprite::create("fire.png");
    pFire->setScale(0.2);
    //pFire->setContentSize(CCSizeMake(10, 20));
    pFire->setPosition(m_pDragon->getPosition());
    this->addChild(pFire);
    m_pAemoArray->addObject(pFire);
}

void GameScene::addEnimy(){
    CCNode* bomb = Bomb::node();
    
    bomb->setPosition(random()%lrintf(m_winSize.width), m_winSize.height);
    
    this->addChild(bomb);
    m_pEnimyArray->addObject(bomb);
}


void GameScene::update(float delta){
    
    if ( (m_iOldFrame & 0x0D) == 0x0D) {
        m_iOldFrame = 0;
        fire();
    }
    
    if ( (m_iOldFireFrame & 0x13) == 0x13) {
        m_iOldFireFrame = 0;        
        addEnimy();
    }
    
    m_iOldFrame ++;
    m_iOldFireFrame ++;
    m_iFrame ++;
   
    
    
    CCObject* aemo = NULL;
    CCObject* removeObject = NULL;
    CCNode* node = NULL;
    CCArray* removeArray = new CCArray(1);
    CCObject* enimy = NULL;
    //敌人移动
    CCARRAY_FOREACH(m_pEnimyArray, enimy){        
        node = (CCNode*)enimy;
        node->setPositionY(node->getPositionY() -2);
    }
    
    //子弹移动
    CCARRAY_FOREACH(m_pAemoArray, aemo){
        ((CCNode*)aemo)->setPositionY(((CCNode*)aemo)->getPositionY() + 5);
        node = (CCNode*)aemo;
        if (node->getPositionY()>m_winSize.height) {
            removeArray->addObject(aemo);
            continue;
        }
        
        
        //碰撞检测
        CCARRAY_FOREACH(m_pEnimyArray, enimy){
            
            if ( ccpDistance(((CCNode*)enimy)->getPosition(), ((CCNode*)aemo)->getPosition() ) < (10 + 5)) {
//                printf("hit %d.  ", m_iFrame);
                removeArray->addObject(enimy);
                removeArray->addObject(aemo);
                
                CCNode* explosion = Explosion::node();
                explosion->setPosition(((CCNode*)enimy)->getPosition() );
                this->addChild(explosion);
                printf("aemo position y: %f. enimy position y:%f .\n", ((CCNode*)aemo)->getPositionY(), ((CCNode*)enimy)->getPositionY() );
                break;
            }
            
        }
    }
    
    
    CCARRAY_FOREACH(removeArray, removeObject){
        this->removeChild((CCNode*)removeObject);
        m_pAemoArray->removeObject(removeObject);
        m_pEnimyArray->removeObject(removeObject);
        removeObject->release();
    }
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    
    m_pDragon->setPosition(point);
    
    //    m_pDragon->setPositionX(point.x);
}


void GameScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    
    m_pDragon->setPosition(point);
    
    //    m_pDragon->setPositionX(point.x);
}