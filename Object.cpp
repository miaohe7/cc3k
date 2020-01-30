//
//  Object.cpp
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-26.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#include "Object.h"


Coordinates Object::getCoord(){
    return position;
}

void Object::setCoord(Coordinates pos){
    position = pos;
}

char Object::getType(){
    return type;
}



Object::~Object() {};
