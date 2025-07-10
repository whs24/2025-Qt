//
// Created by gerw on 8/20/24.
//

#include "HealthHUD.h"
#include <QDebug>
#include <QTransform>

HealthHUD::HealthHUD(QGraphicsItem *parent) : QGraphicsItem(parent) {
    // 加载素材
    greenAvatar = QPixmap(":/Items/Characters/heart/green.png");
    redAvatar = QPixmap(":/Items/Characters/heart/red.png");
    heartIcon = QPixmap(":/Items/Characters/heart/hud_heart.png");
    
    // 加载数字图标
    for (int i = 0; i < 10; ++i) {
        numberIcons[i] = QPixmap(QString(":/Items/Characters/heart/hud_character_%1.png").arg(i));
    }
    
    qDebug() << "HealthHUD: Loading assets";
    qDebug() << "HealthHUD: greenAvatar loaded:" << !greenAvatar.isNull();
    qDebug() << "HealthHUD: redAvatar loaded:" << !redAvatar.isNull();
    qDebug() << "HealthHUD: heartIcon loaded:" << !heartIcon.isNull();
    
    for (int i = 0; i < 10; ++i) {
        qDebug() << "HealthHUD: numberIcons[" << i << "] loaded:" << !numberIcons[i].isNull();
    }
    
    // 设置HUD位置在屏幕顶部
    setPos(0, 0);
    setZValue(1000); // 确保HUD在最上层
}

void HealthHUD::setGreenHealth(int health) {
    greenHealth = qBound(0, health, 100);
    update(); // 触发重绘
}

void HealthHUD::setRedHealth(int health) {
    redHealth = qBound(0, health, 100);
    update(); // 触发重绘
}

QRectF HealthHUD::boundingRect() const {
    // HUD覆盖整个屏幕宽度，高度为100像素
    return QRectF(0, 0, 1280, 100);
}

void HealthHUD::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    // 绘制绿色角色生命值（左侧）
    drawCharacterHealth(painter, greenAvatar, greenHealth, 20, 20);
    
    // 绘制红色角色生命值（右侧，再往左移）
    drawCharacterHealth(painter, redAvatar, redHealth, 1280 - 270, 20);
}

void HealthHUD::drawCharacterHealth(QPainter *painter, const QPixmap &avatar, int health, int x, int y) {
    if (avatar.isNull()) {
        qDebug() << "HealthHUD: Avatar is null, skipping draw";
        return;
    }
    
    // 缩放因子，调整为1.5倍（比初版大，比现在小）
    qreal scale = 0.45; // 从0.6改为0.45，调整为1.5倍
    
    // 绘制头像
    QPixmap scaledAvatar = avatar.scaled(avatar.width() * scale, avatar.height() * scale, 
                                        Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(x, y, scaledAvatar);
    
    // 绘制爱心图标
    if (!heartIcon.isNull()) {
        QPixmap scaledHeart = heartIcon.scaled(heartIcon.width() * scale, heartIcon.height() * scale,
                                              Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(x + scaledAvatar.width() + 10, y + 5, scaledHeart);
    }
    
    // 绘制生命值数字
    drawNumber(painter, health, x + scaledAvatar.width() + 10 + (heartIcon.isNull() ? 0 : heartIcon.width() * scale) + 10, y + 5);
}

void HealthHUD::drawNumber(QPainter *painter, int number, int x, int y) {
    // 将数字转换为字符串
    QString numberStr = QString::number(number);
    
    // 缩放因子，调整为1.5倍
    qreal scale = 0.45; // 从0.6改为0.45，调整为1.5倍
    
    // 绘制每一位数字，进一步减少间距
    for (int i = 0; i < numberStr.length(); ++i) {
        int digit = numberStr[i].digitValue();
        if (digit >= 0 && digit <= 9 && !numberIcons[digit].isNull()) {
            QPixmap scaledDigit = numberIcons[digit].scaled(numberIcons[digit].width() * scale, 
                                                          numberIcons[digit].height() * scale,
                                                          Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter->drawPixmap(x + i * 0.6*(scaledDigit.width() + 0.5), y, scaledDigit);
        }
    }
} 
