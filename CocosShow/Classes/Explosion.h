//
//  Explosion.h
//  CocosShow
//
//  Created by 170warship on 8/9/13.
//
//

#ifndef __CocosShow__Explosion__
#define __CocosShow__Explosion__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "NodeCommon.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "NodeCommon.h"

CCNODEOBJECT_LOAD_HEAD(Explosionc, ExplosionLoader);

class Explosion:public Explosionc, public CCBAnimationManagerDelegate{
public:
    virtual bool init(){
        if ( !Explosionc::init() )
        {
            return false;
        }
        return true;
    }
    
    Explosion(){
        
    }
    
    static cocos2d::CCNode* node();
    virtual void completedAnimationSequenceNamed(const char *name);
    virtual void onEnter();
    CREATE_FUNC(Explosion);
};


CCNODEOBJECT_LOADER_HEAD(Explosion, ExplosionLoader);

#endif /* defined(__CocosShow__Explosion__) */
