#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>
class Enemy {
private:
    Texture2D texture {};
    bool active{false};
    int frameCounter{0};
    int currentFrame{0};
    int frameSpeed{8};
public:
    Rectangle frameRec{};
    Vector2 position{};
    int speed{1};

    void Draw();

    void Update();

    void New();

    Vector2 GenerateRandomPos();

    bool IsActive() const;

    Enemy();

    ~Enemy();

};


#endif