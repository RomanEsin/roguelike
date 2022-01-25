//
//  Game.cpp
//  roguelike
//
//  Created by Роман Есин on 20.01.2022.
//

#include <stdlib.h>
#include <ctime>
#include <iostream>
//#include <ncurses.h>

#include "Game.hpp"
#include "Map.hpp"

using namespace::std;

std::pair<int, int> randomDir() {
    int rand_dir = 1 + rand() % 4; // 1 - UP 2- DOWN 3- LEFT 4-RIGHT
    int dx, dy;
    switch (rand_dir) {
        case 1:
            dx = -1;
            dy = 0;
            break;
        case 2:
            dx = 1;
            dy = 0;
            break;
        case 3:
            dx = 0;
            dy = -1;
            break;
        case 4:
            dx = 0;
            dy = 1;
            break;
    }
    return std::pair<int, int>(dx, dy);
}

void Game::start() {
    Map currentMap = Map();
//    initscr();
//    resize_term(40,112);
//    keypad(stdscr, TRUE);
//    nodelay(stdscr, true);
//    refresh();
//    curs_set(0);
//    clear();
//    noecho();
    currentMap.printOut();

    continueGame(currentMap);
}

void projectileThing(Map map,
                     std::pair<int, int> direction,
                     std::pair<int, int> nextKnightPos,
                     long long &tProjectile,
                     long long &knightAction) {

    auto newProjectile = std::make_shared<Projectile>(nextKnightPos.first, nextKnightPos.second, std::pair<int, int>{ 0, 0 });
    newProjectile->direction = direction;
    newProjectile->fly();
    
    map.projectiles.push_back(newProjectile);

    auto collisionObject = map.getObjectAt(newProjectile->x, newProjectile->y);
    unsigned long lastProjectileIndex = map.projectiles.size() - 1;

    GameResult flag = newProjectile->collide(&*collisionObject);

    if (flag == CanAttack) {
        collisionObject->hit(newProjectile->damage);
        map.projectiles[lastProjectileIndex] = nullptr;
    } else if (flag == CanMove) {
        map.mapObjects[newProjectile->x][newProjectile->y].~shared_ptr();
        map.mapObjects[newProjectile->x][newProjectile->y] = newProjectile;
    } else {
        map.projectiles[lastProjectileIndex] = nullptr;
    }

    tProjectile = clock();
    knightAction = clock();
}

void Game::continueGame(Map map) {
    long long knightAction = clock();
    long long t = clock();
    long long tDragon = clock();
    long long tProjectile = clock();
    // Action duration
    // For using curses
//    long long oneAction = 200;

    while (true) {
//        if ((clock() - tProjectile) >= (oneAction) * 0.5) {
            // Run through all projectiles
            for (int i = 0; i < map.projectiles.size(); i++) {
                if (map.projectiles[i] != nullptr) {
                    auto currentProjectile = map.projectiles[i];
                    int projectileX = currentProjectile->x;
                    int projectileY = currentProjectile->y;

                    std::pair<int, int> collisionObjectPost(projectileX + currentProjectile->direction.first,
                                                      projectileY + currentProjectile->direction.second);

                    auto collisionObject = map.getObjectAt(collisionObjectPost.first, collisionObjectPost.second);

                    GameResult flag = currentProjectile->collide(&*collisionObject);

                    switch (flag) {
                        case CanMove:
                            map.mapObjects[projectileX][projectileY].swap(map.mapObjects[collisionObjectPost.first][collisionObjectPost.second]);
                            currentProjectile->fly();
                            break;
                        case Destroy:
                            map.destroyObject(projectileX, projectileY);
                            map.projectiles[i] = nullptr;
                            break;
                        case CanAttack:
                            collisionObject->hit(currentProjectile->damage);

                            if (collisionObject->getHp() <= 0) {
                                map.destroyObject(collisionObjectPost.first, collisionObjectPost.second);
                            }

                            map.destroyObject(projectileX, projectileY);
                            map.projectiles[i] = nullptr;
                            break;
                        default:
                            break;
                    }
                }
            }
            // Reset projectile randomizer
            tProjectile = clock();
//        }

//        if ((clock() - t) >= (oneAction) * 1.5) {
            for (int i = 0; i < map.zombies.size(); i++) {
                if (map.zombies[i] != nullptr) {
                    auto delta = randomDir();
                    auto zombie = map.zombies[i];
                    auto zombiePos = zombie->getPos();

                    std::pair<int, int> collisionPos(zombiePos.first + delta.first, zombiePos.second + delta.second);
                    auto collisionObject = map.getObjectAt(collisionPos.first, collisionPos.second);

                    GameResult flag = zombie->Collide(&*collisionObject);

                    switch (flag) {
                        case CanMove:
                            map.mapObjects[zombiePos.first][zombiePos.second].swap(map.mapObjects[collisionPos.first][collisionPos.second]);
                            map.zombies[i]->move(collisionPos.first, collisionPos.second);
                            break;
                        case CanAttack:
                            collisionObject->hit(map.zombies[i]->getDamage());
                            break;
                        default:
                            break;
                    }
                }
            }
            t = clock();
//        }

//        if ((clock() - tDragon) >= (oneAction) * 3) {
            for (int i = 0; i < map.dragons.size(); i++) {
                if (map.dragons[i] != nullptr) {
                    auto delta = randomDir();
                    auto dragon = map.dragons[i];
                    auto dragonPos = dragon->getPos();

                    std::pair<int, int> collisionObjectPos(dragonPos.first + delta.first, dragonPos.second + delta.second);
                    auto collisionObject = map.getObjectAt(collisionObjectPos.first, collisionObjectPos.second);

                    GameResult flag = dragon->Collide(&*collisionObject);

                    switch (flag) {
                        case CanMove:
                        {
                            map.mapObjects[dragonPos.first][dragonPos.second].swap(map.mapObjects[collisionObjectPos.first][collisionObjectPos.second]);
                            dragon->move(collisionObjectPos.first, collisionObjectPos.second);

                            auto newProjectile = std::make_shared<Projectile>(collisionObjectPos.first,
                                                                              collisionObjectPos.second,
                                                                              std::pair<int, int>{ 0, 0 });

                            map.projectiles.push_back(newProjectile);
                            unsigned long lastProjectileIndex = map.projectiles.size() - 1;

                            newProjectile->direction = delta;
                            newProjectile->fly();

                            auto collisionObject = map.getObjectAt(newProjectile->x, newProjectile->y);

                            flag = newProjectile->collide(&*collisionObject);
                            if (flag == CanAttack) {
                                collisionObject->hit(newProjectile->damage);
                                map.projectiles[lastProjectileIndex] = nullptr;
                            } else if (flag == CanMove) {
                                map.mapObjects[newProjectile->x][newProjectile->y].~shared_ptr();
                                map.mapObjects[newProjectile->x][newProjectile->y] = newProjectile;
                            } else {
                                map.projectiles[lastProjectileIndex] = nullptr;
                            }
                        }
                            break;
                        case CanAttack:
                            collisionObject->hit(dragon->getDamage());
                            break;
                        default:
                            break;
                    }
                }

            }
            tDragon = clock();
//        }

//        char userInput = getch();
        char userInput;
        std::cin >> userInput;

        if (userInput != ' ') {
//            if ((clock() - knightAction) >= (oneAction * 1)) {
                std::pair<int, int> nextKnightPos = map.knight->try_move(userInput);
                std::pair<int, int> direction;

                switch (userInput) {
                    case '\x3':
                        direction = { -1, 0 };
                        projectileThing(map, direction, nextKnightPos, tProjectile, knightAction);
                        break;
                    case '\x2':
                        direction = { 1, 0 };
                        projectileThing(map, direction, nextKnightPos, tProjectile, knightAction);
                        break;
                    case '\x4':
                        direction = { 0, -1 };
                        projectileThing(map, direction, nextKnightPos, tProjectile, knightAction);
                        break;
                    case '\x5':
                        direction = { 0, 1 };
                        projectileThing(map, direction, nextKnightPos, tProjectile, knightAction);
                        break;
                    default:
                        auto collisionObject = map.getObjectAt(nextKnightPos.first, nextKnightPos.second);
                        GameResult flag = map.knight->collide(&*collisionObject);
                        auto knightPos = map.knight->getPos();
                        switch (flag) {
                            case CanMove:
                                map.mapObjects[knightPos.first][knightPos.second].swap(map.mapObjects[nextKnightPos.first][nextKnightPos.second]);
                                map.knight->move(nextKnightPos.first, nextKnightPos.second);
                                knightAction = clock();
                                break;
                            case AidHP:
                                map.destroyObject(nextKnightPos.first, nextKnightPos.second);
                                map.mapObjects[knightPos.first][knightPos.second].swap(map.mapObjects[nextKnightPos.first][nextKnightPos.second]);
                                map.knight->move(nextKnightPos.first, nextKnightPos.second);
                                map.knight->Regeneration();
                                knightAction = clock();
                                break;
                            case CanAttack:
                                collisionObject->hit(map.knight->getDamage());
                                if (collisionObject->getHp() <= 0) {
                                    map.destroyObject(nextKnightPos.first, nextKnightPos.second);
                                }
                                knightAction = clock();
                                break;
                            default:
                                break;
                        }
                        break;
                }
//            }
        }

        map.printOut();

        if (map.winOrLose()) {
            break;
        }
    }
}
