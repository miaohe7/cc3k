//
//  TextDisplay.cpp
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-26.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#include "TextDisplay.h"
#include "Coordinates.h"
#include "subject.h"
#include <stdio.h>

using namespace std;

TextDisplay::TextDisplay() {
	for(int i = 0; i< floorHeight; i++){
		vector<char> newRow;
		for (int j = 0; j< floorWidth; j++){
			newRow.push_back(' ');
		}
		theDisplay.push_back(newRow);
	}
}


void TextDisplay::notify(Subject &whoNotified) {
    //A FloorTile has notified TextDisplay
    Coordinates position = whoNotified.getCoord();
    char theType;
    //need to consider the . option and convert things to G and P
    if(whoNotified.getObject()){
        theType =whoNotified.getObject()->getType();
        
        
        if(theType <= '5' && theType >='0'){
            theType = 'P';
        } else if (theType <='9' && theType >= '6'){
            theType = 'G';
        }
    } else {
        theType = whoNotified.isInChamber()? '.': ' ';
    }

    theDisplay[position.x][position.y] = theType;

}


TextDisplay::~TextDisplay() {}


SubscriptionType TextDisplay::subType() const {
    return SubscriptionType::All;
}


ostream &operator<<(ostream &out, const TextDisplay &td) {
    for(int i = 0; i< td.floorHeight; i++){
        for (int j = 0; j< td.floorWidth; j++){
            cout << td.theDisplay[i][j];
        }
        cout << endl;
    }
    return out;
}
