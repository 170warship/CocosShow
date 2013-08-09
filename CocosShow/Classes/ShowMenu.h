//
//  ShowMenu.h
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//

#ifndef __CocosShow__ShowMenu__
#define __CocosShow__ShowMenu__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Dragon.h"
USING_NS_CC_EXT;
USING_NS_CC;



class ShowMenu : public CCLayer,

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
    
    ShowMenu(){
        
    }
    
    ~ShowMenu(){
        
    }
    
    //    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ShowMenu,create);
    
    
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget,const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){};
    
    
	
    void playTimeLine1(CCObject* sender);
    void playTimeLine2(CCObject* sender);
    void playTimeLine3(CCObject* sender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ShowMenu);
private:
    Dragon* m_pDragon;
};

class ShowMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ShowMenuLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ShowMenu);
};
#endif /* defined(__CocosShow__ShowMenu__) */
