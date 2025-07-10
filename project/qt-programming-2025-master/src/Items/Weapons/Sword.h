//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_SWORD_H
#define QT_PROGRAMMING_2024_SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
    Q_OBJECT

public:
    explicit Sword(QGraphicsItem *parent = nullptr);
    
    // 实现Weapon的纯虚函数
    QString getWeaponType() const override;
    qreal getWeaponScale() const override;
    qreal getAttackDistance() const override;
    qreal getAttackOffsetY() const override;
    qreal getDefaultOffsetY() const override;
    int getDamage() const override;
    bool isVisibleByDefault() const override;
    void attack() override;
    QRectF boundingRect() const override;

    // QRectF boundingRect() const override {
    //     qreal scale = getWeaponScale();
    //     if (!weaponPixmap.isNull()) {
    //         if (attacking) {
    //             // 攻击时旋转90度，宽高互换
    //             if (facingRight) {
    //                 return QRectF(0, 0, weaponPixmap.height() * scale, weaponPixmap.width() * scale);
    //             } else {
    //                 return QRectF(-weaponPixmap.height() * scale, 0, weaponPixmap.height() * scale, weaponPixmap.width() * scale);
    //             }
    //         } else {
    //             return QRectF(0, 0, weaponPixmap.width() * scale, weaponPixmap.height() * scale);
    //         }
    //     }
    //     return QRectF(0, 0, 40, 40);
    // }

private:
    void loadWeaponPixmaps() override;
};

#endif //QT_PROGRAMMING_2024_SWORD_H 