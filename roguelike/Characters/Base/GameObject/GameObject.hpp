//
//  GameObject.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>

enum GameResult { CanMove, CantMove, CanAttack, AidHP, Damage, Destroy, Nothing };

class Wall;
class Knight;
class Zombie;
class Dragon;
class Princess;
class AidKit;
class Projectile;
class Floor;

class GameObject {
public:
    char getSym();
    void hit(int damage);
    float getHp();

    virtual GameResult collide(Wall*) = 0;
    virtual GameResult collide(Knight*) = 0;
    virtual GameResult collide(Zombie*) = 0;
    virtual GameResult collide(Dragon*) = 0;
    virtual GameResult collide(Princess*) = 0;
    virtual GameResult collide(AidKit*) = 0;
    virtual GameResult collide(Projectile*) = 0;
    virtual GameResult collide(Floor*) = 0;
protected:
    int x;
    int y;
    char symChar;
    float hp;
    float maxHp;
};

#endif /* GameObject_hpp */
