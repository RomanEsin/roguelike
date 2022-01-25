//
//  Floor.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Floor_hpp
#define Floor_hpp

#include "Gameobject.hpp"
#include <stdio.h>
#include <string>

class Floor: public GameObject {
public:
    Floor(int x, int y, std::string sym);
    GameResult collide(Zombie*) override;
    GameResult collide(Floor*) override;
    GameResult collide(Knight*) override;

    GameResult collide(Princess*) override;

    GameResult collide(AidKit*) override;

    GameResult collide(Dragon*) override;

    GameResult collide(Wall*) override;

    GameResult collide(Projectile*) override;
};

#endif /* Floor_hpp */
