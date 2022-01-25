//
//  Map.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <vector>
#include <memory>

#include "Character.hpp"
#include "Knight.hpp"
#include "Princess.hpp"
#include "Zombie.hpp"
#include "Dragon.hpp"

class Map {
public:
    Map();
    ~Map();

    void printOut();

    char getSym(int x, int y);

    void printWin();
    void printLose();
    bool winOrLose();

    void destroyObject(int x, int y);
    std::shared_ptr<GameObject> getObjectAt(int x, int y);

    std::shared_ptr<Knight> knight;
    std::shared_ptr<Princess> princess;
    std::vector<std::vector<std::shared_ptr<GameObject>>> mapObjects;
    std::vector<std::shared_ptr<Zombie>> zombies;
    std::vector<std::shared_ptr<Dragon>> dragons;
    std::vector<std::shared_ptr<Projectile>> projectiles;
};

#endif /* Map_hpp */
