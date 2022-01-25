//
//  Wall.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Wall_hpp
#define Wall_hpp

#include <stdio.h>
#include <string>
#include "GameObject.hpp"

class Wall: public GameObject {
public:
    Wall(int x, int y, std::string sym);

    GameResult collide(Zombie*) override;
    GameResult collide(Wall*) override;

    GameResult collide(Knight*) override;

    GameResult collide(Princess*) override;

    GameResult collide(AidKit*) override;

    GameResult collide(Dragon*) override;

    GameResult collide(Projectile*) override;

    GameResult collide(Floor*) override;
};

#endif /* Wall_hpp */
