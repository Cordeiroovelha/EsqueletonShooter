#include "Bullet.hpp"
#include <raylib.h>

Bullet::Bullet(Vector2 startPosition) : 
    position(startPosition) {}


void Bullet::Update(){
    position.x += speed;
    if(position.x > GetScreenWidth()){
        active = false;
    }
}

void Bullet::Draw(){
    if(active){
        DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 16, 6, YELLOW);
    }
}