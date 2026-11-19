#ifndef PLAYER_H
#define PLAYER_H

/* Player Header:
   Header dedicated to the player
*/

#include <raylib.h>
#include "Bullet.hpp"
#include <vector>

class Player {
private:
    Texture2D textureIdle{};
    Texture2D textureWalk{};
    bool isMoving{false};
public:
    int x{GetScreenWidth() / 2};
    int y{GetScreenHeight() / 2};
    int speed{6};
    Rectangle frameRec{};
    int frameSpeed{4}, frameCounter{0}, currentFrame{0};
    std::vector<Bullet> bullets;

    void Draw(bool facingLeft);

    void Update(bool moving);

    void Shoot(bool facingLeft);

    void UpdateBullets();

    void DrawBullets();

    void Collision();

    void Reset();

    Player();

    ~Player();
};

#endif