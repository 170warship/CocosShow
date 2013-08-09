//
//  Dragon.h
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//

#ifndef __CocosShow__Dragon__
#define __CocosShow__Dragon__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Dragon.h"
USING_NS_CC_EXT;
USING_NS_CC;



class Dragon : public CCNode,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCNodeLoaderListener
{
public:
    static cocos2d::CCNode* node();
    
    
    virtual bool init(){
        if ( !CCNode::init() )
        {
            return false;
        }
        return true;
    }
    
    Dragon(){
        
    }
    
    ~Dragon(){
        
    }
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName){
    
        return NULL;
    }
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName){
        return NULL;
    }
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode){     
        return false;
    }
//    virtual void onEnter(){ }
   // virtual void update(float delta){}
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){}
    
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){}
    
    CREATE_FUNC(Dragon);
};

class DragonLoader : public cocos2d::extension::CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DragonLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Dragon);
};


#endif /* defined(__CocosShow__Dragon__) */
