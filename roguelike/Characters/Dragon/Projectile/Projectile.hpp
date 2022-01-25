//
//  Projectile.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include <utility>

class Projectile: public GameObject {
public:
    void fly();
    Projectile() = default;
    GameResult collide(Zombie*) override;
    GameResult collide(Projectile*) override;
    GameResult collide(Knight*) override;

    GameResult collide(Princess*) override;

    GameResult collide(AidKit*) override;

    GameResult collide(Dragon*) override;

    GameResult collide(Wall*) override;

    GameResult collide(Floor*) override;
    GameResult collide(GameObject* buf);
    std::pair<int, int> direction;
    int damage;
    int x;
    int y;
    Projectile(int x,int y,std::pair<int,int> dir);
};

#endif /* Projectile_hpp */
