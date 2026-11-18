#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "Bullet.hpp"
#include <vector>

class Player {
private:
    Texture2D texture{};
public:
    int x{GetScreenWidth() / 2};
    int y{GetScreenHeight() / 2};
    int speed{6};
    Rectangle frameRec{};
    int frameSpeed{3}, frameCounter{0}, currentFrame{0};
    std::vector<Bullet> bullets;

    void Draw();

    void Update();

    void Shoot();

    void UpdateBullets();

    void DrawBullets();

    void Collision();

    void Reset();

    Player();

    ~Player();
};

#endif