//
//  Character.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Character_hpp
#define Character_hpp

#include "GameObject.hpp"
#include <utility>
#include <stdio.h>

class Character : public GameObject {
protected:
    float damage;

    int vision;
public:

    float getDamage();
    char GetSym();
    int getVision();
    std::pair<int, int> getPos();
};


#endif /* Character_hpp */
