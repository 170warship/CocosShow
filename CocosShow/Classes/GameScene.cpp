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
#include "SelectScene.h"
CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    
    GameScene* game = new GameScene();
    game->setPosition(0, 0);
    game->setContentSize(CCDirector::sharedDirector()->getWinSize());
    
    game->m_pScoreLabel = CCLabelTTF::create("得分:", "Thonburi", 34);
    game->m_pScoreLabel->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height - 20) );

    CCLayerGradient* backgroundLayer = CCLayerGradient::create(ccc4(151, 222, 252, 255), ccc4(116, 171, 239, 255));
    backgroundLayer->setPosition(0, 0);
    backgroundLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());
    backgroundLayer->addChild(game->m_pScoreLabel);
    
    CCScene *scene = new CCScene();
    scene->addChild(backgroundLayer);
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
    m_iOldScore = 0;
    m_iScore = 0;
    m_bIsEnd = false;
    
    m_iEnimySpeed = 4;
}


void GameScene::fire(){
    CCSprite* pFire = CCSprite::create("fire.png");
    pFire->setScale(0.18);
    //pFire->setContentSize(CCSizeMake(10, 20));
    CCPoint point = m_pDragon->getPosition();
    pFire->setPosition(ccp(point.x, point.y + 6));
    this->addChild(pFire);
    m_pAemoArray->addObject(pFire);
}

void GameScene::addEnimy(){
    CCNode* bomb = Bomb::node();
    
    bomb->setPosition(random()%lrintf(m_winSize.width), m_winSize.height);
    
    bomb->setUserData( (void*) (m_iEnimySpeed+random()%m_iEnimySpeed) );
    this->addChild(bomb);
    m_pEnimyArray->addObject(bomb);
}


void GameScene::update(float delta){
    if (m_bIsEnd) {
        return;
    }
    
    //龙的旋转度调整
    m_pDragon->setRotation(m_pDragon->getRotation()*0.7);
    
    //开火
    if ( (m_iOldFrame & 0x0D) == 0x0D) {
        m_iOldFrame = 0;
        fire();
    }
    
    //增加敌人
    if ( (m_iOldFireFrame & (0x18 - (m_iEnimySpeed -2)) ) == (0x18 - (m_iEnimySpeed-2)) ) {
        m_iOldFireFrame = 0;        
        addEnimy();
    }
    
    
    
    m_iOldFrame ++;
    m_iOldFireFrame ++;
    m_iFrame ++;
   
    //敌人增加速度
    if (m_iFrame % (60*20) == 0) {
        m_iEnimySpeed = m_iEnimySpeed > 10? 10:(m_iEnimySpeed+1);
    }
    
    CCObject* aemo = NULL;
    CCObject* removeObject = NULL;
    CCNode* node = NULL;
    CCArray* removeArray = new CCArray(1);
    CCObject* enimy = NULL;
    //敌人移动
    CCARRAY_FOREACH(m_pEnimyArray, enimy){
        node = (CCNode*)enimy;
        CCPoint enimyPoint = node->getPosition();
        
        if (enimyPoint.y < 0) {
            removeArray->addObject(enimy);
            continue;
        }
        
        //龙被击中
        if (ccpDistance( enimyPoint, m_pDragon->getPosition() ) < (5 + 16)) {
            CCNode* explosion = Explosion::node();
            explosion->setPosition( enimyPoint );
            this->addChild(explosion);
            m_bIsEnd = true;
            showButton();
            return;
        }
        
        node = (CCNode*)enimy;
        float speed = (int)(node->getUserData());
        node->setPositionY(node->getPositionY() -(speed/2.0));
        float enimyX = node->getPositionX();
        float dragonX=  m_pDragon->getPositionX();
        
        if (abs(dragonX - enimyX) < 60 && abs(dragonX - enimyX) > 15  ) {
            node->setPositionX( enimyX + ( (( dragonX - enimyX)>0?1:-1)*speed/14.0f) );
        }
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
            
            if ( ccpDistance(((CCNode*)enimy)->getPosition(), ((CCNode*)aemo)->getPosition() ) < (5 + 6)) {
                removeArray->addObject(enimy);
                removeArray->addObject(aemo);
                
                m_iScore ++;
                
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
    
    if (m_iOldScore != m_iScore) {
        char score[30];
        sprintf(score, "得分:%d", m_iScore);
        m_pScoreLabel->setString(score);
        m_iOldScore = m_iScore;
    }
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->getLocationInView();
    m_StartPoint = CCDirector::sharedDirector()->convertToGL(point);
    
//    m_pDragon->setPosition(point);
    
    //    m_pDragon->setPositionX(point.x);
}


void GameScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    CCPoint point;
    
    point = endPoint - m_StartPoint;
    
    CCPoint dragonPoint = m_pDragon->getPosition();
    float x = dragonPoint.x + point.x, y = dragonPoint.y + point.y;
    x = x<0?0:(x>m_winSize.width?m_winSize.width:x);
    y = y<0?0:(y>m_winSize.height?m_winSize.height:y);
    m_pDragon->setRotation(m_pDragon->getRotation() + point.x);
    m_pDragon->setPosition(x , y);
    
    
    m_StartPoint = endPoint;
    //    m_pDragon->setPositionX(point.x);
}


void GameScene::showButton(){
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::goBack));
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
}


void GameScene::goBack(CCObject* sender){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.9, SelectScene::scene()) );
}


void GameScene::reStart(CCObject* sender){
    
}
