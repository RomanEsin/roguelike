//
//  Zombie.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Zombie_hpp
#define Zombie_hpp

#include <stdio.h>
#include <string>
#include "Character.hpp"

class Zombie : public Character {
public:
    Zombie(int x, int y, std::string sym, std::string hp, std::string damage);
    void move(int x, int y);
    GameResult collide(Floor*) override;
    GameResult collide(Zombie*) override;
    GameResult collide(Knight*) override;

    GameResult collide(Princess*) override;

    GameResult collide(AidKit*) override;

    GameResult collide(Dragon*) override;

    GameResult collide(Wall*) override;

    GameResult collide(Projectile*) override;
    GameResult Collide(GameObject* buf);
};

#endif /* Zombie_hpp */
