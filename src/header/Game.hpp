#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <array>
#include <deque>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "BulletEnemy.hpp"

class Game {
private:
    std::deque<Enemy> enemies;
    std::deque<float> enemyHitRespawnTimers;
    std::deque<float> enemyShootTimers;
    std::vector<BulletEnemy> enemyBullets;
    float enemySpawnTimer{0.0f};
    double nextPlayerShotTime{0.0};
    Sound shootSound{};
    Sound deathSound{};
    Sound enemyDeathSound{};
    Music backgroundMusic{};
    bool audioReady{false};
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

    void EnemyColissionWhithWall();

    void CheckCollisionsWithEnemyBullets();

    void GameOver();

    Game();

    ~Game();
};

#endif