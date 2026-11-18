#include "Bullet.hpp"
#include <raylib.h>

Bullet::Bullet(Vector2 startPosition, bool movingLeft)
    : position(startPosition), movingLeft(movingLeft) {}


void Bullet::Update(){
    position.x += movingLeft ? -speed : speed;
    if(position.x > GetScreenWidth() || position.x + 16 < 0){
        active = false;
    }
}

void Bullet::Draw(){
    if(active){
        DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 16, 6, YELLOW);
    }
}