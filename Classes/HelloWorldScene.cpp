#include "HelloWorldScene.h"
#include "GameScene.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto layer = LayerColor::create(Color4B(173, 228, 255, 255));
    
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    TTFConfig config;
    config.fontFilePath = "fonts/blow.ttf";
    config.fontSize = 18.0f;
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("magntron__gamemusic.mp3");
    // play the background music and continuously play it.
    audio->playBackgroundMusic("magntron__gamemusic.mp3", true);
    
    Vector<Label*> menuLbls;
    //тексты для кнопок
    menuLbls.pushBack(Label::createWithTTF(config, "New game"));
    menuLbls.pushBack(Label::createWithTTF(config, "Rules"));
    menuLbls.pushBack(Label::createWithTTF(config, "Sound: on"));
    menuLbls.pushBack(Label::createWithTTF(config, "Rate"));
    
    float scale = 1.5;
    
    
    Vector<MenuItem*> menuItems;
    for (int i=1; i<=4; i++) {
        std::string name = StringUtils::format("item%d.png", i);
        std::string namePressed = StringUtils::format("item%dp.png", i);
        auto normalItem = Sprite::create(name);
        auto selectedItem = Sprite::create(namePressed);
        auto item = MenuItemSprite::create(normalItem, selectedItem,
                                           [=](Ref* sender){
                                               auto node = dynamic_cast<Node*>(sender);
                                               if (node!=nullptr) {
                                                   CCLOG("tapped item %d", node->getTag());
                                               }
                                               if(node->getTag() == 1) {
                                                   auto scene = Game::createScene();
                                                   
                                                   auto tr = TransitionFade::create(0.5, scene);
                                                   Director::getInstance()->replaceScene(tr);
                                               }
                                               
                                               if(node->getTag() == 3) {
                                                   
                                                   if(audio->getBackgroundMusicVolume() > 0.1){
                                                       audio->setBackgroundMusicVolume(0);
                                                       menuLbls.at(2)->setString("Sound: off");
                                                   }
                                                   else {
                                                       audio->setBackgroundMusicVolume(1);
                                                       menuLbls.at(2)->setString("Sound: on");
                                                   }
                                               }

                                           });
        item->setTag(i);
        item->setScale(scale);
        auto box = item->getBoundingBox();
        
        menuLbls.at(i-1)->setPosition((box.getMidX()-box.getMinX())/scale, (box.getMidY()-box.getMinY()+7)/scale);
        item->addChild(menuLbls.at(i-1));
        menuItems.pushBack(item);
    }
    auto size = Director::getInstance()->getWinSize();
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(size.width/2, 80 + 2*(menuItems.at(0)->getBoundingBox().getMaxY()));
    menu->alignItemsVerticallyWithPadding(5);
    this->addChild(menu, 1);

        // подключение шрифта к главному заголовку в приложении
    auto label = Label::createWithTTF("3Angles", "fonts/JeanSunHo.ttf", 120);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 120));

    // add the label as a child to this layer
    this->addChild(label, 1);

    this->addChild(layer);
    return true;
}

// колбк для выхода
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
}

