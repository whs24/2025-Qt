// SolidBall.h
#ifndef SOLIDBALL_H
#define SOLIDBALL_H

#include "Weapon.h"

class SolidBall : public Weapon {
    Q_OBJECT
public:
    explicit SolidBall(int throwCount = 3, QGraphicsItem *parent = nullptr);
    
    // 实现Weapon的纯虚函数
    QString getWeaponType() const override;
    qreal getWeaponScale() const override;
    qreal getAttackDistance() const override;
    qreal getAttackOffsetY() const override;
    qreal getDefaultOffsetY() const override;
    int getDamage() const override;
    bool isVisibleByDefault() const override;
    
    // 攻击方法（投掷实心球）
    void attack() override;
    
    int getRemainingThrows() const { return throwCount; }

private:
    void loadWeaponPixmaps() override;
    
private:
    int throwCount; // 剩余投掷次数
};

#endif // SOLIDBALL_H