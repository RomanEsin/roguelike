//
//  Character.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "Character.hpp"

float Character::getDamage() {
    return this->damage;
}
std::pair<int, int> Character::getPos() {
    return {this->x,this->y};
}

int Character::getVision() {
    return this->vision;
}
