//
// Created by gerw on 8/21/24.
//

#pragma once
#include "TileEntity.h"
#include "../Characters/Character.h"
#include <QGraphicsItem>

enum PlatformType { GRASS, BUSH, SNOW };

class Platform : public TileEntity {
public:
    Platform(QGraphicsItem *parent = nullptr);
    
    // 重写碰撞检测，平台有特殊的碰撞逻辑
    bool collidesWith(const QRectF &rect) const override;
    
    // 平台对角色施加的效果
    void applyEffectToCharacter(Character *character) override;
    
    // 获取实体类型
    QString getEntityType() const override { return "Platform"; }
    
    // 检查角色是否站在平台上
    bool isCharacterOnPlatform(Character *character) const;
    
    // 设置平台类型
    void setPlatformType(PlatformType type);
    PlatformType getPlatformType() const { return platformType; }
    
    // 设置平台位置（用于纹理选择）
    void setPlatformPosition(int x, int totalWidth);
    int getPlatformPosition() const { return platformPosition; }
    
    // 设置平台属性（向后兼容）
    void setSpeedMultiplier(qreal multiplier) { speedMultiplier = multiplier; }
    qreal getSpeedMultiplier() const { return speedMultiplier; }

private:
    PlatformType platformType = GRASS; // 平台类型
    int platformPosition = 0;   // 平台在草地中的位置 (0=左, 1=中, 2=右)
    qreal speedMultiplier = 2.0; // 速度倍数
    void updateTexture();
}; 
