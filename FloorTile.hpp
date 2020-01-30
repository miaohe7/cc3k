//
//  FloorTile.h
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-24.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#ifndef FloorTile_hpp
#define FloorTile_hpp

#include <vector>
#include "Object.h"
#include "subject.h"
#include "observer.h"




class FloorTile: public Subject{
    Coordinates position;
    Object* obj;
    
    bool occupied;
    bool inChamber; // is only relevant to differentiate '.' from ' '
public:
    FloorTile(Coordinates position);
    Object* getObject() override; // return Object pointer.
    Coordinates getCoord() override;// return FloorTile's coordinates

    void addObject(Object *); // add object to FloorTile
    void removeObject(); // remove o bject from FloorTile

    bool isOccupied(); // check if FloorTile is occupied
    bool isInChamber() override; // check if FloorTile is inside a chamber, and not a wall

    void setInChamber(bool); // set the FloorTile to be in or out a chamber.
    void setOccupied(bool); // set FloorTile to be occupied or not occupied.

    ~FloorTile(); // dtor
   
    


};

#endif /* FloorTile_hpp */
