#include <raylib.h>
#include "Game.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

namespace {
constexpr float enemySpawnInterval = 1.0f;
}

void Game::Draw(){
    player.Draw(left);
    player.DrawBullets();

    for (Enemy &enemy : enemies) {
        enemy.Draw();
    }
}

void Game::Update(){
    enemySpawnTimer += GetFrameTime();
    if (enemySpawnTimer >= enemySpawnInterval) {
        for (Enemy &enemy : enemies) {
            if (!enemy.IsActive()) {
                enemy.New();
                enemySpawnTimer = 0.0f;
                break;
            }
        }
    }

    for (Enemy &enemy : enemies) {
        enemy.Update();
    }

    bool moving = false;

    if(IsKeyPressed(KEY_Z)){
        player.Shoot(left);
    }

    player.UpdateBullets();

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

    player.Update(moving);
}

void Game::CheckCollisionsWithEnemy(){
        
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