//
//  Object.h
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-26.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Coordinates.h"



class Object{
    Coordinates position;
protected:
    char type;
public:
    Coordinates getCoord();
    void setCoord(Coordinates);
    char getType();
    virtual ~Object() = 0;

};
#endif /* Object_hpp */
