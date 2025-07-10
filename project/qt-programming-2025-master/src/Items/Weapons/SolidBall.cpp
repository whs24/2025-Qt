// SolidBall.cpp
#include "SolidBall.h"
#include "SolidBallProjectile.h"
#include "../Characters/Character.h"
#include <QDebug>
#include <QGraphicsScene>

SolidBall::SolidBall(int throwCount, QGraphicsItem *parent)
    : Weapon(parent), throwCount(throwCount) {
    loadWeaponPixmaps();
}

QString SolidBall::getWeaponType() const {
    return "SolidBall";
}

qreal SolidBall::getWeaponScale() const {
    return 0.3; // 实心球武器较小
}

qreal SolidBall::getAttackDistance() const {
    return 0; // 不使用近战攻击距离
}

qreal SolidBall::getAttackOffsetY() const {
    return 5; // 攻击时垂直偏移
}

qreal SolidBall::getDefaultOffsetY() const {
    return 50; // 默认在腰间位置
}

int SolidBall::getDamage() const {
    return 15; // 实心球伤害值
}

bool SolidBall::isVisibleByDefault() const {
    return true; // 默认可见
}

void SolidBall::loadWeaponPixmaps() {
    weaponPixmap = QPixmap(":/Items/weapons/weight.png");
    if (weaponPixmap.isNull()) {
        qDebug() << "SolidBall: ERROR - weaponPixmap is null!";
        weaponPixmap = QPixmap(":/Items/weapons/weight.png");
    }
}

void SolidBall::attack() {
    qDebug() << "[DEBUG] SolidBall::attack called, throwCount:" << throwCount << "owner:" << owner << "scene:" << scene();
    if (throwCount <= 0 || !owner || !scene()) {
        qDebug() << "[DEBUG] SolidBall::attack aborted: throwCount <= 0 or owner/scene is nullptr";
        return;
    }
    
    // 计算投掷起始位置（在角色前方）
    QPointF startPos = owner->pos() + 
                      QPointF(facingRight ? owner->boundingRect().width() : -20, 
                              getAttackOffsetY());
    qDebug() << "[DEBUG] SolidBall::attack startPos:" << startPos << "facingRight:" << facingRight;
    
    // 创建子弹
    SolidBallProjectile* projectile = new SolidBallProjectile(
        startPos, facingRight, getDamage(), owner);
    qDebug() << "[DEBUG] SolidBall::attack projectile created:" << static_cast<void*>(projectile);
    
    // 添加到场景
    scene()->addItem(projectile);
    qDebug() << "[DEBUG] SolidBall::attack projectile added to scene, projectile scene:" << static_cast<void*>(projectile->scene());
    projectile->setPos(startPos);
    
    // 减少投掷次数
    throwCount--;
    qDebug() << "[DEBUG] SolidBall::attack throwCount after decrement:" << throwCount;
    
    // 如果没有投掷次数了，移除武器
    if (throwCount <= 0) {
        if (owner) owner->equipFist(); // 或 setWeapon(nullptr)
        // 不要 scene()->removeItem(this); deleteLater();
    }
}
