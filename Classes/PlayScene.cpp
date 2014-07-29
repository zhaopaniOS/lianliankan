//
//  PlayScene.cpp
//  lianliankan
//
//  Created by joe on 14-6-8.
//
//

#include "PlayScene.h"

USING_NS_CC;

static int kCurrentLevelId = 1;

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // 背景图片
    auto sprite = Sprite::create("background.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // images
    auto node = Node::create();
    this->addChild(node, 0, kTagNode);
    
    // 进度条背景
    auto progressBg = Sprite::create("progressbg.png");
    progressBg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 60));
    this->addChild(progressBg, 1);
    
    // 当前第几关
    auto currentLevelNum = LabelTTF::create(StringUtils::format("Level:%d", kCurrentLevelId), "Marker Felt", 16);
    currentLevelNum->setPosition(Point(35, visibleSize.height - 75));
    this->addChild(currentLevelNum, 2);
    
    // 得分
    auto score = LabelTTF::create("Score:0", "Marker Felt", 16);
    score->setPosition(Point(visibleSize.width - 35, visibleSize.height - 75));
    this->addChild(score, 2, PlaySceneLayerTagScore);
    
    // 耗时
    auto timepast = LabelTTF::create("Time:0", "Marker Felt", 16);
    timepast->setPosition(Point(visibleSize.width/2, visibleSize.height - 75));
    this->addChild(timepast, 3, PlaySceneLayerTagTimePast);
    
    // 底部区域
    auto footerLayer = LayerColor::create(Color4B(0, 0, 0, 50), 640, 50);
    footerLayer->setPosition(Point::ZERO);
    this->addChild(footerLayer, 0);
    
    // back
    auto backMenuItem = MenuItemImage::create("back.png",
                                              "backselected.png",
                                              CC_CALLBACK_1(PlayScene::menuBackCallback, this));
    auto ctrlMenu = Menu::create(backMenuItem, NULL);
    ctrlMenu->setPosition(Point(30, 25));
    footerLayer->addChild(ctrlMenu, 200);
    
    // tools
    auto propRefreshItem = MenuItemImage::create("refresh.png",
                                                 "refreshselected.png",
                                                 "refreshdisabled.png",
                                                 CC_CALLBACK_1(PlayScene::menuPropRefreshCallback, this));
    auto refreshNumLabel = LabelTTF::create(StringUtils::format("%d", mRefreshNum), "Marker Felt", 13);
    propRefreshItem->addChild(refreshNumLabel, 1, PlaySceneLayerTagPropsRefresh);
    refreshNumLabel->setPosition(Point(-2, 7));
    
    auto propFinderItem = MenuItemImage::create("finder.png",
                                                "finderselected.png",
                                                "finderdisabled.png",
                                                CC_CALLBACK_1(PlayScene::menuPropFinderCallback, this));
    auto finderNumLabel = LabelTTF::create(StringUtils::format("%d", mFinderNum), "Marker Felt", 13);
    propFinderItem->addChild(finderNumLabel, 1, PlaySceneLayerTagPropsFinder);
    finderNumLabel->setPosition(Point(-2, 7));
    
    auto propBombItem = MenuItemImage::create("bomb.png",
                                              "bombselected.png",
                                              "bombdisabled.png",
                                              CC_CALLBACK_1(PlayScene::menuPropBombCallback, this));
    auto bombNumLabel = LabelTTF::create(StringUtils::format("%d", mBombNum), "Marker Felt", 13);
    propBombItem->addChild(bombNumLabel, 1, PlaySceneLayerTagPropsBomb);
    bombNumLabel->setPosition(Point(-2, 7));
    
    auto propsMenu = Menu::create(propRefreshItem, propFinderItem, propBombItem, NULL);
    propsMenu->alignItemsHorizontallyWithPadding(19.0f);
    propsMenu->setPosition(Point(visibleSize.width - 80, 25));
    footerLayer->addChild(propsMenu, 1);
    
    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("fruit.plist");
    
    this->showLLK();
    
    return true;
}

void PlayScene::goLevel(int level)
{
    kCurrentLevelId = level;
}

void PlayScene::menuBackCallback(cocos2d::Ref *pSender)
{
    
}

void PlayScene::menuPropRefreshCallback(cocos2d::Ref *pSender)
{
    
}

void PlayScene::menuPropFinderCallback(cocos2d::Ref *pSender)
{
    
}

void PlayScene::menuPropBombCallback(cocos2d::Ref *pSender)
{
    
}

void PlayScene::showLLK()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto parent = this->getChildByTag(kTagNode);
    auto frameCache = SpriteFrameCache::getInstance();
    
    mOpers = new CGDataOperate(kVerticalItemCount, kHorizontalItemCount, kMaxItems);
    int rows, cols = 0;
    int** arr = mOpers->GetArr(rows, cols);
    
    float width = kImageDimemsion * cols;
    float height = kImageDimemsion * rows;
    
    float leftSpace = (visibleSize.width - width) / 2;
    float bottomSpace = (visibleSize.height - height) / 2;
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int nItemType = arr[i][j];
            if (kEmpty == nItemType)
            {
                continue;
            }
            // rect
            float x = leftSpace + kImageDimemsion * j + origin.x;
            float y = bottomSpace + kImageDimemsion * i + origin.y;
            
            CGImageNode* sprite = CGImageNode::create(i, j, nItemType, frameCache);
            parent->addChild(sprite, 1, i * mOpers->GetCols() + j);
            sprite->setPosition(Point(x,y));
            mOpers->AddNode(sprite);
        }
    }
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(PlayScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(PlayScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(PlayScene::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(PlayScene::onTouchesCancelled, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void PlayScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}

void PlayScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}

void PlayScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (touches.empty()) return;
    
    Point pt = touches[touches.size()-1]->getLocation();
    
    auto sprite = mOpers->GetNodeByPoint(pt);
    if (sprite == nullptr) return;
    
    auto oldSprite = mOpers->GetCurrentNode();
    if (oldSprite == nullptr)
    {
        mOpers->SetCurrentNode(sprite);
        sprite->runAction(TintBy::create(0.1f, 0, 100, 100));
        return;
    }
    if (oldSprite == sprite) return;
    mOpers->SetCurrentNode(sprite);
    
    // Check if can eliminate
    if (mOpers->CheckErase(oldSprite, sprite))
    {
        // erase
        mOpers->RemoveNode(oldSprite);
        mOpers->RemoveNode(sprite);
        mOpers->SetCurrentNode(nullptr);
        
        oldSprite->removeFromParent();
        sprite->removeFromParent();
    }
    else
    {
        oldSprite->runAction(TintBy::create(0.1f, 0, -100, -100));
        sprite->runAction(TintBy::create(0.1f, 0, 100, 100));
    }
}

void PlayScene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}