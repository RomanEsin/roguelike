//
//  Knight.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "Knight.hpp"
#include <string>

Knight::Knight(int x, int y, std::string sym, std::string hp, std::string damage, std::string vision) {
    this->hp = stoi(hp);
    this->symChar = sym[0];
    this->damage = stoi(damage);
    this->maxHp = stoi(hp);
    this->x = x;
    this->y = y;
    this->vision = stoi(vision);
}

std::pair<int,int> Knight::try_move(char a){
    int buf_x = this->x;
    int buf_y = this->y;

    if (a == 'W'){
        buf_x--;
    }
    if (a == 'S'){
        buf_x++;
    }
    if (a == 'A'){
        buf_y--;
    }
    if (a == 'D') {
        buf_y++;
    }
    
    return std::pair<int, int>(buf_x, buf_y);
}

void Knight::move(int x, int y) {
    this->x = x;
    this-> y = y;
}

void Knight::Regeneration() {
    if (this->hp + 30 > this->maxHp) {
        this->hp = this->maxHp;
    }
    else {
        this->hp += 30;
    }
}

GameResult Knight::collide(Zombie*) {
    return CanAttack;
}
GameResult Knight::collide(Knight*) {
    return CantMove;
}
GameResult Knight::collide(Dragon*) {
    return CanAttack;
}
GameResult Knight::collide(Princess*) {
    return CantMove;
}
GameResult Knight::collide(AidKit*){
    return AidHP;
}
GameResult Knight::collide(Floor*) {
    return Nothing;
}
GameResult Knight::collide(Wall*) {
    return Nothing;
}
GameResult Knight::collide(Projectile*) {
    return CanAttack;
}
GameResult Knight::collide(GameObject* buf) {
    return buf->collide(this);
}
