//
// Created by gerw on 8/20/24.
//

#include <QTransform>
#include "Character.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include "../Weapons/Fist.h"
#include "../Weapons/Sword.h"
#include "../Weapons/SolidBall.h"
#include "../Weapons/Rifle.h"
#include "../Weapons/Sniper.h"

Character::Character(QGraphicsItem *parent, const QString &characterPixmapPath) : Item(parent, characterPixmapPath) {
    // 设置角色缩放为0.5（缩小一半）
    if (pixmapItem != nullptr) {
        pixmapItem->setScale(0.5);
        pixmapItem->setTransformOriginPoint(pixmapItem->boundingRect().center());
    }
    
    // 加载动画帧
    loadAnimationFrames();
    
    // 设置初始帧
    setInitialFrame();
    
    // 初始化默认武器（拳头）
    equipFist();
}

void Character::loadAnimationFrames() {
    // 默认加载Link的动画帧
    idleFrame = QPixmap(":/Items/Characters/Link/green.png");
    walkFrame1 = QPixmap(":/Items/Characters/Link/Animations/WalkRight/frame1.png");
    walkFrame2 = QPixmap(":/Items/Characters/Link/Animations/WalkRight/frame2.png");
    duckFrame = QPixmap(":/Items/Characters/Link/Animations/Duck/duck.png");
    jumpFrame = QPixmap(":/Items/Characters/Link/Animations/Jump/jump.png");
    hitFrame = QPixmap(":/Items/Characters/Link/Animations/hit/hit.png");
    
    // 如果动画帧加载失败，使用原始图片
    if (walkFrame1.isNull()) {
        walkFrame1 = idleFrame;
    }
    if (walkFrame2.isNull()) {
        walkFrame2 = idleFrame;
    }
    if (duckFrame.isNull()) {
        duckFrame = idleFrame;
    }
    if (jumpFrame.isNull()) {
        jumpFrame = idleFrame;
    }
    if (hitFrame.isNull()) {
        hitFrame = idleFrame;
    }
}

void Character::setInitialFrame() {
    if (pixmapItem != nullptr) {
        pixmapItem->setPixmap(idleFrame);
    }
}

bool Character::isLeftDown() const {
    return leftDown;
}

void Character::setLeftDown(bool leftDown) {
    Character::leftDown = leftDown;
}

bool Character::isRightDown() const {
    return rightDown;
}

void Character::setRightDown(bool rightDown) {
    Character::rightDown = rightDown;
}

bool Character::isPickDown() const {
    return pickDown;
}

void Character::setPickDown(bool pickDown) {
    Character::pickDown = pickDown;
}

bool Character::isDuckDown() const {
    return duckDown;
}

void Character::setDuckDown(bool duckDown) {
    Character::duckDown = duckDown;
}

bool Character::isJumpDown() const {
    return jumpDown;
}

void Character::setJumpDown(bool jumpDown) {
    Character::jumpDown = jumpDown;
}

const QPointF &Character::getVelocity() const {
    return velocity;
}

void Character::setVelocity(const QPointF &velocity) {
    Character::velocity = velocity;
}

void Character::processInput() {
    const auto moveSpeed = 0.3;
    const auto airMoveSpeed = 0.5; // 空中移动速度，稍微快一点
    const auto jumpSpeed = -1.5; // 负值表示向上
    const auto gravity = 0.08; // 重力
    const auto maxFallSpeed = 1.5; // 最大下落速度

    // 处理受击状态
    if (isHitState) {
        hitAnimationCounter++;
        if (hitAnimationCounter > 30) { // 受击动画持续30帧
            isHitState = false;
            hitAnimationCounter = 0;
        }
        return; // 受击时不能移动或攻击
    }

    // 处理攻击
    processAttack();

    // 处理跳跃
    if (!lastJumpDown && jumpDown && !_isJumping) {
        // 开始跳跃
        _isJumping = true;
        jumpCount = 1; // 只允许一段跳
        velocity.setY(jumpSpeed);
    }

    // 处理水平移动（重置X轴速度，避免累积）
    velocity.setX(0); // 重置水平速度
    if (!isDuckDown()) {
        // 根据是否跳跃选择移动速度
        qreal currentMoveSpeed = _isJumping ? airMoveSpeed : moveSpeed;
        
        if (isLeftDown()) {
            velocity.setX(-currentMoveSpeed);
        }
        if (isRightDown()) {
            velocity.setX(currentMoveSpeed);
        }
    }

    // 始终应用重力（除非碰到地图组件）
    velocity.setY(qMin(velocity.y() + gravity, maxFallSpeed));
    
    // 如果Y速度为0且之前是跳跃状态，说明落地了，重置跳跃状态
    if (velocity.y() == 0 && _isJumping) {
        _isJumping = false;
        jumpCount = 0;
    }

    // 更新动画状态
    if (isDuckDown()) {
        // 蹲下状态
        isWalking = false;
        isDucking = true;
        _isJumping = false;
    } else if (_isJumping) {
        // 跳跃状态
        isWalking = false;
        isDucking = false;
        isDoubleJumping = false;
        // 根据水平移动方向更新朝向
        if (velocity.x() > 0) {
            isWalkingRight = true;
        } else if (velocity.x() < 0) {
            isWalkingRight = false;
        }
    } else if (velocity.x() != 0) {
        // 行走状态
        isWalking = true;
        isDucking = false;
        _isJumping = false;
        isWalkingRight = (velocity.x() > 0);
    } else {
        // 静止状态
        isWalking = false;
        isDucking = false;
        _isJumping = false;
    }

    if (pickDown) {
        picking = true;
    } else {
        picking = false;
    }
    lastPickDown = pickDown;
    lastJumpDown = jumpDown;
    
    // 更新武器位置（只在状态改变时更新）
    if (currentWeapon) {
        static bool lastWalkingRight = isWalkingRight;
        static bool lastDucking = isDucking;
        
        // 只在朝向或蹲下状态改变时更新武器位置
        if (lastWalkingRight != isWalkingRight || lastDucking != isDucking) {
            currentWeapon->updatePosition(isWalkingRight, isDucking);
            // 强制更新武器显示
            currentWeapon->update();
            lastWalkingRight = isWalkingRight;
            lastDucking = isDucking;
        }
    }
}

bool Character::isPicking() const {
    return picking;
}

Armor *Character::pickupArmor(Armor *newArmor) {
    auto oldArmor = armor;
    if (oldArmor != nullptr) {
        oldArmor->unmount();
        oldArmor->setPos(newArmor->pos());
        oldArmor->setParentItem(parentItem());
    }
    newArmor->setParentItem(this);
    newArmor->mountToParent();
    armor = newArmor;
    return oldArmor;
}

// 碰撞检测实现
bool Character::collidesWith(const QGraphicsItem *other) const {
    if (other == nullptr) return false;
    
    // 使用Qt内置的碰撞检测
    return collidesWithItem(other);
}

bool Character::collidesWithMap() const {
    // 检查与地图的碰撞
    auto scene = this->scene();
    if (scene == nullptr) return false;
    
    // 获取角色在场景中的边界矩形
    QRectF characterRect = sceneBoundingRect();
    
    // 检查是否超出场景边界
    QRectF sceneRect = scene->sceneRect();
    return !sceneRect.contains(characterRect);
}

QRectF Character::getCollisionRect() const {
    // 返回角色图片的实际边界作为碰撞箱，以中心点进行0.5倍缩放
    if (pixmapItem && !pixmapItem->pixmap().isNull()) {
        QRectF originalRect = pixmapItem->boundingRect();
        // 以中心点进行0.5倍缩放，与图片缩放方式一致
        qreal centerX = originalRect.center().x();
        qreal centerY = originalRect.center().y();
        qreal scaledWidth = originalRect.width() * 0.5;
        qreal scaledHeight = originalRect.height() * 0.5;
        return QRectF(centerX - scaledWidth/2, centerY - scaledHeight/2, 
                     scaledWidth, scaledHeight);
    }
    // 如果没有图片，返回默认边界
    return boundingRect();
}

void Character::updateAnimation() {
    if (pixmapItem == nullptr) {
        return;
    }
    if (invisible) {
        pixmapItem->setVisible(false); // 隐身时隐藏角色本体
        if (currentWeapon) currentWeapon->setVisible(true); // 武器始终可见
        return;
    } else {
        pixmapItem->setVisible(true); // 非隐身时显示角色本体
        if (currentWeapon) currentWeapon->setVisible(true);
    }
    
    animationCounter++;
    
    // 受击状态优先显示
    if (isHitState) {
        // 受击状态，显示受击动画
        if (isWalkingRight) {
            // 朝右受击
            pixmapItem->setPixmap(hitFrame);
        } else {
            // 朝左受击，水平翻转
            QPixmap flippedHit = hitFrame.transformed(QTransform().scale(-1, 1));
            pixmapItem->setPixmap(flippedHit);
        }
        animationFrame = 0;
        animationCounter = 0;
        
        // 更新武器朝向
        if (currentWeapon) {
            currentWeapon->updatePosition(isWalkingRight, isDucking);
        }
        return;
    }
    
    if (isDucking) {
        // 蹲下状态，根据朝向显示蹲下图片
        if (isWalkingRight) {
            // 朝右蹲下
            pixmapItem->setPixmap(duckFrame);
        } else {
            // 朝左蹲下，水平翻转
            QPixmap flippedDuck = duckFrame.transformed(QTransform().scale(-1, 1));
            pixmapItem->setPixmap(flippedDuck);
        }
        animationFrame = 0;
        animationCounter = 0;
        
        // 更新武器朝向
        if (currentWeapon) {
            currentWeapon->updatePosition(isWalkingRight, isDucking);
        }
    } else if (_isJumping) {
        // 跳跃状态，根据朝向显示跳跃图片
        if (isWalkingRight) {
            // 朝右跳跃
            pixmapItem->setPixmap(jumpFrame);
        } else {
            // 朝左跳跃，水平翻转
            QPixmap flippedJump = jumpFrame.transformed(QTransform().scale(-1, 1));
            pixmapItem->setPixmap(flippedJump);
        }
        animationFrame = 0;
        animationCounter = 0;
        
        // 更新武器朝向
        if (currentWeapon) {
            currentWeapon->updatePosition(isWalkingRight, isDucking);
        }
    } else if (isWalking) {
        // 每20帧切换一次动画帧（约每0.22秒）
        if (animationCounter % 20 == 0) {
            animationFrame = (animationFrame + 1) % 2;
            
            // 根据移动方向选择动画帧
            if (isWalkingRight) {
                // 向右移动，使用原始帧
                if (animationFrame == 0) {
                    pixmapItem->setPixmap(walkFrame1);
                } else {
                    pixmapItem->setPixmap(walkFrame2);
                }
            } else {
                // 向左移动，水平翻转帧
                QPixmap flippedFrame;
                if (animationFrame == 0) {
                    flippedFrame = walkFrame1.transformed(QTransform().scale(-1, 1));
                } else {
                    flippedFrame = walkFrame2.transformed(QTransform().scale(-1, 1));
                }
                pixmapItem->setPixmap(flippedFrame);
            }
        }
    } else {
        // 静止状态，保持朝向最后一次移动的方向
        if (isWalkingRight) {
            // 朝右静止
            pixmapItem->setPixmap(idleFrame);
        } else {
            // 朝左静止，水平翻转
            QPixmap flippedIdle = idleFrame.transformed(QTransform().scale(-1, 1));
            pixmapItem->setPixmap(flippedIdle);
        }
        animationFrame = 0;
        animationCounter = 0;
    }
    
    // 更新武器朝向
    if (currentWeapon) {
        currentWeapon->updatePosition(isWalkingRight, isDucking);
        // 强制更新武器显示
        currentWeapon->update();
    }
}

void Character::setJumping(bool jumping) {
    _isJumping = jumping;
}

void Character::setJumpCount(int count) {
    jumpCount = count;
}

void Character::setHealth(int health) {
    this->health = qBound(0, health, maxHealth);
}

void Character::takeDamage(int damage) {
    if (damage > 0) {
        health = qMax(0, health - damage);
    }
}

void Character::heal(int amount) {
    if (amount > 0) {
        health = qMin(maxHealth, health + amount);
    }
}

void Character::setAttackDown(bool attackDown) {
    this->attackDown = attackDown;
}

void Character::processAttack() {
    qDebug() << "[DEBUG] Character::processAttack called, attackDown:" << attackDown << ", lastAttackDown:" << lastAttackDown << ", weapon:" << (currentWeapon ? currentWeapon->getWeaponType() : "nullptr");
    if (currentWeapon && attackDown && !lastAttackDown) {
        qDebug() << "[DEBUG] Character::processAttack, weapon type:" << currentWeapon->getWeaponType();
        currentWeapon->attack();
    }
    lastAttackDown = attackDown;
}

void Character::takeHit() {
    if (!isHitState) {
        isHitState = true;
        hitAnimationCounter = 0;
    }
}

void Character::setWeapon(Weapon *weapon) {
    if (!weapon) {
        qDebug() << "[ERROR] setWeapon called with nullptr!";
        return;
    }
    qDebug() << "[DEBUG] setWeapon called for" << this << "Weapon type:" << weapon->getWeaponType();
    if (currentWeapon) {
        // 彻底防御：先断开parent，再remove，再delete
        try {
            currentWeapon->setParentItem(nullptr);
            if (scene()) {
                scene()->removeItem(currentWeapon);
            }
            delete currentWeapon;
        } catch (...) {
            qDebug() << "[ERROR] Exception during delete currentWeapon!";
        }
        currentWeapon = nullptr;
    }
    currentWeapon = weapon;
    currentWeapon->setOwner(this);
    currentWeapon->setParentItem(this);
    qDebug() << "[SETWEAPON]" << this << "now has weapon:" << (currentWeapon ? currentWeapon->getWeaponType() : "nullptr");
}

void Character::equipSword() {
    qDebug() << "[DEBUG] equipSword called for" << this;
    Sword *sword = new Sword(this);
    setWeapon(sword);
}

void Character::equipFist() {
    qDebug() << "[DEBUG] equipFist called for" << this;
    Fist *fist = new Fist(this);
    setWeapon(fist);
}

void Character::equipSolidBall() {
    qDebug() << "[DEBUG] equipSolidBall called for" << this;
    setWeapon(new SolidBall(3, this));
}

void Character::equipRifle() {
    setWeapon(new Rifle(this));
}

void Character::equipSniper() {
    setWeapon(new Sniper(this));
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    // 不手动绘制角色图片，让pixmapItem自动处理
    // 绘制碰撞箱可视化（红色线条）
    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(getCollisionRect());
}

void Character::setSpeedMultiplier(qreal multiplier) {
    speedMultiplier = multiplier;
}

qreal Character::getSpeedMultiplier() const {
    return speedMultiplier;
}

void Character::setInvisible(bool val) { invisible = val; }
bool Character::isInvisible() const { return invisible; }
qreal Character::getCurrentSpeed() const { return baseSpeed * speedMultiplier; }
bool Character::isCrouching() const { return duckDown; }
