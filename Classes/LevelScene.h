//
//  LevelScene.h
//  lianliankan
//
//  Created by joe on 14-6-8.
//
//

#ifndef __lianliankan__LevelScene__
#define __lianliankan__LevelScene__

#include "cocos2d.h"

#define kRowDisplayLevelNum 6

class LevelScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuLevelNumCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelScene);
};

#endif /* defined(__lianliankan__LevelScene__) */
