//
//  Dragon.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Dragon_hpp
#define Dragon_hpp

#include <stdio.h>

#include <string>
#include "Character.hpp"
#include "Projectile.hpp"

class Dragon: public Character {
public:
    Dragon(int x, int y, std::string sym, std::string hp, std::string damage);
    Projectile Attack(int x,int y);
    void move(int x, int y);
    GameResult collide(Zombie*) override;
    GameResult collide(Dragon*) override;
    GameResult collide(Knight*) override;

    GameResult collide(Princess*) override;

    GameResult collide(AidKit*) override;

    GameResult collide(Floor*) override;

    GameResult collide(Wall*) override;

    GameResult collide(Projectile*) override;
    GameResult Collide(GameObject* buf);
};

#endif /* Dragon_hpp */
