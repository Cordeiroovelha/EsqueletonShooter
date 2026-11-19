#include <raylib.h>
#include <algorithm>
#include "Bullet.hpp"
#include "Player.hpp"

void Player::Draw(bool facingLeft){
    const Texture2D &texture = isMoving ? textureWalk : textureIdle;
    Rectangle source = frameRec;
    if(facingLeft){
        source.x += source.width;
        source.width = -source.width;
    }

    DrawTextureRec(texture, source,
        Vector2{static_cast<float>(position.x), static_cast<float>(position.y)}, WHITE);
}

void Player::Update(bool moving){
    if(isMoving != moving){
        isMoving = moving;
        currentFrame = 0;
        frameCounter = 0;
        frameRec.x = 0;
    }

    frameCounter++;

    if(frameCounter >= (60/frameSpeed)){
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % 6;

        frameRec.x = static_cast<float>(currentFrame) * frameRec.width;
    }
}

void Player::Shoot(bool facingLeft){
    bullets.emplace_back(Vector2{
        facingLeft ? static_cast<float>(position.x) - 16.0f
                   : static_cast<float>(position.x) + frameRec.width,
        static_cast<float>(position.y) + frameRec.height / 2
    }, facingLeft);
}

void Player::UpdateBullets(){
    for(Bullet &bullet : bullets){
        bullet.Update();
    }

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet &bullet){ return !bullet.active; }),
        bullets.end()
    );
}

void Player::DrawBullets(){
    for(Bullet &bullet : bullets){
        bullet.Draw();
    }
}

void Player::Collision(){

if(position.y + frameRec.height >= GetScreenHeight()){
	position.y = GetScreenHeight() - static_cast<int>(frameRec.height);
}
if(position.y <= 0){
	position.y = 0;
}
if (position.x + frameRec.width >= GetScreenWidth()){
	position.x = GetScreenWidth() - static_cast<int>(frameRec.width);
}
if (position.x <= 0){
	position.x = 0;
}
}

void Player::Reset(){
    position = {static_cast<float>(GetScreenWidth()) / 2 - 400, static_cast<float>(GetScreenHeight()) / 2};
    bullets.clear();
}

Player::Player()
    : textureIdle(LoadTexture("Graphics/PlayerIdle.png")),
      textureWalk(LoadTexture("Graphics/PlayerWalk.png")),
        frameRec{0, 0, static_cast<float>(textureIdle.width) / 6, static_cast<float>(textureIdle.height)} {}

Player::~Player() {
    UnloadTexture(textureIdle);
    UnloadTexture(textureWalk);
}