#ifndef BULLET_H
#define BULLET_H

/* Wepom Header:
   Header dedicated to the Wepom (there is only the gun)
*/

#include <raylib.h>

class Bullet {
public:
    Texture2D Texture;
    Rectangle frameRec{};
    int frameSpeed{4}, frameCounter{0}, currentFrame{0};
    Vector2 position;
    float speed{12};
    bool active{true};
    bool movingLeft{false};

    Bullet(Vector2 startPosition, bool movingLeft);
    Bullet(const Bullet&) = delete;
    Bullet& operator=(const Bullet&) = delete;
    Bullet(Bullet&& other) noexcept;
    Bullet& operator=(Bullet&& other) noexcept;

    virtual void Update();

    void Draw();

    virtual ~Bullet();
};

#endif