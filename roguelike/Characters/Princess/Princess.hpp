//
//  Princess.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Princess_hpp
#define Princess_hpp

#include <stdio.h>
#include <string>
#include "Character.hpp"

class Princess: public Character {
public:
    Princess() = default;
    Princess(int x, int y, std::string sym, std::string hp, std::string damage);
    GameResult collide(Zombie*) override;
    GameResult collide(Princess*) override;
    GameResult collide(Knight*) override;

    GameResult collide(Floor*) override;

    GameResult collide(AidKit*) override;

    GameResult collide(Dragon*) override;

    GameResult collide(Wall*) override;

    GameResult collide(Projectile*) override;
};

#endif /* Princess_hpp */
