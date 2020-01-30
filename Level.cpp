#include "Level.h"
#include "enemy.h"
#include "treasureTypes.h"
#include "potionTypes.h"
#include <stdio.h>
#include "helpers.h"

using namespace std;

Level::Level(int floorCount, PC* pc) :floorCount{floorCount}, pc {pc}{
    // initialize td
    td = new TextDisplay{};
    pcInitial= Coordinates{0,0};
    floorWidth = 80;
    floorHeight = 25;
    
     directions = {"no","so","ea", "we","ne","nw","se","sw"};
    
    // Need to initialize each chamber

    //Chamber 1
    for (int i = 3; i <= 28; ++i){
        for (int j = 3; j <= 6;++j){
            chamber1.push_back(Coordinates{j,i});
        }

    }

		//Chamber 2
    for (int i = 3; i <= 4; ++ i){
        for (int j = 39; j <= 61; ++j){
            chamber2.push_back(Coordinates{i,j});

        }
    }

    for (int i = 39; i <= 69; ++i){
        chamber2.push_back(Coordinates{5,i});
    }

    for (int i = 39; i <= 72; ++i){
        chamber2.push_back(Coordinates{6,i});
    }
            
    for (int i = 7; i <= 12 ; ++i){
        for (int j = 61; j <= 75; ++j){
            chamber2.push_back(Coordinates{i,j});
        }
    }

    // chamber 3
    for (int i = 10; i <= 12; ++i){
        for (int j = 38; j <= 49; j++){
            chamber3.push_back(Coordinates{i,j});
        }
    }

    // chamber 4
    for (int i = 15; i<= 21; ++i){
        for (int j = 4; j<= 24;++j){
            chamber4.push_back(Coordinates{i,j});
        }
    }


    //chamber5

    for (int i = 16 ; i <= 18; i++){
        for (int j = 65; j <= 75; ++j){
            chamber5.push_back(Coordinates{i,j});
        }
    }
        
    for (int i = 19; i <= 21; ++i){
        for (int j = 37; j <= 75; ++j){
            chamber5.push_back(Coordinates{i,j});
        }
    }
	
    // Chamber initalization done

    // floorGrid initialization?
    
    for(int i = 0; i<floorHeight; i++){
        vector<FloorTile> newRow;
        for(int j = 0; j<floorWidth; j++){
            newRow.push_back(FloorTile{Coordinates{i,j}});
        }
        floorGrid.push_back(newRow);
    }
    
    

    // attach observers
    for(int i = 0; i<floorHeight; i++){
        for(int j = 0; j<floorWidth; j++){
            // add textDisplay observer

            floorGrid[i][j].attach(td);

        }
    }
}



void Level::set(int x, int y , char c){
    floorGrid[x][y].setOccupied(true);

    switch (c) {
            // PC
        case '@':
            floorGrid[x][y].addObject(pc);
            pcInitial = Coordinates {x,y};
            break;
            // Stairs
        case '\\':
            floorGrid[x][y].addObject(new Stairs());
            break;
        case '.':
            floorGrid[x][y].setInChamber(true);
            floorGrid[x][y].setOccupied(false);
            floorGrid[x][y].notifyObservers(SubscriptionType::All);

            break;
            // Wall
        case '-':
            floorGrid[x][y].addObject(new HorizontalWall());
            break;
        case '|':
            floorGrid[x][y].addObject(new VerticalWall());
            break;
            // Door
        case '+':
            floorGrid[x][y].addObject(new Door());
            break;
            //Passage
        case '#':
            floorGrid[x][y].addObject(new Passage());
            break;
            // Enemy
        case 'H':{
            floorGrid[x][y].addObject(new Human());
            Enemy* ene = dynamic_cast<Enemy *>(floorGrid[x][y].getObject());
            enemies.push_back(ene);
            break;
        }
        case 'W':{
            floorGrid[x][y].addObject(new Dwarf());
            Enemy* ene = dynamic_cast<Enemy *>(floorGrid[x][y].getObject());
            enemies.push_back(ene);
            break;
        }
        case 'E':{
            floorGrid[x][y].addObject(new Elf());
            Enemy* ene = dynamic_cast<Enemy *>(floorGrid[x][y].getObject());
            enemies.push_back(ene);
            break;
        }
        case 'O':{
            floorGrid[x][y].addObject(new Orcs());
            Enemy* ene = dynamic_cast<Enemy *>(floorGrid[x][y].getObject());
            enemies.push_back(ene);
            break;
        }
        case 'M':{
            floorGrid[x][y].addObject(new Merchant());
            Enemy* ene = dynamic_cast<Enemy *>(floorGrid[x][y].getObject());
            enemies.push_back(ene);
            break;
        }
        case 'D':{
            floorGrid[x][y].addObject(new Dragon());
            Enemy* ene = dynamic_cast<Enemy *>(floorGrid[x][y].getObject());
            enemies.push_back(ene);
            break;
        }
        case 'L':{
            floorGrid[x][y].addObject(new Halfling());
            Enemy* ene = dynamic_cast<Enemy *>(floorGrid[x][y].getObject());
            enemies.push_back(ene);
            break;
        }

            // Potion
        case '0':
            floorGrid[x][y].addObject(new RH());
            break;
        case '1':
            floorGrid[x][y].addObject(new BA());
            break;
        case '2':
            floorGrid[x][y].addObject(new BD());
            break;
        case '3':
            floorGrid[x][y].addObject(new PH());
            break;
        case '4':
            floorGrid[x][y].addObject(new WA());
            break;
        case '5':
            floorGrid[x][y].addObject(new WD());
            break;
            // Treasure
        case '6':
            floorGrid[x][y].addObject(new NormalHoard());
            break;
        case '7':
            floorGrid[x][y].addObject(new SmallHoard());
            break;
        case '8':
            floorGrid[x][y].addObject(new MerchantHoard());
            break;
        case '9':
            floorGrid[x][y].addObject(new DragonHoard());
            break;
        default:
            floorGrid[x][y].setInChamber(false);
            floorGrid[x][y].setOccupied(false);
            break;
    }



}



FloorTile* Level::get(int x, int y){
    return &floorGrid[x][y];
}





FloorTile* Level::newFT(Coordinates startPoint, string direction){

    int x, y;
    int i = startPoint.x;
    int j = startPoint.y;

    if(direction == "no"){// no need to check Boundary points of floorGrid since
            // Objects will always be inside a chamber, never at the edge of floor

        x = i-1;
        y = j;
    }else if (direction == "so"){
        x = i+1;
        y = j;
    }else if (direction == "we"){
        x = i;
        y = j-1;
    }else if (direction == "ea"){
        x = i;
        y = j+1;
    }else if (direction == "nw"){
        x = i-1;
        y = j-1;
    }else if (direction == "ne"){
        x = i-1;
        y = j+1;
    }else if (direction == "sw"){
        x = i+1;
        y = j-1;
    }else if (direction == "se"){
        x = i+1;
        y = j+1;
    } else{   // invalid input, by default gives empty
         return nullptr;
    }

        return &floorGrid[x][y];
}




void Level::move(Coordinates startPoint,string direction){
    int x = startPoint.x;
    int y = startPoint.y;
    Object* tempObject = floorGrid[x][y].getObject();
    floorGrid[x][y].removeObject();
    FloorTile*  newFloorTile= newFT(startPoint, direction);
    newFloorTile->addObject(tempObject);
}




int Level::PCMoves(string direction){
    //check if valid move
    FloorTile* destination = newFT(pc->getCoord(), direction);
    
    
    if (!destination){
        
        return 0; // unvalid direction
    }
    if(destination->getObject()){ // pick up gold if there is one.
        char type = destination->getObject()->getType();
        if(type >= '6' && type <= '9'){
            
            int x = destination->getCoord().x;
            int y = destination->getCoord().y;

            Object* obj = floorGrid[x][y].getObject();

            Treasure* treasure = dynamic_cast <Treasure *> (obj);
            
            if(treasure->canPickup() ==  false) return 0; //check if it's dragonhoard
            
            pc->takeGold(treasure);

            
            
            destination->removeObject();
            delete treasure;
            move(pc->getCoord(), direction);

            return 2; // picked up gold
        }
        if(type == '\\'){
            // next level
            // need to add code here to initiate new level.
            // special case, need to communicate this information back to main
            // in order to read in new floor. may need to change return type.
            return -1;
        }
        if (type == '#' || type == '+'){
            // remove the object type # or +
            destination->removeObject();
            // move there
            move(pc->getCoord(), direction);
            return 1;
        }
    } else{
        if(destination->isInChamber() && !(destination->isOccupied())){ // there is free space
            move(pc->getCoord(), direction);
            return 1;
        }
    }
    
    // cannot move to the given direction
    return 0;
}


string Level::checkPotion(string direction){

    Coordinates pcCoords = pc->getCoord();
    FloorTile *tempTile = newFT(pcCoords, direction);
    if(tempTile->getObject()){
        char newType =tempTile->getObject()->getType();

        if (newType <= '5' && newType >='0'){   // makes sure that there's a potion in that location
            Potion* potion = dynamic_cast <Potion* > (tempTile->getObject());
            return potion->getDescription();
            // shows the description of the potion if has been ided, "Unknown potion" else
        }
    }

    return ""; // no Potion there

}



char Level::usePotion(string direction){
    Coordinates pcCoords = pc->getCoord();
    FloorTile *tempTile = newFT(pcCoords, direction);
    Potion *potion = dynamic_cast <Potion *> (tempTile->getObject());
    if(potion){
        char potionType = potion->getType();
        pc->takePotion(potion);// takes the potion in the location specified
        
        // need to delete potion
        
        delete potion;
        
        tempTile->removeObject();
        
        // Tells the floortile that the potion has been consumed
        return potionType;
    }
    return 'X'; // no potion there
} // If there is a Potion, use it.


bool isValidEnemyType(char type){
    switch (type) {
        case 'W':
            return true;
        case 'O':
            return true;
        case 'H':
            return true;
        case 'E':
            return true;
        case 'M':
            return true;
        case 'D':
            return true;
        case 'L':
            return true;
        default:
            return false;
    }
}


int Level::PCattack(string direction){
    Coordinates pcCoords = pc->getCoord();
   // int x = pcCoords.x;
   // int y = pcCoords.y;
    FloorTile *enemyTile = newFT(pcCoords,direction);
    // If there is an enemy,attack it and enemy will react.
    char enemyType;

    // Check for valid command
    if(enemyTile->getObject() == nullptr){
        
        return 0; // no object
    }
    enemyType = enemyTile->getObject()->getType();

    // if it is a valid command
    if (isValidEnemyType(enemyType)){
        // attack the enemy
        Enemy* ene = dynamic_cast<Enemy *>(enemyTile->getObject());
        int success =  pc->attack(ene); // return an int
        if(success>0){ // attack is success
            return success;

        }else if (success == 0){ // missed
            
            return -2;

        } else{ // enemy died
            
            
            
            enemyTile->removeObject();

            switch (enemyType) {
                case 'H':
                case 'M':
                {
                    Object * goldDropped = dynamic_cast<Object *>(new MerchantHoard ());
                    enemyTile->addObject(goldDropped);
                    break;
                }
                case 'D':
                    break;

                default:
                    int goldDropped = rand() % 2 + 1;
                    pc->takeGold(goldDropped);
                    break;
            }

            deleteEnemy(ene->getCoord());
            return -1;
        }


    } else {
        
        return 0; // object not enemy
    }

}



Enemy* Level::enemyAttack(){ // Each enemy on the floor will attack, if PC is near
    for(auto enemy:enemies){
        // if enemy is dragon, then also check if pc is next to its gold.
        if (enemy->getType() == 'D'){
            // find where its gold is
            Treasure* gold = nullptr;
            for(auto dir: directions){
                Object* obj =newFT(enemy->getCoord(),dir)->getObject();
                if(obj){
                    if(obj->getType() == '9'){ //
                        gold = dynamic_cast <Treasure *> (obj);
                    }
                }
            }
        // once we have the gold, check if pc is near by gold
            if(gold){
                for(auto dir: directions){
                    // check if PC is in this direction of gold
                    Object* newObj = newFT(gold->getCoord(),dir)->getObject();
                    PC* pc1 = dynamic_cast<PC *>(newObj);
                    if(pc1){
                        // check if it is pc
                        enemy->attack(pc); // attack pc
                        return enemy;
                    }
                }
            }
        }
        
        
        // for all enemies
        for(auto dir: directions){
            //check if enemy is hostile (only Merchant canbe not hostile)
            if(!enemy->isHostile()) break;
            
            // check if PC is in this direction of this enemy
            Object* newObj = newFT(enemy->getCoord(),dir)->getObject();

            PC* pc1 = dynamic_cast<PC *>(newObj);
            if(pc1){
                // check if it is pc
                enemy->attack(pc); // attack pc

                return enemy;
            }
        }
    }
    return nullptr; // cannot attack
}


template <typename T>

T Level::pickFromList(vector <T> v){
    int length =int(v.size());
    int index = rand() % length;
    return v[index];
}




bool Level::EnemyMove(){
    bool moved = false;
    for(auto enemy: enemies){
        if(enemy->getType() != 'D'){
            // first check if it is a .
            // enemy cannot leave chamber
            vector <string> validDirections;
            for (auto dir: directions){
                FloorTile* newft = newFT(enemy->getCoord(), dir);

                if(!(newft->getObject())&& (newft->isInChamber())){
                    validDirections.push_back(dir);
                }
            }
            // pick one direction from the valid ones.
            if(!validDirections.empty()){
                string direction = pickFromList(validDirections);
                move(enemy->getCoord(), direction);  // move there and break;
                moved = true;
            }
        }
    }
    return moved;
}


// Delete an enemy from the vector of Enemies and delete the pointer
void Level::deleteEnemy(Coordinates enemyCords){
    int enemy_X = enemyCords.x;
    int enemy_Y = enemyCords.y;
    int length = int(enemies.size());
    for (int i = 0; i< length; i++){
        int this_X = (enemies[i]->getCoord()).x;
        int this_Y = (enemies[i]->getCoord()).y;

        if((this_X == enemy_X) && (this_Y == enemy_Y)){
            Enemy * temp = enemies[i];
            enemies.erase(enemies.begin()+i);
            delete temp;
        }
        
    }
}



// For preset floors, call this to bind dragons to nearest dragon hoard
void Level::bindDragons(){
    //go through the list of the enemies to find the dragon that needs to be binded
    for(auto enemy:enemies){
        // if enemy is dragon, then also check if pc is next to its gold.
        if (enemy->getType() == 'D'){
            Dragon * dragon = nullptr;
            // find where its gold is
            DragonHoard* gold = nullptr;
            for(auto dir: directions){
                Object* obj =newFT(enemy->getCoord(),dir)->getObject();
                if(obj){
                    if(obj->getType() == '9'){ //if it is a dragonHoard
                        gold = dynamic_cast <DragonHoard *> (obj);
                        if (gold->isThisBinded() == false){
                            dragon = dynamic_cast<Dragon *>(enemy);
                            dragon->bindHoard(gold);
                            gold->bindThis();
                        }
                    }
                }
            }
        }
    }
}


// Randomly generate a coordinate from chamber number, "chamber"
Coordinates Level::randomCord(int chamber){
	int chamberIndex;
	switch (chamber) {
		case 0:
			chamberIndex = rand() % 108;
			return chamber1[chamberIndex];
		case 1:
			chamberIndex = rand() % 201;
			return chamber2[chamberIndex];
		case 2:
			chamberIndex = rand() % 39;
			return chamber3[chamberIndex];
		case 3:
			chamberIndex = rand() % 147;
			return chamber4[chamberIndex];
		default:
			chamberIndex = rand() % 150;
			return chamber5[chamberIndex];
	}
	
}


void Level::initRandom(){

	// 1) set PC
	int pcChamber = randomChamber();
	pcInitial = randomCord(pcChamber);
	
	
	// 2) set Stairs (not in same chamber as PC)
	int stairChamber = randomChamber();
	while (stairChamber == pcChamber) {
		stairChamber = randomChamber();
	}
	Coordinates stairCoords = randomCord(stairChamber);
	set(stairCoords.x,stairCoords.y,'\\');
	
	// 3) set potion
	char typesOfPotions[6]{'0','1','2','3','4','5'};
	for (int i = 0; i < 10; ++i){
		char newPotionType = typesOfPotions[rand() % 6];
		bool occupied = true;
		Coordinates potionCoord;
		while (occupied) {
			int potionChamber = randomChamber();
			potionCoord = randomCord(potionChamber);
			FloorTile *temp = get(potionCoord.x,potionCoord.y);
			if (temp->getObject() == nullptr){
				occupied = false;
				
			}
		}
		set(potionCoord.x,potionCoord.y,newPotionType);
	}
	
	// 4) set treasure
	char typesOfTreasure[8]{'6','6','6','6','6','9','7','7'};
	for (int i = 0; i < 10; ++i){
		char newTreasureType = typesOfTreasure[rand() % 8];
		bool occupied = true;
		Coordinates treasureCoord;
		while (occupied){
			int treasureChamber = randomChamber();
			treasureCoord = randomCord(treasureChamber);
			FloorTile *temp = get(treasureCoord.x,treasureCoord.y);
			if (temp->getObject() == nullptr){
				occupied = false;
			}
		}
		
		set(treasureCoord.x,treasureCoord.y,newTreasureType);
		
		// If treasure type spawned was a dragon hoard
		if (newTreasureType == '9'){
			Coordinates dragonCoord;
			for(auto dir: directions){
				FloorTile *temp =newFT(treasureCoord,dir);
				if((temp->getObject()==nullptr)){
					dragonCoord = temp->getCoord();
					set(dragonCoord.x,dragonCoord.y,'D');
					break;
				}
			}
		}
	}


	// 5) set enemies
	char typesOfEnemies[18]{'H','H','H','H','W','W','W','L','L','L','L','L',
	'E','E','O','O','M','M'};
	for (int i = 0; i < 20; ++i){
		char newEnemyType = typesOfEnemies[rand() % 18];
		bool occupied = true;
		Coordinates enemyCoord;
		while(occupied){
			int enemyChamber = randomChamber();
			enemyCoord = randomCord(enemyChamber);
			FloorTile *temp = get(enemyCoord.x,enemyCoord.y);
			if (temp->getObject() == nullptr){
				occupied = false;
			}
		}
		set(enemyCoord.x,enemyCoord.y,newEnemyType);
	}
}


Coordinates Level::getInitial(){
    return pcInitial;
}


void Level::setInitial (Coordinates pos){
    pcInitial = pos;
}



Level::~Level(){
    floorGrid.clear();
    delete td;
}




ostream &operator<<(std::ostream &out, const Level& level){
    out << (*level.td);
    return out;
}
