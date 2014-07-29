//
//  LevelScene.cpp
//  lianliankan
//
//  Created by joe on 14-6-8.
//
//

#include "LevelScene.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* LevelScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelScene::init()
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
    this->addChild(sprite, -1);
    
    // 菜单标题
    auto label = LabelTTF::create("连连看", "Marker Felt", 32);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height - 60));
    
    // add the label as a child to this layer
    this->addChild(label, 0);
    
    // 关卡总数
    auto levelTotal = 30;
    // 已通关数
    auto levelUnlockNum = 1;
    // 缓存图片
    auto levelLockedBatch = SpriteBatchNode::create("levellocked.png");
    this->addChild(levelLockedBatch);
    // 行
    int row = 1;
    int col = 1;
    auto menu = Menu::create();
    for (int i = 0; i < levelTotal; ++i) {
        if ((i % kRowDisplayLevelNum) == 0)
        {
            col = 1;
            row++;
        }
        // offset
        float offsetPraction = ((float)col) / (kRowDisplayLevelNum + 1);
        float positionX = visibleSize.width * offsetPraction;
        float positionY = visibleSize.height - 66 * row;
        
        if (i < levelUnlockNum) {
            auto menuItem = MenuItemSprite::create(Sprite::create("level.png"),
                                                   Sprite::create("levelselected.png"),
                                                   CC_CALLBACK_1(LevelScene::menuLevelNumCallback, this));
            menuItem->setPosition(Point(positionX,positionY));
            menuItem->setTag(i);
            menu->addChild(menuItem);
            
            
            auto levelNumber = LabelTTF::create(StringUtils::format("%i", i+1), "Marker Flet", 14);
            levelNumber->setPosition(Point(16, 16));
            levelNumber->setColor(Color3B(116, 170, 45));
            menuItem->addChild(levelNumber);
        } else {
            auto levelLockedSprite = Sprite::create("levellocked.png");
            levelLockedSprite->setPosition(Point(positionX, positionY));
            levelLockedBatch->addChild(levelLockedSprite);
        }
        col++;
    }
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
}

void LevelScene::menuLevelNumCallback(cocos2d::Ref *pSender)
{
    auto levelUnlock = (MenuItemSprite*)pSender;
    int level = levelUnlock->getTag() + 1;
    log("level: %d", level);
    
    PlayScene::goLevel(level);
    
    auto sc = PlayScene::createScene();
    
    auto director = Director::getInstance();
    
    director->replaceScene(sc);
}
