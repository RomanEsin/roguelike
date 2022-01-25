//
//  AidKit.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef AidKit_hpp
#define AidKit_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include <string>

class AidKit: public GameObject {
public:
    AidKit(int x, int y, std::string sym);
    GameResult collide(Zombie*) override;
    GameResult collide(AidKit*) override;
    GameResult collide(Knight*) override;

    GameResult collide(Dragon*) override;

    GameResult collide(Princess*) override;

    GameResult collide(Floor*) override;

    GameResult collide(Wall*) override;

    GameResult collide(Projectile*) override;
};




#endif /* AidKit_hpp */
