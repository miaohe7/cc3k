//
//  level.h
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-26.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

#include <stdio.h>
#include "FloorTile.h"
#include <vector>
#include "pc.h"
#include "Coordinates.h"
#include "Stairs.h"
#include <string>
#include <iostream>
#include "TextDisplay.h"


class Level{

    int floorCount;
    PC* pc;
    Coordinates pcInitial;
    std::vector <std::vector < FloorTile>> floorGrid;
    std::vector<Enemy* > enemies; // all enemies on floor execpt dragon
    TextDisplay *td;
    int floorWidth;
    int floorHeight = 25;
    std::vector <std::string> directions {"no","so","ea", "we","ne","nw","se","sw"};
    std::vector <Coordinates> chamber1, chamber2, chamber3, chamber4,chamber5;
    // set all 5 chambers to their Coordinates. only inside counts

    FloorTile* newFT(Coordinates startPoint, std::string direction);
    // check what is in the FloorTile in this direction, from startPoint.
    void move(Coordinates startPoint, std::string direction);
    // move object to given direction. input must be valid.

    void deleteEnemy(Coordinates);
public:
    Level(int floorCount, PC* pc);
    void set(int x, int y , char c);
    // initiate the FloorTile at position x,y according to char c.

    FloorTile * get(int x, int y); // return the Floortile at position x,y
    void initRandom(); // Set an empty floor and randomly populate it.
    int PCMoves(std::string direction); // If Direction is valid, move pc.
    // if there is gold at that position, pick it up.

    std::string checkPotion(std::string direction); // check if there is potion and return description if so
    char usePotion(std::string direction); // Use Potion
    int PCattack(std::string direction); // If there is an enemy,attack it.
    Enemy* enemyAttack(); //Enemy attack PC if it is near.


    bool EnemyMove(); // randomly move all enemies
    template <typename T> T pickFromList(std::vector <T> );
    // pick a random item from the given list.
    
    void bindDragons(); // Bind dragons to nearest treasure
    
    
    friend std::ostream &operator<<(std::ostream&, const Level&);
		Coordinates randomCord(int);
    Coordinates getInitial(); // returns pcInitial field
    void setInitial (Coordinates); // set pcInitial

    ~Level();
};




#endif /* level_hpp */
