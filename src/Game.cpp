#include <raylib.h>
#include <cstddef>
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

namespace { // SpawInterval
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

void Game::Update(){
    // Enemy Update
    const float frameTime = GetFrameTime();
    enemySpawnTimer += frameTime;
    if (enemySpawnTimer >= enemySpawnInterval) {
        for (std::size_t i = 0; i < enemies.size(); ++i) {
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
        player.y -= player.speed;
        player.Collision();
        running = true;
        moving = true;
    }
    if (IsKeyDown(KEY_DOWN)){
        player.y += player.speed;
        player.Collision();
        running = true;
        moving = true;
    }   
    if (IsKeyDown(KEY_LEFT)){
        player.x -= player.speed;
        player.Collision();
        running = true;
        moving = true;
        left = true;
    }
    if (IsKeyDown(KEY_RIGHT)){
        player.x += player.speed;
        player.Collision();
        running = true;
        moving = true;
        left = false;
    }

    player.x -= 3;
    player.Collision();
    player.Update(moving);
}

void Game::CheckCollisionsWithEnemy(){
        
}

void Game::EnemyColissionWhithBullet(){
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
                enemy.Deactivate();
                enemyHitRespawnTimers[i] = enemyHitRespawnInterval;
                break;
            }
        }
    }
}

void Game::CheckCollisionsWithWall(){
        
}

void Game::CheckCollisionsWithBody(){
        
}

void Game::GameOver(){
        
}

Game::Game() {
    enemies[0].New();
}

Game::~Game()
{
    // UnloadSound(eatSound);
    // UnloadSound(wallSound);
    // CloseAudioDevice();
}