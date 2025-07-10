//
// Created by gerw on 8/20/24.
//

#include "Sword.h"
#include <QDebug>
#include "../Characters/Character.h"


Sword::Sword(QGraphicsItem *parent) : Weapon(parent) {
    // 加载剑图片
    loadWeaponPixmaps();
}

QString Sword::getWeaponType() const {
    return "Sword";
}

qreal Sword::getWeaponScale() const {
    return 1.0; // 剑放大一倍
}

qreal Sword::getAttackDistance() const {
    return 3; // 剑攻击距离适中
}

qreal Sword::getAttackOffsetY() const {
    return 0; // 剑水平位置
}

qreal Sword::getDefaultOffsetY() const {
    return 40; // 剑在腰间的位置
}


int Sword::getDamage() const {
    return 10; // 剑伤害为10
}

bool Sword::isVisibleByDefault() const {
    return true; // 剑默认可见
}

void Sword::loadWeaponPixmaps() {
    weaponPixmap = QPixmap(":/Items/weapons/sword.png");
    
    if (weaponPixmap.isNull()) {
        qDebug() << "Sword: ERROR - weaponPixmap is null!";
        // 尝试从绝对路径加载
        weaponPixmap = QPixmap("assets/Items/weapons/sword.png");
    }
}

void Sword::attack() {
    qDebug() << "[DEBUG] Sword::attack called, owner:" << owner;
    // 剑攻击时调用基类的startAttack
    if (owner) {
        startAttack(owner->getIsWalkingRight()); // 角色朝向决定攻击方向
    }
}

QRectF Sword::boundingRect() const {
    if (weaponPixmap.isNull()) return QRectF(0, 0, 0, 0);
    qreal scale = getWeaponScale();
    qreal width = weaponPixmap.width() * scale;
    qreal height = weaponPixmap.height() * scale;
    if (attacking) {
        // 以中心为基准旋转90°，宽高互换，中心不变
        qreal cx = width / 2;
        qreal cy = height / 2;
        // 旋转后左上角坐标
        qreal newW = height;
        qreal newH = width;
        qreal newX = cx - newW / 2;
        qreal newY = cy - newH / 2;
        return QRectF(newX, newY, newW, newH);
    } else {
        return QRectF(0, 0, width, height);
    }
}

