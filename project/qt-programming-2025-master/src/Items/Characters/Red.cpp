//
// Created by gerw on 8/20/24.
//

#include <memory>
#include "Red.h"
#include "../HeadEquipments/CapOfTheHero.h"
#include "../Armors/OldShirt.h"
#include "../LegEquipments/WellWornTrousers.h"
#include "../Weapons/SolidBall.h"

Red::Red(QGraphicsItem *parent, const QString &characterPixmapPath) : Character(parent, characterPixmapPath) {
    // 重新加载Red角色的动画帧（覆盖父类加载的Link动画帧）
    loadAnimationFrames();
    
    // 设置初始朝向为向左（与Link相反）
    setRightDown(false);
    setLeftDown(false);
    
    // 重新设置初始帧
    setInitialFrame();
    
    // headEquipment = new CapOfTheHero(this);
    // legEquipment = new WellWornTrousers(this);
    // armor = new OldShirt(this);
    // headEquipment->mountToParent();
    // legEquipment->mountToParent();
    // armor->mountToParent();
    // equipSolidBall();
    // equipFist(); // 删除Red::equipFist实现（如果有）
}

void Red::loadAnimationFrames() {
    // 加载Red角色的动画帧
    idleFrame = QPixmap(":/Items/Characters/Red/Red.png");
    walkFrame1 = QPixmap(":/Items/Characters/Red/Animations/WalkRight/frame1.png");
    walkFrame2 = QPixmap(":/Items/Characters/Red/Animations/WalkRight/frame2.png");
    duckFrame = QPixmap(":/Items/Characters/Red/Animations/Duck/duck.png");
    jumpFrame = QPixmap(":/Items/Characters/Red/Animations/Jump/jump.png");
    hitFrame = QPixmap(":/Items/Characters/Red/Animations/hit/hit.png");
    
    qDebug() << "Red: Loading animation frames";
    qDebug() << "Red: idleFrame loaded:" << !idleFrame.isNull();
    qDebug() << "Red: walkFrame1 loaded:" << !walkFrame1.isNull();
    qDebug() << "Red: walkFrame2 loaded:" << !walkFrame2.isNull();
    qDebug() << "Red: duckFrame loaded:" << !duckFrame.isNull();
    qDebug() << "Red: jumpFrame loaded:" << !jumpFrame.isNull();
    qDebug() << "Red: hitFrame loaded:" << !hitFrame.isNull();
    
    // 如果动画帧加载失败，使用原始图片
    if (walkFrame1.isNull()) {
        walkFrame1 = idleFrame;
        qDebug() << "Red: Using idleFrame for walkFrame1";
    }
    if (walkFrame2.isNull()) {
        walkFrame2 = idleFrame;
        qDebug() << "Red: Using idleFrame for walkFrame2";
    }
    if (duckFrame.isNull()) {
        duckFrame = idleFrame;
        qDebug() << "Red: Using idleFrame for duckFrame";
    }
    if (jumpFrame.isNull()) {
        jumpFrame = idleFrame;
        qDebug() << "Red: Using idleFrame for jumpFrame";
    }
    if (hitFrame.isNull()) {
        hitFrame = idleFrame;
        qDebug() << "Red: Using idleFrame for hitFrame";
    }
}

void Red::setInitialFrame() {
    if (pixmapItem != nullptr) {
        // 设置初始帧为朝左的静止状态
        QPixmap flippedIdle = idleFrame.transformed(QTransform().scale(-1, 1));
        pixmapItem->setPixmap(flippedIdle);
        // 设置初始朝向为向左
        isWalkingRight = false;
        qDebug() << "Red: Set initial frame to left-facing";
    }
}

void Red::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    // 不手动绘制角色图片，让pixmapItem自动处理
    // 绘制碰撞箱可视化（绿色线条，与Link的红色区分）
    painter->setPen(QPen(Qt::green, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(getCollisionRect());
}

void Red::setAIEnabled(bool enabled) {
    aiEnabled = enabled;
}

bool Red::isAIEnabled() const {
    return aiEnabled;
}

void Red::updateAI() {
    if (!aiEnabled) {
        return;
    }
    
    // TODO: 在这里实现AI逻辑
    // 例如：自动移动、追踪玩家、躲避障碍等
}

