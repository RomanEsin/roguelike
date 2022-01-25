//
//  Projectile.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "Projectile.hpp"

Projectile::Projectile(int x, int y,std::pair<int,int> dir) {
    this->x = x;
    this->y = y;
    this->symChar ='*';
    this->direction = dir;
    this->damage = 20;
}

void Projectile::fly() {
    this->x += this->direction.first;
    this->y += this->direction.second;
}

GameResult Projectile::collide(Zombie*) {
    return CantMove;
}
GameResult Projectile::collide(Projectile*) {
    return Destroy;
}
GameResult Projectile::collide(Dragon*) {
    return CantMove;
}
GameResult Projectile::collide(Princess*) {
    return CantMove;
}
GameResult Projectile::collide(AidKit*) {
    return Destroy;
}
GameResult Projectile::collide(Floor*) {
    return Nothing;
}
GameResult Projectile::collide(Wall*) {
    return Destroy;
}
GameResult Projectile::collide(Knight*) {
    return CantMove;
}
GameResult Projectile::collide(GameObject* buf) {
    return buf->collide(this);
}
