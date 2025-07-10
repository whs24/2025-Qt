//
// Created by gerw on 8/20/24.
//

#include "Fist.h"
#include <QDebug>
#include "../Characters/Character.h"

Fist::Fist(QGraphicsItem *parent) : Weapon(parent) {
    // 加载拳头图片
    loadWeaponPixmaps();
}

QString Fist::getWeaponType() const {
    return "Fist";
}

qreal Fist::getWeaponScale() const {
    return 0.05; // 拳头缩小十倍
}

qreal Fist::getAttackDistance() const {
    return 4; // 拳头攻击距离更近
}

qreal Fist::getAttackOffsetY() const {
    return 5; // 拳头稍微向下
}

qreal Fist::getDefaultOffsetY() const {
    return 10; // 拳头在腰间的位置
}

int Fist::getDamage() const {
    return 5; // 拳头伤害为5
}

bool Fist::isVisibleByDefault() const {
    return false; // 拳头默认不可见
}

void Fist::loadWeaponPixmaps() {
    weaponPixmap = QPixmap(":/Items/weapons/fist.png");

    if (weaponPixmap.isNull()) {
        qDebug() << "fist: ERROR - weaponPixmap is null!";
        // 尝试从绝对路径加载
        weaponPixmap = QPixmap("assets/Items/weapons/fist.png");
    }
}

void Fist::attack() {
    qDebug() << "[DEBUG] Fist::attack called, owner:" << owner;
    // 拳头攻击时调用基类的startAttack
    if (owner) {
        startAttack(owner->getIsWalkingRight()); // 角色朝向决定攻击方向
    }
}

