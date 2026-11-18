#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>

class Bullet {
public:
    Vector2 position;
    float speed{12};
    bool active{true};

    Bullet(Vector2 startPosition);

    void Update();

    void Draw();

};

#endif