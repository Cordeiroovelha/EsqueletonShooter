#include <raylib.h>
#include "Bullet.hpp"

Bullet::Bullet(Vector2 startPosition, bool movingLeft)
    : Texture(LoadTexture("Graphics/Bullet.png")),
      frameRec{0, 0, static_cast<float>(Texture.width),
               static_cast<float>(Texture.height)},
      position(startPosition),
      movingLeft(movingLeft) {}

Bullet::Bullet(Bullet&& other) noexcept
    : Texture(other.Texture),
      frameRec(other.frameRec),
      position(other.position),
      speed(other.speed),
      active(other.active),
      movingLeft(other.movingLeft) {
    other.Texture = {0};
}

Bullet& Bullet::operator=(Bullet&& other) noexcept {
    if (this != &other) {
        UnloadTexture(Texture);
        Texture = other.Texture;
        frameRec = other.frameRec;
        position = other.position;
        speed = other.speed;
        active = other.active;
        movingLeft = other.movingLeft;
        other.Texture = {0};
    }
    return *this;
}


void Bullet::Update(){
    position.x += movingLeft ? -speed : speed;
    if(position.x > GetScreenWidth() || position.x + 16 < 0){
        active = false;
    }
}

void Bullet::Draw(){
    const Texture2D &texture = Texture;
    Rectangle source = frameRec;

    if(active){
        DrawTextureRec(texture, source, position, WHITE);
        // DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 16, 6, YELLOW);
    }
}

Bullet::~Bullet(){
    if(Texture.id != 0){
        UnloadTexture(Texture);
    }
}