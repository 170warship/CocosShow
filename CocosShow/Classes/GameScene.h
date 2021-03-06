//
//  GameScene.h
//  CocosShow
//
//  Created by 170warship on 8/8/13.
//
//

#ifndef __CocosShow__GameScene__
#define __CocosShow__GameScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Dragon.h"
USING_NS_CC_EXT;
USING_NS_CC;


class GameScene:public CCLayer{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    CCLabelTTF* m_pScoreLabel;
    
    virtual bool init();
    
    GameScene();
    ~GameScene();
    //
    //    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    virtual void onEnter();
    virtual void update(float delta);
    
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private:
    void fire();
    void addEnimy();
    void showButton();
    void goBack(CCObject* sender);
    void reStart(CCObject* sender);
    Dragon* m_pDragon;
    
    CCPoint m_StartPoint;
    CCArray* m_pAemoArray;
    CCArray* m_pEnimyArray;
    CCSize m_winSize;
    int m_iOldFrame;
    int m_iOldFireFrame;
    int m_iFrame;
    int m_iScore;
    int m_iOldScore;
    int m_iEnimySpeed;
    bool m_bIsEnd;
};

#endif /* defined(__CocosShow__GameScene__) */
