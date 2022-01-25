//
//  Game.hpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Map.hpp"

class Game {
public:
    Game() = default;
    void start();
    void continueGame(Map map);
};

#endif /* Game_hpp */
