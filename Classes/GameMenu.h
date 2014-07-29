#ifndef __GAMEMENU_SCENE_H__
#define __GAMEMENU_SCENE_H__

#include "cocos2d.h"

class GameMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // menu item callback
    void menuEnterGameCallback(cocos2d::Ref* pSender);
    void menuSettingCallback(cocos2d::Ref* pSender);
    void menuPurchaseCallback(cocos2d::Ref* pSender);
    void menuHelpCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMenu);
};

#endif // __GAMEMENU_SCENE_H__
