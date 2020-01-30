//
//  TextDisplay.h
//  cs246 part1
//
//  Created by Jia Ying Lin on 2016-11-26.
//  Copyright © 2016 Jia Ying Lin. All rights reserved.
//

#ifndef TextDisplay_hpp
#define TextDisplay_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "observer.h"


class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
    const int floorWidth = 80;
    const int floorHeight = 25;

public:
    TextDisplay();

    void notify(Subject &whoNotified) override;
    SubscriptionType subType() const override;

    ~TextDisplay();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif /* TextDisplay_hpp */
