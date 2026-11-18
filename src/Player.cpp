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
        Vector2{static_cast<float>(x), static_cast<float>(y)}, WHITE);
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
        facingLeft ? static_cast<float>(x) - 16.0f
                   : static_cast<float>(x) + frameRec.width,
        static_cast<float>(y) + frameRec.height / 2
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

if(y + frameRec.height >= GetScreenHeight()){
	y = GetScreenHeight() - static_cast<int>(frameRec.height);
}
if(y <= 0){
	y = 0;
}
if (x + frameRec.width >= GetScreenWidth()){
	x = GetScreenWidth() - static_cast<int>(frameRec.width);
}
if (x <= 0){
	x = 0;
}
}

void Reset(){
        
}

Player::Player()
    : textureIdle(LoadTexture("Graphics/PlayerIdle.png")),
      textureWalk(LoadTexture("Graphics/PlayerWalk.png")),
        frameRec{0, 0, static_cast<float>(textureIdle.width) / 6, static_cast<float>(textureIdle.height)} {}

Player::~Player() {
    UnloadTexture(textureIdle);
    UnloadTexture(textureWalk);
}