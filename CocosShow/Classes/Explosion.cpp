//
//  Explosion.cpp
//  CocosShow
//
//  Created by 170warship on 8/9/13.
//
//

#include "Explosion.h"
#include "CCBAnimationManager.h"
CCNODEOBJECT_LOAD_BODY(Explosion, ExplosionLoader, ExplosionInit, "Explosion");

void Explosion::completedAnimationSequenceNamed(const char *name){
    if(this->getParent()){
        this->removeFromParent();
    }
}


void Explosion::onEnter(){
    Explosionc::onEnter();
    ( (CCBAnimationManager*)(this->getUserObject()) )->setDelegate(this);
}

