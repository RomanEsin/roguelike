//
//  Princess.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "Princess.hpp"

Princess::Princess(int x, int y, std::string sym, std::string hp, std::string damage) {
    this->hp = stoi(hp);
    this->symChar = sym[0];
    this->damage = stoi(damage);
    this->maxHp = stoi(hp);
    this->x = x;
    this->y = y;
}

GameResult Princess::collide(Zombie*) {
    return CantMove;
}
GameResult Princess::collide(Princess*) {
    return CantMove;
}
GameResult Princess::collide(Dragon*) {
    return CantMove;
}
GameResult Princess::collide(Knight*) {
    return CantMove;
}
GameResult Princess::collide(AidKit*) {
    return Nothing;
}
GameResult Princess::collide(Floor*) {
    return Nothing;
}
GameResult Princess::collide(Wall*) {
    return Nothing;
}
GameResult Princess::collide(Projectile*) {
    return Damage;
}
