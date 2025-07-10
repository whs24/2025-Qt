#ifndef GUN_H
#define GUN_H

#include "Weapon.h"
#include <QTimer>

class Gun : public Weapon {
    Q_OBJECT
public:
    explicit Gun(int bulletCount, int intervalMs, QGraphicsItem* parent = nullptr);
    int getRemainingBullets() const { return bullets; }
    int getMaxBullets() const { return maxBullets; }
    bool canShoot() const { return !coolingDown && bullets > 0; }
    void setOwner(Character* owner);

    // 远程武器通用接口
    virtual void shoot(bool facingRight) = 0;

protected:
    int bullets;
    int maxBullets;
    int intervalMs; // 射击间隔（毫秒）
    bool coolingDown = false;
    QTimer* intervalTimer = nullptr;

    void startCooldown();

protected slots:
    void onCooldownFinished();
};

#endif // GUN_H 