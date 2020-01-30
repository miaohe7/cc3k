//
//  Stairs.cpp
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-26.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#include "Stairs.h"


Stairs::Stairs() {
    type = '\\';
}


VerticalWall::VerticalWall() {
    type = '|';
}


HorizontalWall::HorizontalWall() {
    type = '-';
}


Door::Door(){
    type = '+';
}



Passage::Passage(){
    type = '#';
}
