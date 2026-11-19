#ifndef ENEMY_HPP
#define ENEMY_HPP

/* Enemy Header:
   Header dedicated to the enemy (only one for now)
*/

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

    void Deactivate();

    Vector2 GenerateRandomPos();

    bool IsActive() const;
    
    void restart();

    Enemy();

    ~Enemy();

};


#endif