//
//  BuyUndosScene.cpp
//  TriaGame
//
//  Created by Valik on 11/7/16.
//
//

#include "BuyUndosScene.hpp"

#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BuyUndos::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BuyUndos::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BuyUndos::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto layer = LayerColor::create(Color4B(173, 228, 255, 255));
    
    

    
    auto label = Label::createWithTTF("Donat", "fonts/JeanSunHo.ttf", 100);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(200, 200));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    this->addChild(layer);
    return true;
}


void BuyUndos::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

