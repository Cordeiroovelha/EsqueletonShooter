#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include "Bullet.hpp"

class BulletEnemy : public Bullet {
private:

public:
    void Update() override;
    explicit BulletEnemy(Vector2 startPosition);
    BulletEnemy(BulletEnemy&& other) noexcept = default;
    BulletEnemy& operator=(BulletEnemy&& other) noexcept = default;
    BulletEnemy(const BulletEnemy&) = delete;
    BulletEnemy& operator=(const BulletEnemy&) = delete;
    ~BulletEnemy() override = default;
};



#endif