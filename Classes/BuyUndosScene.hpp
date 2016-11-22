//
//  BuyUndosScene.hpp
//  TriaGame
//
//  Created by Valik on 11/7/16.
//
//

#ifndef BuyUndosScene_hpp
#define BuyUndosScene_hpp

#include <stdio.h>


class BuyUndos : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BuyUndos);
};

#endif
