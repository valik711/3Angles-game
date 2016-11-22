//
//  Triangle.cpp
//  TriaGame
//
//  Created by Valik on 11/6/16.
//
//

#include "Triangle.hpp"
#include <math.h>


filatov::Triangle::Triangle(int pts, int rot, int x, int y, int z){
    this->points = pts;
    this->rotation = rot;
    this->x = x;
    this->y = y;
    this->z = z;
    sw = true;
    cocos2d::Size size = cocos2d::Director::getInstance()->getWinSize();
    
    dx = 0;
    dy = 0;
    dz = 0;
    
    
    this->sprite = cocos2d::Sprite::create("triangle.png");
    sprite->setPosition(this->getScreenPosition().x+size.width/2, this->getScreenPosition().y);
    sprite->setScale(0.8);
    sprite->setAnchorPoint(cocos2d::Point(0.5, 0.3333));
    
    auto pointslbl = cocos2d::Label::create();
    pointslbl->setSystemFontSize(20 - 3*log10(this->points)/2);
    //this->points;
    pointslbl->setString(cocos2d::StringUtils::toString(this->points));
    pointslbl->setPosition((sprite->getBoundingBox().getMaxX()-sprite->getBoundingBox().getMidX())/0.8, (sprite->getBoundingBox().getMaxY()-sprite->getBoundingBox().getMidY()-3)/0.8-6);
    sprite->addChild(pointslbl);
    
    
    
    
}


void filatov::Triangle::movePlusX(){
    if(std::find(cells.begin(), cells.end(), 100*(x+1)+10*y+z) != cells.end()) {
        x++;
        dx++;
    } else if((std::find(cells.begin(), cells.end(), 100*x+10*(y-1)+z) != cells.end())) {
        y--;
        dx++;
    }
}

void filatov::Triangle::moveMinusX(){
    if(std::find(cells.begin(), cells.end(), 100*(x-1)+10*y+z) != cells.end()) {
        x--;
        dx--;
    } else if(std::find(cells.begin(), cells.end(), 100*x+10*(y+1)+z) != cells.end()) {
        y++;
        dx--;
    }
}

void filatov::Triangle::movePlusY(){
    if(std::find(cells.begin(), cells.end(), 100*x+10*(y+1)+z) != cells.end()) {
        y++;
        dy++;
    } else if(std::find(cells.begin(), cells.end(), 100*x+10*y+z+1) != cells.end()) {
        z++;
        dy++;
    }
}

void filatov::Triangle::moveMinusY(){
    if(std::find(cells.begin(), cells.end(), 100*x+10*(y-1)+z) != cells.end()) {
        y--;
        dy--;
    } else if(std::find(cells.begin(), cells.end(), 100*x+10*y+z-1) != cells.end()){
        z--;
        dy--;
    }
}

void filatov::Triangle::movePlusZ(){
    if(std::find(cells.begin(), cells.end(), 100*(x+1)+10*y+z) != cells.end()) {
        x++;
        dz++;
    } else if(std::find(cells.begin(), cells.end(), 100*x+10*y+z+1) != cells.end()){
        z++;
        dz++;
    }
}

void filatov::Triangle::moveMinusZ(){
    if(std::find(cells.begin(), cells.end(), 100*(x-1)+10*y+z) != cells.end()) {
        x--;
        dz--;
    } else if(std::find(cells.begin(), cells.end(), 100*x+10*y+z-1) != cells.end()){
        z--;
        dz--;
    }
}

int filatov::Triangle::getX(){
    return this->x;
}
int filatov::Triangle::getY(){
    return this->y;
}
int filatov::Triangle::getZ(){
    return this->z;
}

void filatov::Triangle::nullds(){
    dx=0;
    dy=0;
    dz=0;}

void filatov::Triangle::rotateCW(){
    rotation++;
    if(rotation%3 == 0) this->sprite->setPosition(this->sprite->getPosition().x, this->sprite->getPosition().y+5);
}

std::vector<int> filatov::Triangle::getNeighbours(){
    switch(100*x+10*y+z){
        case 300: return {310, 000, 000, 000, 000, 000};
        case 310: return {000, 210, 000, 300, 000, 311};
        case 210: return {220, 000, 000, 000, 310, 000};
        case 311: return {321, 000, 310, 000, 000, 000};
            
        case 120: return {130, 000, 000, 000, 220, 000};
        case 220: return {000, 120, 000, 210, 000, 221};
        case 221: return {231, 000, 220, 000, 321, 000};
        case 321: return {000, 221, 000, 311, 000, 322};
        case 322: return {332, 000, 321, 000, 000, 000};
            
        case 30: return {000, 000, 000, 000, 130, 000};
        case 130: return {000, 30, 000, 120, 000, 131};
        case 131: return {000, 000, 130, 000, 231, 000};
        case 231: return {000, 131, 000, 221, 000, 232};
        case 232: return {000, 000, 231, 000, 332, 000};
        case 332: return {000, 232, 000, 322, 000, 333};
        case 333: return {000, 000, 332, 000, 000, 000};
            
    }

}

int filatov::Triangle::getRotation(){
    return rotation;
}
