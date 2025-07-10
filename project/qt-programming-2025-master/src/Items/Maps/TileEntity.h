//
// Created by gerw on 8/21/24.
//

#ifndef QT_PROGRAMMING_2024_TILEENTITY_H
#define QT_PROGRAMMING_2024_TILEENTITY_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include "../Characters/Character.h"

class TileEntity : public QGraphicsItem {
public:
    explicit TileEntity(QGraphicsItem *parent = nullptr);
    
    // 基础碰撞检测
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    
    // 碰撞检测
    virtual bool collidesWith(const QRectF &rect) const;
    
    // 获取碰撞箱
    virtual QRectF getCollisionRect() const;
    
    // 对角色施加效果（由子类实现）
    virtual void applyEffectToCharacter(Character *character);
    
    // 获取实体类型
    virtual QString getEntityType() const { return "TileEntity"; }
    
    // 设置和获取纹理
    void setTexture(const QString &texturePath);
    QPixmap getTexture() const;

protected:
    QGraphicsPixmapItem *pixmapItem;
    static const int TILE_SIZE = 64; // 64x64像素
};

#endif //QT_PROGRAMMING_2024_TILEENTITY_H 