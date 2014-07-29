#include "GameMenu.h"
#include "LevelScene.h"

USING_NS_CC;

Scene* GameMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameMenu::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    

    // 背景图片
    auto sprite = Sprite::create("background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, -1);
    
    // 菜单标题
    auto label = LabelTTF::create("菜单", "Marker Felt", 32);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height - 80));
    
    // add the label as a child to this layer
    this->addChild(label, 0);
    
    // 菜单
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(25);
    auto levelMenu = MenuItemFont::create("进入游戏",
                                          CC_CALLBACK_1(GameMenu::menuEnterGameCallback, this));
    auto settingMenu = MenuItemFont::create("游戏设置",
                                          CC_CALLBACK_1(GameMenu::menuSettingCallback, this));
    auto purchaseMenu = MenuItemFont::create("购买新关卡",
                                             CC_CALLBACK_1(GameMenu::menuPurchaseCallback, this));
    auto helpMenu = MenuItemFont::create("帮助",
                                             CC_CALLBACK_1(GameMenu::menuHelpCallback, this));
    auto menuGame = Menu::create(levelMenu, settingMenu, purchaseMenu, helpMenu, NULL);
    menuGame->alignItemsVerticallyWithPadding(30);
    this->addChild(menuGame, 1);
    
    return true;
}

void GameMenu::menuEnterGameCallback(cocos2d::Ref *pSender)
{
    auto sc = LevelScene::createScene();
    
    auto director = Director::getInstance();
    
    director->replaceScene(sc);
}

void GameMenu::menuSettingCallback(cocos2d::Ref *pSender)
{
    
}

void GameMenu::menuPurchaseCallback(cocos2d::Ref *pSender)
{
    
}

void GameMenu::menuHelpCallback(cocos2d::Ref *pSender)
{
    
}

void GameMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
