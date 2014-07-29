//
//  PlayScene.h
//  lianliankan
//
//  Created by joe on 14-6-8.
//
//

#ifndef __lianliankan__PlayScene__
#define __lianliankan__PlayScene__

#include "cocos2d.h"
#include "DataOperate.h"

// tags
typedef enum
{
    PlaySceneLayerTagScore = 3,
    PlaySceneLayerTagTimePast = 4,
    PlaySceneLayerTagPropsRefresh = 5,
    PlaySceneLayerTagPropsFinder = 6,
    PlaySceneLayerTagPropsBomb = 7,
} PlaySceneLayerTags;

#define kVerticalItemCount 9
#define kHorizontalItemCount 8
#define kMaxItems 32
#define kTagNode 2
#define kPaddingBottom 125.0f
#define kPaddingLeft 1.0f
#define kImageDimemsion 32

class PlayScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
    
    static void goLevel(int level);
    void menuBackCallback(cocos2d::Ref* pSender);
    void menuPropRefreshCallback(cocos2d::Ref* pSender);
    void menuPropFinderCallback(cocos2d::Ref* pSender);
    void menuPropBombCallback(cocos2d::Ref* pSender);
    void showLLK();
public:
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
public:
    uint32_t mRefreshNum;
    uint32_t mFinderNum;
    uint32_t mBombNum;
    CGDataOperate* mOpers;
};

#endif /* defined(__lianliankan__PlayScene__) */
