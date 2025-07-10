// SolidBallProjectile.cpp
#include "SolidBallProjectile.h"
#include "../Characters/Character.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QtMath>

const qreal GRAVITY = 0.2;     // 重力加速度
const qreal INITIAL_VY = -4.0; // 初始垂直速度
const qreal INITIAL_VX = 6.0;  // 初始水平速度

SolidBallProjectile::SolidBallProjectile(QPointF startPos, bool facingRight, int damage, Character* owner, QGraphicsItem* parent)
    : QObject(), QGraphicsItem(parent), position(startPos), damage(damage), owner(owner) {
    
    // 设置速度方向
    velocity = QPointF(facingRight ? INITIAL_VX : -INITIAL_VX, INITIAL_VY);
    
    // 加载子弹图片
    bulletPixmap = QPixmap(":/Items/weapons/weight.png");
    if (bulletPixmap.isNull()) {
        qDebug() << "SolidBallProjectile: ERROR - bulletPixmap is null!";
        bulletPixmap = QPixmap("：/Items/weapons/solid_ball.png");
    }
    
    // 设置移动定时器
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &SolidBallProjectile::updatePosition);
    moveTimer->start(16); // 约60FPS
}

QRectF SolidBallProjectile::boundingRect() const {
    if (bulletPixmap.isNull()) {
        return QRectF(-5, -5, 10, 10);
    }
    // 返回缩放后的实际显示区域
    return QRectF(0, 0, bulletPixmap.width() * 0.3, bulletPixmap.height() * 0.3);
}

void SolidBallProjectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    if (!active) return;
    
    if (bulletPixmap.isNull()) {
        // 绘制默认圆形
        painter->setBrush(Qt::darkGray);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(boundingRect());
    } else {
        // 放大2倍显示
        painter->drawPixmap(0, 0, bulletPixmap.scaled(bulletPixmap.width()*0.3, bulletPixmap.height()*0.3));
    }
    // 绘制碰撞体积（红色线框）
    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

void SolidBallProjectile::updatePosition() {
    if (!active) return;

    // 应用重力
    velocity.setY(velocity.y() + GRAVITY);

    // 更新位置
    position += velocity;
    setPos(position);

    // 检查与所有角色的碰撞
    for (QGraphicsItem* item : scene()->items()) {
        if (auto* character = dynamic_cast<Character*>(item)) {
            if (character == owner) continue; // 跳过自己
            if (collidesWithCharacter(character)) {
                character->takeDamage(damage);
                character->takeHit(); // 触发受击动画
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

    // 更新显示
    update();

    qDebug() << "[DEBUG] SolidBallProjectile pos:" << position << "velocity:" << velocity;
}

bool SolidBallProjectile::collidesWithCharacter(Character *target) const {
    if (!active || !target || !scene()) return false;
    
    // 计算子弹的碰撞矩形
    QRectF bulletRect = boundingRect().translated(position);
    
    // 获取目标的碰撞矩形
    QRectF targetRect = target->getCollisionRect().translated(target->pos());
    
    // 检查碰撞
    return bulletRect.intersects(targetRect);
}
