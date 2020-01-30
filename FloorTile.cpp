//
//  FloorTile.cpp
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-24.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#include "FloorTile.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "subscriptions.h"
#include <stdio.h>

FloorTile::FloorTile (Coordinates position): position {position}{
    obj = nullptr;

}

Object* FloorTile::getObject(){
    return obj;

}


Coordinates FloorTile::getCoord(){
    return position;
}


void FloorTile::addObject(Object *object){
    obj = object;
    object->setCoord(position);
    setOccupied(true);
    notifyObservers(SubscriptionType::All);

}


void FloorTile::removeObject(){
    if(obj){
        if(obj->getType() == '+'||obj->getType() == '#'){
            // remove the object if it is a door way or passage
            delete obj;
            obj = nullptr;
            
        }
        else {
            obj = nullptr;
        }
        setInChamber(true);
        setOccupied(false);
        notifyObservers(SubscriptionType::All);
    }

}


bool FloorTile::isOccupied(){
    return occupied;
}


bool FloorTile::isInChamber(){
    return inChamber;
}


void FloorTile::setInChamber(bool in){
    inChamber = in;
}


void FloorTile::setOccupied(bool occ){
     occupied = occ;
}


FloorTile::~FloorTile(){
    //check if object is pc, if it is not, delete the object
    if(obj){
        
        if(!(obj->getType() == '@')){
            delete obj;
            
        }
    }
}



