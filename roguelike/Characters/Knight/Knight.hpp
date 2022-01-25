//
//  Knight.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Knight_hpp
#define Knight_hpp

#include <stdio.h>
#include <string>
#include "Character.hpp"

class Knight: public Character {
public:
    Knight() = default;
    Knight(int x, int y, std::string sym, std::string hp, std::string damage, std::string vision);
    std::pair<int,int> try_move(char a);
    void move(int x, int y);
    void Regeneration();
    GameResult collide(GameObject* buf);
    GameResult collide(Zombie*) override;
    GameResult collide(Knight*) override;
    GameResult collide(Dragon*) override;

    GameResult collide(Princess*) override;

    GameResult collide(AidKit*) override;

    GameResult collide(Floor*) override;

    GameResult collide(Wall*) override;

    GameResult collide(Projectile*) override;

};

#endif /* Knight_hpp */
