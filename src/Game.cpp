#include <raylib.h>
#include <algorithm>
#include <cstddef>
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "BulletEnemy.hpp"

namespace { // SpawInterval
constexpr std::size_t initialEnemyLimit = 5;
constexpr float enemySpawnInterval = 3.0f;
constexpr float enemyHitRespawnInterval = 1.0f;
constexpr double playerShotCooldown = 0.25;

float RandomEnemyShotInterval() {
    return static_cast<float>(GetRandomValue(2000, 4000)) / 1000.0f;
}
}

void Game::Draw(){
    player.Draw(left);
    player.DrawBullets();

    for (BulletEnemy &bullet : enemyBullets) {
        bullet.Draw();
    }

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
    nextPlayerShotTime = 0.0;
    enemyShootTimers[0] = RandomEnemyShotInterval();
    enemies[0].New();

    if (IsMusicValid(backgroundMusic)) {
        SeekMusicStream(backgroundMusic, 0.0f);
        PlayMusicStream(backgroundMusic);
    }
}

void Game::Update(){
    if (!GameRuning) {
        return;
    }

    // Enemy Update
    const float frameTime = GetFrameTime();
    if (IsMusicValid(backgroundMusic)) {
        UpdateMusicStream(backgroundMusic);
    }

    const std::size_t maxEnemiesOnScreen =
        initialEnemyLimit + static_cast<std::size_t>(score / 10);
    enemySpawnTimer += frameTime;
    if (enemySpawnTimer >= enemySpawnInterval) {
        for (std::size_t i = 0; i < maxEnemiesOnScreen; ++i) {
            if (!enemies[i].IsActive() && enemyHitRespawnTimers[i] <= 0.0f) {
                enemies[i].New();
                enemyShootTimers[i] = RandomEnemyShotInterval();
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
                enemyShootTimers[i] = RandomEnemyShotInterval();
            }
        }
        enemies[i].Update();

        if (enemies[i].IsActive()) {
            enemyShootTimers[i] -= frameTime;
            if (enemyShootTimers[i] <= 0.0f) {
                const Enemy &enemy = enemies[i];
                enemyBullets.emplace_back(Vector2{
                    enemy.position.x,
                    enemy.position.y + enemy.frameRec.height / 2.0f
                });
                enemyShootTimers[i] = RandomEnemyShotInterval();
            }
        }
    }

    for (BulletEnemy &bullet : enemyBullets) {
        bullet.Update();
    }
    enemyBullets.erase(
        std::remove_if(enemyBullets.begin(), enemyBullets.end(),
            [](const BulletEnemy &bullet) { return !bullet.active; }),
        enemyBullets.end()
    );

    // Player Moviment
    bool moving = false;

    const double currentTime = GetTime();
    if (IsKeyPressed(KEY_Z) && currentTime >= nextPlayerShotTime) {
        if (IsSoundValid(shootSound)) {
            PlaySound(shootSound);
        }
        player.Shoot(left);
        nextPlayerShotTime = currentTime + playerShotCooldown;
    }

    player.UpdateBullets();
    EnemyColissionWhithBullet();
    EnemyColissionWhithWall();

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
    CheckCollisionsWithEnemyBullets();
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
                    enemyShootTimers.push_back(0.0f);
                }
                if (IsSoundValid(enemyDeathSound)) {
                    PlaySound(enemyDeathSound);
                }
                enemy.Deactivate();
                enemyHitRespawnTimers[i] = enemyHitRespawnInterval;
                break;
            }
        }
    }
}

void Game::EnemyColissionWhithWall(){
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

        if(enemyBounds.x + enemyBounds.width / 2 <= 0){
            GameOver();
        }
    }
}

void Game::CheckCollisionsWithEnemyBullets() {
    const Rectangle playerBounds{
        player.position.x,
        player.position.y,
        player.frameRec.width,
        player.frameRec.height
    };

    for (const BulletEnemy &bullet : enemyBullets) {
        if (!bullet.active) {
            continue;
        }

        const Rectangle bulletBounds{
            bullet.position.x,
            bullet.position.y,
            bullet.frameRec.width,
            bullet.frameRec.height
        };

        if (CheckCollisionRecs(bulletBounds, playerBounds)) {
            GameOver();
            return;
        }
    }
}

void Game::GameOver(){
    score = 0;
    GameRuning = false;
    enemySpawnTimer = 0.0f;
    enemyBullets.clear();
    if (IsMusicValid(backgroundMusic)) {
        StopMusicStream(backgroundMusic);
    }

    for (std::size_t i = 0; i < enemies.size(); ++i) {
        enemies[i].restart();
        enemyHitRespawnTimers[i] = 0.0f;
        enemyShootTimers[i] = 0.0f;
    }

    if (IsSoundValid(deathSound)) {
        PlaySound(deathSound);
    }
    player.Reset();
}

Game::Game()
    : enemies(initialEnemyLimit),
      enemyHitRespawnTimers(initialEnemyLimit, 0.0f),
      enemyShootTimers(initialEnemyLimit, 0.0f) {
    InitAudioDevice();
    audioReady = IsAudioDeviceReady();
    if (!audioReady) {
        TraceLog(LOG_WARNING, "Audio device could not be initialized");
        return;
    }

    deathSound = LoadSound("Graphics/Sound/PlayerDeath.ogg");
    enemyDeathSound = LoadSound("Graphics/Sound/EnemyDeath.ogg");
    shootSound = LoadSound("Graphics/Sound/buster_shot.ogg");
    backgroundMusic = LoadMusicStream("Graphics/Sound/BackGroundSound.mp3");
    
    if (!IsMusicValid(backgroundMusic)) {
        TraceLog(LOG_WARNING, "Failed to load background music");
    } else {
        backgroundMusic.looping = true;
    }
}

Game::~Game()
{
    if (!audioReady) {
        return;
    }

    if (IsSoundValid(deathSound)) {
        UnloadSound(deathSound);
    }
    if (IsSoundValid(enemyDeathSound)) {
        UnloadSound(enemyDeathSound);
    }
    if (IsSoundValid(shootSound)) {
        UnloadSound(shootSound);
    }
    if (IsMusicValid(backgroundMusic)) {
        UnloadMusicStream(backgroundMusic);
    }
    CloseAudioDevice();
}