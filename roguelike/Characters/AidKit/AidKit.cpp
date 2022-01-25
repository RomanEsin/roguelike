//
//  AidKit.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "AidKit.hpp"

AidKit::AidKit(int x, int y, std::string sym) {
    this->x = x;
    this->y = y;
    this->symChar = sym[0];
}

GameResult AidKit::collide(Zombie*) {
    return Destroy;
}
GameResult AidKit::collide(AidKit*) {
    return Nothing;
}
GameResult AidKit::collide(Dragon*) {
    return Destroy;
}
GameResult AidKit::collide(Princess*) {
    return Destroy;
}
GameResult AidKit::collide(Knight*) {
    return AidHP;
}
GameResult AidKit::collide(Floor*) {
    return Nothing;
}
GameResult AidKit::collide(Wall*) {
    return Nothing;
}
GameResult AidKit::collide(Projectile*) {
    return Destroy;
}
