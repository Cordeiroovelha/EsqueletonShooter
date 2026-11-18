#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <array>
#include "Player.hpp"
#include "Enemy.hpp"

class Game {
private:
    std::array<Enemy, 5> enemies;
    float enemySpawnTimer{0.0f};
public:
    Player player;

    bool running = true;
    bool left = false;
    int score = 0;

    void Draw();

    void Update();

    void CheckCollisionsWithEnemy();

    void CheckCollisionsWithWall();

    void CheckCollisionsWithBody();

    void GameOver();

    Game();

    ~Game();
};

#endif