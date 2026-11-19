#include <raylib.h>
#include "Enemy.hpp"
#include "Bullet.hpp"

// Vector2{static_cast<float>(GetRandomValue(0, GetScreenHeight())), 
//             static_cast<float>(GetScreenWidth()) + 10}, WHITE);

void Enemy::Draw(){
    const Texture2D &textureEnemy = texture;
    Rectangle source = frameRec;

    if (active) {
        DrawTextureRec(textureEnemy, source, position, WHITE);
    }
}

void Enemy::Update(){
    if (!active) {
        return;
    }

    // Walk to the left
    position.x -= speed;
    frameCounter++;
    if (frameCounter >= 60 / frameSpeed) {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % 4;
        frameRec.x = static_cast<float>(currentFrame) * frameRec.width;
    }

    if (position.x + frameRec.width < 0) {
        active = false;
    }
}
// new Enemy
void Enemy::New(){
    position = GenerateRandomPos();
    frameCounter = 0;
    currentFrame = 0;
    frameRec.x = 0;
    active = true;
}

void Enemy::Deactivate(){
    active = false;
}

Vector2 Enemy::GenerateRandomPos(){
    const int maxY = GetScreenHeight() > static_cast<int>(frameRec.height)
        ? GetScreenHeight() - static_cast<int>(frameRec.height)
        : 0;
    const float y = static_cast<float>(GetRandomValue(0, maxY));
    return Vector2{static_cast<float>(GetScreenWidth() + 10), y};
}

bool Enemy::IsActive() const{
    return active;
}

Enemy::Enemy() : texture(LoadTexture("Graphics/Enemy.png")),
        frameRec{0, 0, static_cast<float>(texture.width) / 4, static_cast<float>(texture.height)} {}

Enemy::~Enemy(){
    UnloadTexture(texture);
}