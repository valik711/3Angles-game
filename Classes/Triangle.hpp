//
//  Triangle.hpp
//  TriaGame
//
//  Created by Valik on 11/6/16.
//
//

#ifndef Triangle_hpp
#define Triangle_hpp

#define ROTATION_BOTTOM 0
#define ROTATION_LEFT 1
#define ROTATION_RIGHT 2

#include <stdio.h>

#endif /* Triangle_hpp */

namespace filatov {
    
    
class Triangle{
private:
    std::vector<int> cells = {30, 130, 120, 220, 210, 310, 300, 131, 231, 221, 321, 311, 232, 332, 322, 333};

    int points;
    int rotation;
    int x;
    int y;
    int z;
    bool sw;
    
public:
    cocos2d::Sprite* sprite;
    cocos2d::Vec2 getScreenPosition(){
        int deltaHeight = 0;
        if(rotation%6 == 0) deltaHeight = -8;
        if(rotation%6 == 1) deltaHeight = +10;
        if(rotation%6 == 2) deltaHeight = -8;
        if(rotation%6 == 3) deltaHeight = +10;
        if(rotation%6 == 4) deltaHeight = -8;
        if(rotation%6 == 5) deltaHeight = +10;
        switch(100*x+10*y+z){
            case 300: return cocos2d::Vec2(0, 348+deltaHeight);
            case 310: return cocos2d::Vec2(0, 295+deltaHeight);
            case 210: return cocos2d::Vec2(-30.5, 295+deltaHeight);
            case 311: return cocos2d::Vec2(30.5, 295+deltaHeight);
                
            case 120: return cocos2d::Vec2(-60.5, 242+deltaHeight);
            case 220: return cocos2d::Vec2(-30.5, 242+deltaHeight);
            case 221: return cocos2d::Vec2(0, 242+deltaHeight);
            case 321: return cocos2d::Vec2(30.5, 242+deltaHeight);
            case 322: return cocos2d::Vec2(60.5, 242+deltaHeight);
                
            case 30: return cocos2d::Vec2(-90.5, 189+deltaHeight);
            case 130: return cocos2d::Vec2(-60.5, 189+deltaHeight);
            case 131: return cocos2d::Vec2(-30.5, 189+deltaHeight);
            case 231: return cocos2d::Vec2(0, 189+deltaHeight);
            case 232: return cocos2d::Vec2(30.5, 189+deltaHeight);
            case 332: return cocos2d::Vec2(60.5, 189+deltaHeight);
            case 333: return cocos2d::Vec2(90.5, 189+deltaHeight);
                
        }
    }
    
    cocos2d::Vec2 xyzToScreenPos(int x, int y, int z){
        switch(100*x+10*y+z){
            case 300: return cocos2d::Vec2(0, 222);
            case 310: return cocos2d::Vec2(0, 187);
            case 210: return cocos2d::Vec2(-20, 187);
            case 311: return cocos2d::Vec2(20, 187);
                
            case 120: return cocos2d::Vec2(-40, 152);
            case 220: return cocos2d::Vec2(-20, 152);
            case 221: return cocos2d::Vec2(0, 152);
            case 321: return cocos2d::Vec2(20, 152);
            case 322: return cocos2d::Vec2(40, 152);
                
            case 30: return cocos2d::Vec2(-60, 117);
            case 130: return cocos2d::Vec2(-40, 117);
            case 131: return cocos2d::Vec2(-20, 117);
            case 231: return cocos2d::Vec2(0, 117);
            case 232: return cocos2d::Vec2(20, 117);
            case 332: return cocos2d::Vec2(40, 117);
            case 333: return cocos2d::Vec2(60, 117);
                
        }
    }

    
    Triangle(int pts, int rot, int x, int y, int z);
    
    void movePlusX();
    void movePlusY();
    void movePlusZ();
    void moveMinusX();
    void moveMinusY();
    void moveMinusZ();
    
    int getX();
    int getY();
    int getZ();
    
    int getRotation();
    
    int dx;
    int dy;
    int dz;
    
    void rotateCW();
    
    void nullds();
    
    std::vector<int> getNeighbours();
    
    
};
}
