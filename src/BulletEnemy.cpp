#include "Bullet.hpp"
#include "BulletEnemy.hpp"

BulletEnemy::BulletEnemy(Vector2 startPosition)
    : Bullet(startPosition, true) {
    speed = 7.0f;
}

void BulletEnemy::Update() {
    Bullet::Update();
}