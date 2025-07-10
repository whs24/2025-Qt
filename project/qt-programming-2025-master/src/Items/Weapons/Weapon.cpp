//
// Created by gerw on 8/20/24.
//

#include "Weapon.h"
#include "../Characters/Character.h"
#include <QDebug>
#include <QTransform>
#include <QObject>
#include <QGraphicsScene>
#include "../Maps/Platform.h"
#include "../Maps/TileMap.h"

Weapon::Weapon(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent) {
    // 创建攻击计时器
    attackTimer = new QTimer(this);
    attackTimer->setSingleShot(true);
    connect(attackTimer, &QTimer::timeout, this, &Weapon::onAttackFinished);
    
    setZValue(1000); // 确保武器在角色之上，使用更高的Z值
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

void Weapon::startAttack(bool facingRight) {
    if (attacking) return; // 防止重复攻击
    
    this->facingRight = facingRight;
    attacking = true;
    hasDealtDamage = false; // 重置伤害状态
    setVisible(true); // 攻击时总是可见
    
    // 更新武器位置
    updatePosition(facingRight, false);
    
    // 强制更新显示
    update();
    
    // 设置攻击持续时间（300毫秒）
    attackTimer->start(300);
}

void Weapon::stopAttack() {
    attacking = false;
    hasDealtDamage = false; // 重置伤害状态
    
    // 根据武器类型设置可见性
    setVisible(isVisibleByDefault());
    
    // 更新位置到默认位置
    updatePosition(facingRight, false);
    
    // 强制更新显示
    update();
}

void Weapon::onAttackFinished() {
    stopAttack();
    // 强制更新显示，确保碰撞箱消失
    update();
}

bool Weapon::collidesWithCharacter(Character *target) const {
    if (!attacking || !target || target == owner || hasDealtDamage) return false;
    
    // 计算武器在场景中的绝对位置
    QRectF weaponRect = calculateWeaponRect(facingRight, false);
    weaponRect.translate(scenePos());
    
    // 获取目标的碰撞箱
    QRectF targetRect = target->getCollisionRect();
    targetRect.translate(target->pos());
    
    // 检查碰撞
    bool collision = weaponRect.intersects(targetRect);
    if (collision) {
        // 标记已造成伤害
        const_cast<Weapon*>(this)->hasDealtDamage = true;
    }
    return collision;
}

QRectF Weapon::boundingRect() const {
    return calculateWeaponRect(facingRight, false);
}

void Weapon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    if (weaponPixmap.isNull()) {
        qDebug() << "Weapon::paint - weaponPixmap is null";
        // 绘制一个默认的红色矩形作为占位符
        painter->setPen(QPen(Qt::red, 3));
        painter->setBrush(Qt::red);
        painter->drawRect(QRectF(0, 0, 20, 10));
        return;
    }
    
    // 处理图片
    QPixmap displayPixmap = weaponPixmap;
    
    // 缩放图片
    qreal scale = getWeaponScale();
    QPixmap scaledPixmap = displayPixmap.scaled(displayPixmap.width() * scale, 
                                                displayPixmap.height() * scale,
                                                Qt::KeepAspectRatio, Qt::SmoothTransformation);
    
    // 剑在攻击时旋转90度
    if (attacking && getWeaponType() == "Sword") {
        painter->save();
        // 移动到图片中心进行旋转
        painter->translate(scaledPixmap.width() / 2, scaledPixmap.height() / 2);
        if (facingRight) {
            painter->rotate(90);
        } else {
            painter->rotate(-90);
        }
        painter->translate(-scaledPixmap.width() / 2, -scaledPixmap.height() / 2);
        painter->drawPixmap(0, 0, scaledPixmap);
        painter->restore();
    } else {
        // 向左攻击时翻转图片
        if (!facingRight && attacking) {
            // 在绘制时进行水平翻转
            painter->save();
            painter->translate(scaledPixmap.width(), 0);
            painter->scale(-1, 1);
            painter->drawPixmap(0, 0, scaledPixmap);
            painter->restore();
        } else {
            painter->drawPixmap(0, 0, scaledPixmap);
        }
    }
    
    // 始终显示碰撞箱（红色，便于调试）
    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

void Weapon::updatePosition(bool facingRight, bool isDucking) {
    this->facingRight = facingRight;
    
    QPointF newPos = calculateWeaponPosition(facingRight, isDucking);
    setPos(newPos);
    
    // 如果不是攻击状态，设置默认可见性
    if (!attacking) {
        setVisible(isVisibleByDefault());
    }
    
    // 强制更新显示，确保动画流畅
    update();
    
    // 通知场景重绘
    if (scene()) {
        scene()->update();
    }
    
    // 调试：输出武器朝向信息

}

QPointF Weapon::calculateWeaponPosition(bool facingRight, bool isDucking) const {
    if (!owner) return QPointF(0, 0);
    
    // 获取角色碰撞箱
    QRectF ownerRect = owner->getCollisionRect();
    qreal ownerWidth = ownerRect.width();
    qreal ownerHeight = ownerRect.height();
    
    // 获取武器自身尺寸
    qreal scale = getWeaponScale();
    qreal weaponWidth = weaponPixmap.width() * scale;
    qreal weaponHeight = weaponPixmap.height() * scale;
    
    qreal x, y;
    qreal attackDistance = getAttackDistance();
    
    if (attacking) {
        // 攻击时，武器向前伸出
        qreal directionFactor = facingRight ? 1.0 : -1.0;
        
        // 计算武器中心点相对于角色中心的水平位置
        qreal weaponCenterOffset = ownerWidth / 2 + attackDistance;
        
        // 根据方向调整武器左上角坐标
        x = ownerWidth  + directionFactor * weaponCenterOffset -
            (facingRight ? 0 : weaponWidth); // 关键点：向左攻击时减去武器宽度
        
        // 垂直方向以角色中心为基准，考虑武器高度和垂直偏移
        y = ownerHeight  + getAttackOffsetY() - weaponHeight / 2;
    } else {
        // 非攻击时，武器在腰间
        if (!facingRight) {
            x = ownerWidth / 2 - weaponWidth / 2; // 居中显示
        } else {
            if (getWeaponType() == "SolidBall") {
                x = ownerWidth / 2 + weaponWidth / 0.6;
            } else {
                x = ownerWidth / 2 + weaponWidth / 0.3; // 居中显示
            }
            // 向左时，剑的位置相对于中心对称

        }
        y = ownerHeight / 2 + getDefaultOffsetY() - weaponHeight / 2;
    }
    
    return QPointF(x, y);
}

QRectF Weapon::calculateWeaponRect(bool facingRight, bool isDucking) const {
    if (weaponPixmap.isNull()) return QRectF(0, 0, 0, 0);
    
    // 获取武器缩放比例
    qreal scale = getWeaponScale();
    qreal width = weaponPixmap.width() * scale;
    qreal height = weaponPixmap.height() * scale;
    
    // 直接使用图片边框作为碰撞箱

    return QRectF(0, 0, width, height);

} 

void Weapon::attack() {}
void Weapon::update() {} 

void Weapon::fallUpdate(const QList<QGraphicsItem*>& platforms, qreal gravity, qreal maxFallSpeed) {
    if (!isFalling) return;
    // 应用重力
    velocity.setY(qMin(velocity.y() + gravity, maxFallSpeed));
    QPointF newPos = pos() + velocity;
    QRectF weaponSceneRect = this->sceneBoundingRect();
    // 获取TileMap指针
    TileMap* tileMap = nullptr;
    if (scene() && !scene()->items().isEmpty()) {
        for (QGraphicsItem* item : scene()->items()) {
            tileMap = dynamic_cast<TileMap*>(item);
            if (tileMap) break;
        }
    }
    bool collided = false;
    if (tileMap && tileMap->checkCollision(weaponSceneRect)) {
        collided = true;
        // 停止在当前Y
        setY(pos().y());
    }
    if (!collided) {
        setPos(newPos);
    } else {
        velocity.setY(0);
        isFalling = false;
    }
} 
