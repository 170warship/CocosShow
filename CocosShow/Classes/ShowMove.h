//
//  ShowMove.h
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//

#ifndef __CocosShow__ShowMove__
#define __CocosShow__ShowMove__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Dragon.h"
USING_NS_CC_EXT;
USING_NS_CC;



class ShowMove : public CCLayer,

public CCBMemberVariableAssigner,

public CCBSelectorResolver,

public CCNodeLoaderListener
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    
    virtual bool init();
    //
    //    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    virtual void onEnter();
    
    ShowMove(){
        m_bMoved = false;
        m_bTouchIn = false;
    }
    
    ~ShowMove(){
        
    }
    
    //    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ShowMove,create);
    
    
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget,const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){};
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ShowMove);
private:
    bool m_bMoved;
    bool m_bTouchIn;
    CCPoint m_startpPoint;
    Dragon* m_pDragon;
};

class ShowMoveLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ShowMoveLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ShowMove);
};
#endif /* defined(__CocosShow__ShowMenu__) */
