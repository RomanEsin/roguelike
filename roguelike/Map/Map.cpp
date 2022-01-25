//
//  Map.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include "Map.hpp"

#include <fstream>
#include <string>
#include <map>
#include <math.h>
//#include <curses.h>
#include "iostream"

#include "GameObject.hpp"
#include "Wall.hpp"
#include "Zombie.hpp"
#include "Dragon.hpp"
#include "Knight.hpp"
#include "Floor.hpp"
#include "AidKit.hpp"


std::map<std::string, std::string> readConfig() {
    std::ifstream fin("config.txt");
    std::string buf;
    std::map<std::string, std::string> constants;
    while (fin >> buf) {
        auto index = buf.find('=');
        constants.emplace(buf.substr(0, index), buf.substr(index + 1));
    }
    fin.close();
    return constants;
}

Map::Map() {
    std::map<std::string, std::string> constants = readConfig();
    
    std::string mapName = "map1.txt";
//    std::cout << "Введите название файла карты:" << std::endl;
//    std::cin >> mapName;

    std::ifstream fin(mapName);
    int num_row = 0;
    fin >> num_row;

    for (int x = 0; x < num_row; x++) {
        std::string mapLine;
        fin >> mapLine;
        std::vector<std::shared_ptr<GameObject>> mapLineObjects;

        for (int y = 0; y < mapLine.size(); y++) {
            switch (mapLine[y]) {
                case '#':
                    mapLineObjects.push_back(std::make_shared<Wall>(x, y, constants["WALL_CHAR"]));
                    break;
                case '.':
                    mapLineObjects.push_back(std::make_shared<Floor>(x, y, constants["FLOOR_CHAR"]));
                    break;
                case '+':
                    mapLineObjects.push_back(std::make_shared<AidKit>(x, y, constants["AIDKIT_CHAR"]));
                    break;
                case 'K':
                    this->knight = std::make_shared<Knight>(x, y, constants["KNIGHT_CHAR"], constants["KNIGHT_HP"], constants["KNIGHT_DAMAGE"], constants["KNIGHT_VISION"]);
                    mapLineObjects.push_back(this->knight);
                    break;
                case 'P':
                    this->princess = std::make_shared<Princess>(x, y, constants["PRINCESS_CHAR"], constants["PRINCESS_HP"], constants["PRINCESS_DAMAGE"]);
                    mapLineObjects.push_back(this->princess);
                    break;
                case 'Z':
                    this->zombies.push_back(std::make_shared<Zombie>(x, y, constants["ZOMBIE_CHAR"], constants["ZOMBIE_HP"], constants["ZOMBIE_DAMAGE"]));
                    mapLineObjects.push_back(this->zombies[zombies.size()-1]);
                    break;
                case 'D':
                    this->dragons.push_back(std::make_shared<Dragon>(x, y, constants["DRAGON_CHAR"], constants["DRAGON_HP"], constants["DRAGON_DAMAGE"]));
                    mapLineObjects.push_back(this->dragons[dragons.size()-1]);
                    break;
                default:
                    exit(-1);
                    break;
            }
        }

        this->mapObjects.push_back(mapLineObjects);
    }

    fin.close();
}

Map::~Map() {
    for (int i = 0; i < mapObjects.size(); i++) {
        for (int j = 0; j < mapObjects[i].size(); j++) {
            if (mapObjects[i][j] == nullptr) { continue; }
            mapObjects[i][j].~shared_ptr();
            mapObjects[i][j] = nullptr;
        }
    }

    knight = nullptr;
    princess = nullptr;
}

char Map::getSym(int x, int y) {
    return mapObjects[x][y]->getSym();
}

void Clear() {
    // Mac only
    system("clear");
}

void Map::printOut() {
    Clear();

    for (int i = 0; i < mapObjects.size(); i++) {
        for (int j = 0; j < mapObjects[i].size(); j++) {
            auto letter = mapObjects[i][j]->getSym();
            std::cout << letter;
        }
        std::cout << std::endl;
    }
}

float distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

bool Map::winOrLose() {
    auto knightPos = knight->getPos();
    auto princessPos = princess->getPos();

    if (distance(knightPos.first, knightPos.second, princessPos.first, princessPos.second) <= 1) {
        this->printWin();
        return true;
    }

    if (this->knight->getHp() <= 0) {
        this->printLose();
        return true;
    }

    return false;
}

void Map::printWin() {
    Clear();
    std::cout << "You saved the princess! Congratulations!";
    getchar();
}

void Map::printLose() {
    Clear();
    std::cout << "You died...";
    getchar();
}

void Map::destroyObject(int x, int y) {
    std::map<std::string, std::string> constants = readConfig();
    switch (mapObjects[x][y]->getSym()) {
        case 'Z':
            for (int i = 0; i < zombies.size(); i++) {
                if (zombies[i] == nullptr) { continue; }
                if (zombies[i]->getHp() == mapObjects[x][y]->getHp()) {
                    zombies[i] = nullptr;
                    break;
                }
            }
        case 'D':
            for (int i = 0; i < dragons.size(); i++) {
                if (dragons[i] == nullptr) { continue; }
                if (dragons[i]->getHp() == mapObjects[x][y]->getHp()) {
                    dragons[i] = nullptr;
                    break;
                }
            }
    }
    mapObjects[x][y].~shared_ptr();
    mapObjects[x][y] = std::make_shared<Floor>(x,y, constants["FLOOR_CHAR"]);
}

std::shared_ptr<GameObject> Map::getObjectAt(int x, int y) {
    return mapObjects[x][y];
}
