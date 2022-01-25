//
//  GameObject.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "GameObject.hpp"

char GameObject::getSym() {
    return this->symChar;
}
void GameObject::hit(int damage) {
    this->hp -= damage;
}
float GameObject::getHp() {
    return this->hp;
}
