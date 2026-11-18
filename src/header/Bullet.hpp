#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>

class Bullet {
public:
    Vector2 position;
    float speed{12};
    bool active{true};
    bool movingLeft{false};

    Bullet(Vector2 startPosition, bool movingLeft);

    void Update();

    void Draw();

};

#endif