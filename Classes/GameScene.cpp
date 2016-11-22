//
//  GameScene.cpp
//  TriaGame
//
//  Created by Valik on 11/5/16.
//
//

#include "GameScene.hpp"
#include "Triangle.hpp"
#include "HelloWorldScene.h"
#include "BuyUndosScene.hpp"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

int touchx;
int touchy;

int undos = cocos2d::UserDefault::getInstance()->getIntegerForKey("undos");

std::vector<filatov::Triangle*> trias;

USING_NS_CC;

bool byX(filatov::Triangle a, filatov::Triangle b) { return a.getX() > b.getX(); }
bool byY(filatov::Triangle a, filatov::Triangle b) { return a.getY() > b.getY(); }
bool byZ(filatov::Triangle a, filatov::Triangle b) { return a.getZ() > b.getZ(); }


bool isempty(std::vector<filatov::Triangle*> trs, int x, int y, int z){
    for(auto tr = trs.begin(); tr != trs.end(); tr++){
        if((*tr)->getX() == x && (*tr)->getY() == y && (*tr)->getZ() == z) return false;
    }
    return true;
}

int getRotationByXYZ(std::vector<filatov::Triangle*> trs, int x, int y, int z){
    if(x == 0 && y == 0 && z == 0) return -1;
    for(auto tr = trs.begin(); tr != trs.end(); tr++){
        if((*tr)->getX() == x && (*tr)->getY() == y && (*tr)->getZ() == z) return (*tr)->getRotation();
    }
    return -2;
}

int getTriaRotation(std::vector<filatov::Triangle*> trs, int xyz){
    for(auto tr = trs.begin(); tr != trs.end(); tr++){
        if((*tr)->getX() == xyz/100 && (*tr)->getY() == xyz/10-(xyz/100)*10 && (*tr)->getZ() == xyz - (xyz/100)*100 - (xyz/100)*10) return (*tr)->getRotation();
    }
    return true;
}

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto layer = LayerColor::create(Color4B(173, 228, 255, 255));
    Size size = Director::getInstance()->getWinSize();
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadEffect("fins__button.wav");
    
    
    auto draw = DrawNode::create();
    draw->drawTriangle(Vec2(size.width/2, 374), Vec2(size.width/2+120, 164), Vec2(size.width/2-120,164), Color4F::WHITE);
    this->addChild(draw, 1);
    
    auto grid = DrawNode::create();
    grid->drawSegment(Vec2(size.width/2-60, 164), Vec2(size.width/2+30, 322), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2, 164), Vec2(size.width/2+60, 269), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2+60, 164), Vec2(size.width/2+90, 217), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2-60, 164), Vec2(size.width/2-90, 217), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2, 164), Vec2(size.width/2-60, 269), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2+60, 164), Vec2(size.width/2-30, 322), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2-30, 322), Vec2(size.width/2+30, 322), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2-60, 269), Vec2(size.width/2+60, 269), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    grid->drawSegment(Vec2(size.width/2-90, 217), Vec2(size.width/2+90, 217), 1.2f,
                      Color4F(Color4B(173, 228, 255, 255)));
    this->addChild(grid, 1);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    trias.push_back(new filatov::Triangle(1, 0, 3, 0, 0));
    trias.push_back(new filatov::Triangle(10, 0, 3, 3, 3));
    
    trias.push_back(new filatov::Triangle(100, 0, 3, 1, 1));
    trias.push_back(new filatov::Triangle(100000, 0, 2, 1, 0));
    
    for(int i = 0; i < trias.size(); i++){
        this->addChild(trias.at(i)->sprite,1);
    }
    
    
    
    
    auto menuButton = ui::Button::create("tomenu.png");

    menuButton->setAnchorPoint(Point(0, 1));
    menuButton->::Game::setPosition(35,size.height-10);
    menuButton->setScale(0.5);
    menuButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        auto mainscene = HelloWorld::createScene();
        
        auto tr = TransitionFade::create(0.5, mainscene);
        Director::getInstance()->replaceScene(tr);
    });
    
    this->addChild(menuButton, 1);
    
    TTFConfig config;
    config.fontFilePath = "fonts/blow.ttf";
    config.fontSize = 24.0f;
    
    std::string undosStr = StringUtils::format("Undos: %d", undos);
    Label *undosNumLbl = Label::createWithTTF(config, undosStr);
    undosNumLbl->setTextColor(cocos2d::Color4B(14, 109, 223, 255));
    undosNumLbl->setPosition(size.width/2, size.height-22);
    this->addChild(undosNumLbl, 1);
    
    auto undoButton = ui::Button::create("undo.png");
    undoButton->setAnchorPoint(Point(1, 1));
    undoButton->::Game::setPosition(size.width-35, size.height-10);
    undoButton->setScale(0.5);
    undoButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
        if(type == ui::Widget::TouchEventType::BEGAN){
            if(undos > 0){
                undos--;
                undosNumLbl->setString(StringUtils::format("Undos: %d", undos));
                
                UserDefault::getInstance()->setIntegerForKey("undos", undos);
                UserDefault::getInstance()->flush();
            }
            else{
                auto buyScene = BuyUndos::createScene();
                
                auto tr = TransitionFade::create(0.5, buyScene);
                Director::getInstance()->replaceScene(tr);
            }
        }
    });

    this->addChild(undoButton,1);
    
    
    
    
    
    Label *scoreLbl = Label::createWithTTF(config, "Score:\n\n 100");
    scoreLbl->setHorizontalAlignment(TextHAlignment::CENTER);
    scoreLbl->setTextColor(cocos2d::Color4B(14, 109, 223, 255));
    scoreLbl->setPosition(90, 50);
    this->addChild(scoreLbl, 1);
    
    Label *bestLbl = Label::createWithTTF(config, "Best:\n\n 228");
    bestLbl->setHorizontalAlignment(TextHAlignment::CENTER);
    bestLbl->setTextColor(cocos2d::Color4B(14, 109, 223, 255));
    bestLbl->setPosition(size.width - 90, 50);
    this->addChild(bestLbl, 1);
    
    
    int*  oldx = new int[10];
    int*  oldy = new int[10];

    
    auto listener1 = EventListenerTouchOneByOne::create();
    // trigger when you push down
    
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
        touchx = touch->getLocation().x;
        touchy = touch->getLocation().y;
        
        
        for(int i = 0; i < trias.size(); i++){
            *(oldx+i) = trias.at(i)->getScreenPosition().x;
            *(oldy+i) = trias.at(i)->getScreenPosition().y;
        }
        
        
        return true; // if you are consuming it
    };
    
    
    
    // trigger when moving touch
    listener1->onTouchMoved = [this](Touch* touch, Event* event){
        
    };
    
    // trigger when you let up
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        int deltax = touch->getLocation().x - touchx;
        int deltay = touch->getLocation().y - touchy;
        if(deltay == 0) deltay = 1;
        
        //trias.push_back(new filatov::Triangle(1, 0, 3, 0, 0));
        trias.push_back(new filatov::Triangle(99, 0, 3, 2, 2));
        this->addChild(trias.at(trias.size()-1)->sprite, 1);
        
        int dx[10] = {0,0,0,0,0,0,0,0,0,0};
        int dy[10] = {0,0,0,0,0,0,0,0,0,0};
        int dz[10] = {0,0,0,0,0,0,0,0,0,0};
        
        
        
        
        
        for(int act = 0; act < 10; act++){

        
        float tan = (float)deltax / (float)deltay;
        
        if(deltax > 0 && tan < 1.7320 && tan > 0) {
            for(int i = 0; i < trias.size(); i++){
                if(isempty(trias, trias.at(i)->getX()+1, trias.at(i)->getY(), trias.at(i)->getZ())
                   && isempty(trias, trias.at(i)->getX(), trias.at(i)->getY()-1, trias.at(i)->getZ()))
                {trias.at(i)->movePlusX();
                    dx[i]++;
                    
                }
            }
            CCLOG("dx+");
        }
        if(deltax > 0 && ((tan > 1.7320 && tan >0) || (tan < -1.7320 && tan < 0))) {
            
            for(int i = 0; i < trias.size(); i++){
                if(isempty(trias, trias.at(i)->getX()+1, trias.at(i)->getY(), trias.at(i)->getZ())
                   && isempty(trias, trias.at(i)->getX(), trias.at(i)->getY(), trias.at(i)->getZ()+1)){
                    trias.at(i)->movePlusZ();
                    dz[i]++;
                                   }
            }
            CCLOG("dz+");}
        if(deltax > 0 && tan > -1.7320 && tan < 0){
            for(int i = 0; i < trias.size(); i++){
                if(isempty(trias, trias.at(i)->getX(), trias.at(i)->getY()+1, trias.at(i)->getZ())
                   && isempty(trias, trias.at(i)->getX(), trias.at(i)->getY(), trias.at(i)->getZ()+1)){
                    trias.at(i)->movePlusY();
                    dy[i]++;
                   
                }
            }

            CCLOG("dy+");
        }
        
        if(deltax < 0 && tan < 1.7320 && tan > 0) {
            for(int i = 0; i < trias.size(); i++){
                if(isempty(trias, trias.at(i)->getX()-1, trias.at(i)->getY(), trias.at(i)->getZ())
                   && isempty(trias, trias.at(i)->getX(), trias.at(i)->getY()+1, trias.at(i)->getZ())){
                    trias.at(i)->moveMinusX();
                    dx[i]--;
                    
                }
            }
            CCLOG("dx-");}
        if(deltax < 0 && ((tan > 1.7320 && tan >0) || (tan < -1.7320 && tan < 0))){
            for(int i = 0; i < trias.size(); i++){
                if(isempty(trias, trias.at(i)->getX()-1, trias.at(i)->getY(), trias.at(i)->getZ())
                   && isempty(trias, trias.at(i)->getX(), trias.at(i)->getY(), trias.at(i)->getZ()-1)){
                    trias.at(i)->moveMinusZ();
                    dz[i]--;
                    
                }
            }

            CCLOG("dz-");
        }
        if(deltax < 0 && tan > -1.7320 && tan < 0){
            for(int i = 0; i < trias.size(); i++){
                if(isempty(trias, trias.at(i)->getX(), trias.at(i)->getY()-1, trias.at(i)->getZ())
                   && isempty(trias, trias.at(i)->getX(), trias.at(i)->getY(), trias.at(i)->getZ()-1)){
                    trias.at(i)->moveMinusY();
                    dy[i]--;
                    
                }
            }

            CCLOG("dy-");}
        
        
    };
        for(int i = 0; i < trias.size(); i++){
            
            
               // if(abs(getTriaRotation(trias, *it) - trias.at(i)->getRotation())%3 == 0  && abs(getTriaRotation(trias, *it) - trias.at(i)->getRotation())%6 != 0){audio->playEffect("fins__button.wav");
                   // exit(1);
                //}
                //xyz/100 && (*tr)->getY() == xyz/10-(xyz/100)*10 && (*tr)->getZ() == xyz - (xyz/100)*100 - (xyz/100)*10)
            
            
            auto rotate = RotateBy::create(0.5, 60);
            if(abs(trias.at(i)->dx + trias.at(i)->dy + trias.at(i)->dz)%2 == 1){
                trias.at(i)->sprite->runAction(rotate);
                trias.at(i)->rotateCW();
            }
            auto move = MoveTo::create(((abs(trias.at(i)->dx)+abs(trias.at(i)->dy)+abs(trias.at(i)->dz))*0.1), Vec2(trias.at(i)->getScreenPosition().x+size.width/2, trias.at(i)->getScreenPosition().y));
            trias.at(i)->sprite->runAction(move);
            trias.at(i)->nullds();
        }
        for(int i = 0; i < trias.size(); i++){
            std::vector<int> nei = trias.at(i)->getNeighbours();

            std::vector<int>::iterator it = nei.begin();
            int neib = *(it+(trias.at(i)->getRotation())%6);
            int zcoor = neib%10;
            int neibRot = getRotationByXYZ(trias, neib/100, neib/10-(neib/100)*10, zcoor);
            if(neibRot > 0 && (abs(neibRot - trias.at(i)->getRotation()))%3 == 0 && (abs(neibRot - trias.at(i)->getRotation()))%6 != 0) audio->playEffect("fins__button.wav");;
            
            
        }
        
    };
    
    
    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    
    
    this->addChild(layer);
    return true;
}


void Game::menuCloseCallback(Ref* pSender)
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
