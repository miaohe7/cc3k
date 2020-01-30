#include <iostream>
#include <fstream>
#include <vector>
#include "Level.h"
#include <algorithm>
#include <sstream>
#include <string>
#include "helpers.h"
#include "math.h"
#include <time.h>

using namespace std;



bool isDirection(string str){ // returns true if str is a direction
    vector <string> directions {"no","so", "ea", "we","ne","nw","se","sw"};
    for(auto dir:directions){
        if(dir == str) return true;
    }
    return false;
}



char printGameRules(){
    //print rules, return the type of PC the player chose.
    bool wrongCommand = true;
    char PCtype;
    cout <<"CC3k: Please choose your player character race: "<< endl;
    cout << "s -- Shade" << endl << "d -- Drow" << endl<< "v -- Vampire" << endl ;
    cout << "t -- Troll" << endl << "g -- goblin" << endl;
    while(wrongCommand){

        if(cin>> PCtype){
            if(PCtype == 's' || PCtype == 'd' || PCtype == 'v' ||
               PCtype == 't' || PCtype == 'g' ){
                wrongCommand = false;
                return PCtype;
            }
        }
        cout << "Invalid command." << endl;
    }
    return ' ';
}


void readIN(string fileName, vector <Level*> levels){
    // read in from an existing file and initialize all 5 levels.
    ifstream myFile(fileName);
    char c; // read in char by char
    for(int floor = 0; floor <5; floor++){
        Level* level = levels[floor];
        // create level
        for (int i = 0; i < 25; i++) {
            for(int j=0; j < 80; j++){
                myFile.get(c);
                if(c == '@'){
                    level->setInitial(Coordinates {i,j});
                } else {
                    level->set(i,j,c);
                }
             
            }
        }
    }
}




int main(int argc, const char * argv[]) {
    
    srand(time(NULL));

    bool game = true;

    while (game){
        //1) Initiate PC

        char PCtype = printGameRules();


        PC* pc;

        switch(PCtype){
            case 's':
                pc = new Shade {};
                break;
            case 'd':
                pc = new Drow {};
                break;
            case 'v':
                pc = new Vampire {};
                break;
            case 't':
                pc = new Troll {};
                break;
            default:
                pc = new Goblin {};
                break;
        } // done iniitializing pc


        // 2) Initiate Level

        Level* level0 = new Level {0, pc};
        Level* level1 = new Level {1, pc};
        Level* level2 = new Level {2, pc};
        Level* level3 = new Level {3, pc};
        Level* level4 = new Level {4, pc};

        vector <Level*> levels {level0,level1,level2,level3,level4};

        int current = 0;
        Level *currentLevel = levels[current];
        



        // initiate every floortile of level according to reading

        if(argc == 2){ // readIN and existing file
            string PRESET_FLOOR_FILE = argv[1];
            readIN(PRESET_FLOOR_FILE,levels);
            
        } else { // randomize all 5 floors
            readIN("emptyFloor.txt", levels);
            for(auto level: levels){
                // initiate all 5 levels;
                level->initRandom();
            }
            
            
        }
        
        // set first level PC coordinates according to reading.
        
        currentLevel->set(currentLevel->getInitial().x, currentLevel->getInitial().y, '@');
        
        


        // 3) display, ready to start game.


        cout << *currentLevel;
        cout << "Race: "<< charToRace(PCtype);
        cout << " Gold: " << pc->getGold();
        cout << "                                            Floor " << current+1 << endl;
        cout << "HP: " << pc->getHP()<< endl;
        cout << "Atk: " << pc->getATK() << endl;
        cout << "Def: " << pc->getDEF() << endl;
        
        cout << "action: " << endl;
        
				currentLevel->bindDragons();
			
        // while command loop to play the game
        string command;



        bool valid = false;
        bool EnemyCanMove = true;
        bool PCAlive = true;



        while(cin>> command){
            string action = "";

            if (isDirection(command)) {// move
                int validMove = currentLevel->PCMoves(command);
                if (validMove>0) {
                    action += "PC moves " + translateDirection(command)+ ". ";
                    valid = true;
                    if(validMove == 2){
                        action += "PC picked up gold. ";
                    }
                } else if(validMove ==0){
                    action += "PC cannot move there. ";
                    valid = true;
                } else {// moved to stairs, either new floor or won
                    //new floor
                    if(current == 4){ // won
                        int goldValue = (pc->getType() == 's')? ceil(pc->getGold() * 1.5): pc->getGold();
                        cout << "You won! Here is your gold " << goldValue<< endl;
                        cout << "Play again? (y/n)" << endl;
                        cin >> command;
                        if(command == "y"){
                            game = true;
                            break;
                        } else {
                            game = false;
                            break;
                        }

                    }
                    // new floor
                    current++;
                    currentLevel = levels[current];
                    currentLevel->set(currentLevel->getInitial().x, currentLevel->getInitial().y, '@');
                    pc->setATK(pc->getinitialATK());
                    pc->setDEF(pc->getinitialDEF());
                    valid = true;
                    action += "PC has moved to level " +makeString(current+1) + ".";
                }
                
                // enemy attack if close to pc:
                
                Enemy* enemyAttacked = currentLevel->enemyAttack();
                if(enemyAttacked){
                    char enemyType = enemyAttacked->getType();
                    
                    action += makeString(enemyType) + " attacks PC. ";
                }
                    
                //move enemies
                if(!enemyAttacked && valid && EnemyCanMove) currentLevel->EnemyMove();





            }else if(command == "c"){ // check Potion

                cin >> command;
                if(isDirection(command)){ // if(command is direction), else invalid already
                    string description = currentLevel->checkPotion(command);
                    if(description != ""){
                        action += "Potion type is " + description;
                        valid = true;
                    }

                }

            } else if(command == "u"){
                cin >> command;
                
                if(isDirection(command)){
                    char potionTaken = currentLevel->usePotion(command); // if there is a Potion, use it.
                    if (potionTaken != 'X'){
                        
                        action += "PC uses Potion " + translatePotion(potionTaken) + ".";
                        valid = true;
                    }
                }
            }


            else if(command == "a"){
                cin >> command;
                // if(command is direction), else invalid already
                if(isDirection(command)){

                    int success = currentLevel->PCattack(command);
                    valid = (success != 0);
                    if(success == -1){ // enemy died
                        action += "PC killed enemy.";
                       
                    } else if(success > 0){ // PC attacked
                        Enemy* enemyAttacked = currentLevel->enemyAttack();
                        if(enemyAttacked){
                            char enemyType = enemyAttacked->getType();

                            action += "PC deals " + makeString(success) + " damage to "+
                            makeString(enemyType) + ". Enemy attacks back. Enemy may have missed.";
                           

                        }
                    } else if (success == -2){ // Pc missed
                        Enemy* enemyAttacked = currentLevel->enemyAttack();
                        if(enemyAttacked){
                            char enemyType = enemyAttacked->getType();
                            
                            action += "PC missed, " + makeString(enemyType) + " attacks back. Enemy may have missed.";
                            
                        }
                    
                    }// don't do anything if did not attack, it is invalid input.
                }
                // not sure if enemies should move in combat.
                //if(valid && EnemyCanMove) level->EnemyMove();
            }

            else if(command == "f"){//Enemy cannot move
                EnemyCanMove = !EnemyCanMove;
                valid = true;
            } else if(command == "r"){
                // restart game
                valid = true;
                break;

            } else if(command == "q"){
                // exit game
                game = false;

                valid = true;
                
        
                break;
            }



            // done one turn
            if(!valid){

                action = "Invalid Command." ;
            }

            // print textdisplay, race of pc and action string.

            cout << *currentLevel;

            // print PC status
            cout << "Race: "<< charToRace(PCtype);
            cout << " Gold: " << pc->getGold();
            cout << "                                            Floor " << current+1 << endl;
            cout << "HP: " << pc->getHP()<< endl;
            cout << "Atk: " << pc->getATK() << endl;
            cout << "Def: " << pc->getDEF() << endl;
            PCAlive = (pc->getHP())>0;
            if(!PCAlive) { // PC died
                cout << "You lost! PC died! Play again? (y/n)" << endl;
                cin >> command;
                if(command == "y"){
                    game = true;
                    break;
                } else {
                    game = false;
                    break;
                }
            
            
            }
            cout << "action: " <<action << endl;

            action = "";

        } // end of while command loop

        for (auto level: levels){
            delete level;
        }
       
        delete pc;
    
        
    }// end of a round
    


} // end of main
