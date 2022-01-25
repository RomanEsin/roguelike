//
//  Floor.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "Floor.hpp"

Floor::Floor(int x, int y, std::string sym) {
    this->x = x;
    this->y = y;
    this->symChar = sym[0];
}

GameResult Floor::collide(Zombie*) {
    return CanMove;
}
GameResult Floor::collide(AidKit*) {
    return Nothing;
}
GameResult Floor::collide(Floor*) {
    return Nothing;
}
GameResult Floor::collide(Princess*) {
    return CantMove;
}
GameResult Floor::collide(Knight*) {
    return CanMove;
}
GameResult Floor::collide(Dragon*) {
    return CanMove;
}
GameResult Floor::collide(Wall*) {
    return Nothing;
}
GameResult Floor::collide(Projectile*) {
    return CanMove;
}
