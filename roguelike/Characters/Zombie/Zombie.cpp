//
//  Zombie.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "Zombie.hpp"

Zombie::Zombie(int x, int y, std::string sym, std::string hp, std::string damage){
    this->hp = stoi(hp);
    this->symChar = sym[0];
    this->damage = stoi(damage);
    this->maxHp = stoi(hp);
    this->x = x;
    this->y = y;
}

void Zombie:: move(int x, int y) {
    this->x = x;
    this->y = y;
}

GameResult Zombie::collide(Knight*) {
    return CanAttack;
}
GameResult Zombie::collide(Zombie*) {
    return CantMove;
}
GameResult Zombie::collide(Dragon*) {
    return CantMove;
}
GameResult Zombie::collide(Princess*) {
    return CantMove;
}
GameResult Zombie::collide(AidKit*) {
    return Nothing;
}
GameResult Zombie::collide(Floor*) {
    return Nothing;
}
GameResult Zombie::collide(Wall*) {
    return Nothing;
}
GameResult Zombie::collide(Projectile*) {
    return CanAttack;
}
GameResult Zombie::Collide(GameObject* buf) {
    return buf->collide(this);
}
