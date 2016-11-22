//
//  GameScene.hpp
//  TriaGame
//
//  Created by Valik on 11/5/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"




class Game : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
    
};

#endif // __HELLOWORLD_SCENE_H__
