#include <raylib.h>
#include <cstddef>
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

namespace { // SpawInterval
constexpr std::size_t initialEnemyLimit = 5;
constexpr float enemySpawnInterval = 3.0f;
constexpr float enemyHitRespawnInterval = 1.0f;
}

void Game::Draw(){
    player.Draw(left);
    player.DrawBullets();

    for (Enemy &enemy : enemies) {
        enemy.Draw();
    }
}

void Game::Start(){
    if (GameRuning) {
        return;
    }

    GameRuning = true;
    enemySpawnTimer = 0.0f;
    enemies[0].New();
}

void Game::Update(){
    if (!GameRuning) {
        return;
    }

    // Enemy Update
    const float frameTime = GetFrameTime();
    const std::size_t maxEnemiesOnScreen =
        initialEnemyLimit + static_cast<std::size_t>(score / 10);
    enemySpawnTimer += frameTime;
    if (enemySpawnTimer >= enemySpawnInterval) {
        for (std::size_t i = 0; i < maxEnemiesOnScreen; ++i) {
            if (!enemies[i].IsActive() && enemyHitRespawnTimers[i] <= 0.0f) {
                enemies[i].New();
                enemySpawnTimer = 0.0f;
                break;
            }
        }
    }

    for (std::size_t i = 0; i < enemies.size(); ++i) {
        if (enemyHitRespawnTimers[i] > 0.0f) {
            enemyHitRespawnTimers[i] -= frameTime;
            if (enemyHitRespawnTimers[i] <= 0.0f) {
                enemyHitRespawnTimers[i] = 0.0f;
                enemies[i].New();
            }
        }
        enemies[i].Update();
    }

    // Player Moviment
    bool moving = false;

    if(IsKeyPressed(KEY_Z)){
        player.Shoot(left);
    }

    player.UpdateBullets();
    EnemyColissionWhithBullet();

    if (IsKeyDown(KEY_UP)){
        GameRuning = true;
        player.position.y -= player.speed;
        player.Collision();
        running = true;
        moving = true;
    }
    if (IsKeyDown(KEY_DOWN)){
        GameRuning = true;
        player.position.y += player.speed;
        player.Collision();
        running = true;
        moving = true;
    }   
    if (IsKeyDown(KEY_LEFT)){
        GameRuning = true;
        player.position.x -= player.speed;
        player.Collision();
        running = true;
        moving = true;
        left = true;
    }
    if (IsKeyDown(KEY_RIGHT)){
        GameRuning = true;
        player.position.x += player.speed;
        player.Collision();
        running = true;
        moving = true;
        left = false;
    }

    player.position.x -= 3;
    player.Collision();
    player.Update(moving);
    CheckCollisionsWithEnemy();
}

void Game::CheckCollisionsWithEnemy(){
    for (std::size_t i = 0; i < enemies.size(); ++i) {
        Enemy &enemy = enemies[i];
        if (!enemy.IsActive()) {
            continue;
        }

        const Rectangle enemyBounds{
            enemy.position.x,
            enemy.position.y,
            enemy.frameRec.width,
            enemy.frameRec.height
        };

        const Rectangle playerBounds{
            player.position.x,
            player.position.y,
            player.frameRec.width,
            player.frameRec.height
        };

        if(CheckCollisionRecs(enemyBounds, playerBounds)){
            GameOver();
        }
    }
}

void Game::EnemyColissionWhithBullet() {
    for (std::size_t i = 0; i < enemies.size(); ++i) {
        Enemy &enemy = enemies[i];
        if (!enemy.IsActive()) {
            continue;
        }

        const Rectangle enemyBounds{
            enemy.position.x,
            enemy.position.y,
            enemy.frameRec.width,
            enemy.frameRec.height
        };

        for (Bullet &bullet : player.bullets) {
            if (!bullet.active) {
                continue;
            }

            const Rectangle bulletBounds{
                bullet.position.x,
                bullet.position.y,
                bullet.frameRec.width,
                bullet.frameRec.height
            };

            if (CheckCollisionRecs(bulletBounds, enemyBounds)) {
                bullet.active = false;
                score += 1;
                const std::size_t maxEnemyCount =
                    initialEnemyLimit + static_cast<std::size_t>(score / 10);
                if (score % 10 == 0 && enemies.size() < maxEnemyCount) {
                    enemies.emplace_back();
                    enemyHitRespawnTimers.push_back(0.0f);
                }
                enemy.Deactivate();
                enemyHitRespawnTimers[i] = enemyHitRespawnInterval;
                break;
            }
        }
    }
}

void Game::GameOver(){
    score = 0;
    GameRuning = false;
    enemySpawnTimer = 0.0f;

    for (std::size_t i = 0; i < enemies.size(); ++i) {
        enemies[i].restart();
        enemyHitRespawnTimers[i] = 0.0f;
    }

    player.Reset();
}

Game::Game()
    : enemies(initialEnemyLimit),
      enemyHitRespawnTimers(initialEnemyLimit, 0.0f) {}

Game::~Game()
{
    // UnloadSound(eatSound);
    // UnloadSound(wallSound);
    // CloseAudioDevice();
}