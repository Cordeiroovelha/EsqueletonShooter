#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <array>
#include <deque>
#include "Player.hpp"
#include "Enemy.hpp"

class Game {
private:
    std::deque<Enemy> enemies;
    std::deque<float> enemyHitRespawnTimers;
    float enemySpawnTimer{0.0f};
public:
    Player player;

    bool running = true;
    bool left = false;
    bool GameRuning = false;
    int score = 0;

    void Draw();

    void Start();

    void Update();

    void CheckCollisionsWithEnemy();

    void CheckCollisionsWithWall();

    void CheckCollisionsWithBody();

    void EnemyColissionWhithBullet();

    void GameOver();

    Game();

    ~Game();
};

#endif