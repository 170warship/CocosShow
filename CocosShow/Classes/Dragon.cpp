//
//  Dragon.cpp
//  CocosShow
//
//  Created by 170warship on 8/7/13.
//
//

#include "Dragon.h"

class DragonInit{
public:
    DragonInit(){
        CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader("Dragon", DragonLoader::loader());
    }
};
static DragonInit dragonInitInstance;

CCNode* Dragon::node(){
    CCNodeLoaderLibrary * ccbLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccbLib->registerCCNodeLoader("Dragon", DragonLoader::loader());
    CCBReader *ccbReader = new CCBReader(ccbLib);
    CCNode* node = ccbReader->readNodeGraphFromFile("Dragon.ccbi");
    
    ccbReader->release();
    return node;
}