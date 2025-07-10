#ifndef QT_PROGRAMMING_2025_MASTER_FIST_H
#define QT_PROGRAMMING_2025_MASTER_FIST_H

#include "Weapon.h"

class Fist : public Weapon {
public:
    explicit Fist(QGraphicsItem *parent = nullptr);
    
    // 实现Weapon的纯虚函数
    QString getWeaponType() const override;
    qreal getWeaponScale() const override;
    qreal getAttackDistance() const override;
    qreal getAttackOffsetY() const override;
    qreal getDefaultOffsetY() const override;
    int getDamage() const override;
    bool isVisibleByDefault() const override;
    void attack() override;
    
private:
    void loadWeaponPixmaps() override;
};

#endif //QT_PROGRAMMING_2025_MASTER_FIST_H 