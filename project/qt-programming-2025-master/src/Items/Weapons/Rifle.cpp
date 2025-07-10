#include "Rifle.h"
#include "RifleBullet.h"
#include "../Characters/Character.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>

Rifle::Rifle(QGraphicsItem* parent)
    : Gun(5, 200, parent) // 5发子弹，射击间隔200ms
{
    loadWeaponPixmaps();
}

void Rifle::loadWeaponPixmaps() {
    weaponPixmap = QPixmap(":/Items/weapons/small.png");
    if (weaponPixmap.isNull()) {
        qDebug() << "Rifle: ERROR - weaponPixmap is null!";
    }
}

void Rifle::attack() {
    if (!owner) return;
    if (canShoot()) {
        shoot(owner->getIsWalkingRight());
    }
}

void Rifle::shoot(bool facingRight) {
    if (!scene() || bullets <= 0 || coolingDown) return;
    // 计算子弹起始位置
    QPointF startPos = owner->pos() + QPointF(facingRight ? owner->boundingRect().width() : -20, getAttackOffsetY() + 100);
    RifleBullet* bullet = new RifleBullet(startPos, facingRight, getDamage(), owner);
    scene()->addItem(bullet);
    bullet->setPos(startPos);
    bullets--;
    startCooldown();
    if (bullets <= 0 && owner) {
        owner->equipFist(); // 子弹打完失去武器
    }
}

void Rifle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if (weaponPixmap.isNull()) return;
    QPixmap displayPixmap = weaponPixmap;
    qreal scale = getWeaponScale();
    QPixmap scaledPixmap = displayPixmap.scaled(displayPixmap.width() * scale, displayPixmap.height() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if (!facingRight) {
        painter->save();
        painter->translate(scaledPixmap.width(), 0);
        painter->scale(-1, 1);
        painter->drawPixmap(0, 0, scaledPixmap);
        painter->restore();
    } else {
        painter->drawPixmap(-30, 0, scaledPixmap);
    }
    // 绘制碰撞箱（红色，便于调试）
    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

