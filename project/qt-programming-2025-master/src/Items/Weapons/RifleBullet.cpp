#include "RifleBullet.h"
#include <QDebug>
#include <QGraphicsScene>

const qreal BULLET_SPEED = 8.0;

RifleBullet::RifleBullet(QPointF startPos, bool facingRight, int damage, Character* owner, QGraphicsItem* parent)
    : QObject(), QGraphicsItem(parent), position(startPos), damage(damage), owner(owner) {
    velocity = QPointF(facingRight ? BULLET_SPEED : -BULLET_SPEED, 0);
    bulletPixmap = QPixmap(":/Items/weapons/smallbullet.png");
    if (bulletPixmap.isNull()) {
        qDebug() << "RifleBullet: ERROR - bulletPixmap is null!";
    }
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &RifleBullet::updatePosition);
    moveTimer->start(16); // 约60FPS
}

QRectF RifleBullet::boundingRect() const {
    if (bulletPixmap.isNull()) {
        return QRectF(-3, -3, 6, 6);
    }
    return QRectF(0, 0, bulletPixmap.width(), bulletPixmap.height());
}

void RifleBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if (!active) return;
    if (bulletPixmap.isNull()) {
        painter->setBrush(Qt::yellow);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(boundingRect());
    } else {
        painter->drawPixmap(0, 0, bulletPixmap);
    }
    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

void RifleBullet::updatePosition() {
    if (!active) return;
    position += velocity;
    setPos(position);
    // 检查与所有角色的碰撞
    for (QGraphicsItem* item : scene()->items()) {
        if (auto* character = dynamic_cast<Character*>(item)) {
            if (character == owner) continue; // 跳过自己
            if (collidesWithCharacter(character)) {
                character->takeDamage(damage);
                character->takeHit();
                active = false;
                scene()->removeItem(this);
                deleteLater();
                return;
            }
        }
    }
    // 检查是否超出场景边界
    if (!scene() || !scene()->sceneRect().contains(position)) {
        active = false;
        scene()->removeItem(this);
        deleteLater();
        return;
    }
    update();
}

bool RifleBullet::collidesWithCharacter(Character *target) const {
    if (!active || !target || !scene()) return false;
    QRectF bulletRect = boundingRect().translated(position);
    QRectF targetRect = target->getCollisionRect().translated(target->pos());
    return bulletRect.intersects(targetRect);
} 