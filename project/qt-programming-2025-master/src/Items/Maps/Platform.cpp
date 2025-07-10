//
// Created by gerw on 8/21/24.
//

#include "Platform.h"
#include <QDebug>

Platform::Platform(QGraphicsItem *parent) : TileEntity(parent), platformType(GRASS), speedMultiplier(1.0) {
    updateTexture();
}

bool Platform::collidesWith(const QRectF &rect) const {
    if (platformType == BUSH) {
        // 灌木丛不阻挡
        return false;
    }
    // 其它平台只检测顶部碰撞
    QRectF platformRect = boundingRect();
    QRectF topCollisionRect = QRectF(platformRect.x(), platformRect.y(), 
                                     platformRect.width(), 5);
    return topCollisionRect.intersects(rect);
}

void Platform::applyEffectToCharacter(Character *character) {
    if (!character) return;
    switch (platformType) {
        case GRASS:
            // 无特效
            break;
        case SNOW:
            character->setSpeedMultiplier(1.5);
            break;
        case BUSH:
            if (this->sceneBoundingRect().intersects(character->sceneBoundingRect()) && character->isCrouching()) {
                character->setInvisible(true);
            }
            break;
    }
}

void Platform::setPlatformType(PlatformType type) {
    platformType = type;
    switch (type) {
        case GRASS:
            speedMultiplier = 1.0;
            break;
        case SNOW:
            speedMultiplier = 1.5; // 适当加速
            break;
        case BUSH:
            speedMultiplier = 1.0;
            break;
    }
    updateTexture();
}

void Platform::setPlatformPosition(int x, int totalWidth) {
    // 计算平台在草地中的位置
    if (totalWidth <= 1) {
        platformPosition = 0; // 单个平台
    } else if (x == 0) {
        platformPosition = 0; // 最左侧
    } else if (x == totalWidth - 1) {
        platformPosition = 2; // 最右侧
    } else {
        platformPosition = 1; // 中间
    }
    
    // 更新纹理
    updateTexture();
}

void Platform::updateTexture() {
    QString texturePath;
    switch (platformType) {
        case GRASS:
            texturePath = ":/Items/Maps/Tile/Platform/grass/1.png";
            break;
        case SNOW:
            texturePath = ":/Items/Maps/Tile/Platform/snow/1.png";
            break;
        case BUSH:
            texturePath = ":/Items/Maps/Tile/Platform/bush/bush.png";
            break;
    }
    setTexture(texturePath);
}

bool Platform::isCharacterOnPlatform(Character *character) const {
    if (!character) return false;
    
    QRectF characterRect = character->boundingRect();
    QRectF platformRect = boundingRect();
    
    // 检查角色的底部是否与平台顶部接触
    qreal characterBottom = character->pos().y() + characterRect.bottom();
    qreal platformTop = pos().y() + platformRect.top();
    
    // 允许一定的容差
    const qreal tolerance = 5.0;
    
    return qAbs(characterBottom - platformTop) <= tolerance &&
           character->pos().x() + characterRect.left() < pos().x() + platformRect.right() &&
           character->pos().x() + characterRect.right() > pos().x() + platformRect.left();
} 
