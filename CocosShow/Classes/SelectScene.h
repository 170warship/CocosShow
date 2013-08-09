

//
//  SelectScene.h
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//

#ifndef __CocosShow__SelectScene__
#define __CocosShow__SelectScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Dragon.h"
USING_NS_CC_EXT;
USING_NS_CC;



class SelectScene : public CCLayer,

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
    
    SelectScene(){
        
    }
    
    ~SelectScene(){
        
    }
    
    //    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectScene,create);
    
    
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget,const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){};
    
    void sceneTimeLine(CCObject* sender);
    void sceneAction(CCObject* sender);
    void sceneTransition(CCObject* sender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(SelectScene);
};

class SelectSceneLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectScene);
};


#endif /* defined(__CocosShow__SelectScene__) */
