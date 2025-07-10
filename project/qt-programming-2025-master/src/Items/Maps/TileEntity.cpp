//
// Created by gerw on 8/21/24.
//

#include "TileEntity.h"
#include <QDebug>

TileEntity::TileEntity(QGraphicsItem *parent) : QGraphicsItem(parent), pixmapItem(nullptr) {
    // 设置默认大小
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

QRectF TileEntity::boundingRect() const {
    if (pixmapItem != nullptr) {
        return pixmapItem->boundingRect();
    }
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
}

void TileEntity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    if (pixmapItem != nullptr) {
        // 绘制纹理
        painter->drawPixmap(0, 0, pixmapItem->pixmap());
    } else {
        // 如果没有纹理，绘制一个默认的矩形
        painter->setPen(QPen(Qt::gray, 1));
        painter->setBrush(QBrush(Qt::lightGray));
        painter->drawRect(0, 0, TILE_SIZE, TILE_SIZE);
    }
}

bool TileEntity::collidesWith(const QRectF &rect) const {
    return boundingRect().intersects(rect);
}

QRectF TileEntity::getCollisionRect() const {
    // 返回实体图片的实际边界作为碰撞箱
    if (pixmapItem && !pixmapItem->pixmap().isNull()) {
        return pixmapItem->boundingRect();
    }
    // 如果没有图片，返回默认边界
    return boundingRect();
}

void TileEntity::applyEffectToCharacter(Character *character) {
    // 基础类不施加任何效果
    Q_UNUSED(character)
}

void TileEntity::setTexture(const QString &texturePath) {
    if (pixmapItem) {
        delete pixmapItem;
    }
    
    if (!texturePath.isEmpty()) {
        pixmapItem = new QGraphicsPixmapItem(this);
        QPixmap pixmap(texturePath);
        if (!pixmap.isNull()) {
            pixmapItem->setPixmap(pixmap.scaled(TILE_SIZE, TILE_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to load texture:" << texturePath;
        }
    }
}

QPixmap TileEntity::getTexture() const {
    if (pixmapItem) {
        return pixmapItem->pixmap();
    }
    return QPixmap();
} 