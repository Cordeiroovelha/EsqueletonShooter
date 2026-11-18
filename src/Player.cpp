#include <raylib.h>
#include <algorithm>
#include "Bullet.hpp"
#include "Player.hpp"

void Player::Draw(){
    DrawTextureRec(texture, frameRec,
        Vector2{static_cast<float>(x), static_cast<float>(y)}, WHITE);
}

void Player::Update(){
    frameCounter++;

    if(frameCounter >= (60/frameSpeed)){
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % 6;

        frameRec.x = static_cast<float>(currentFrame) * frameRec.width;
    }
}

void Player::Shoot(){
    bullets.emplace_back(Vector2{
        static_cast<float>(x) + frameRec.width,
        static_cast<float>(y) + frameRec.height / 2
    });
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
    : texture(LoadTexture("Graphics/Player_idle.png")),
        frameRec{0, 0, static_cast<float>(texture.width) / 6, static_cast<float>(texture.height)} {}

Player::~Player() { UnloadTexture(texture); }