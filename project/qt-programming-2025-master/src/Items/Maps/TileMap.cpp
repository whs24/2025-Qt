//
// Created by gerw on 8/21/24.
//

#include "TileMap.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "Platform.h"
#include "../Characters/Character.h"

TileMap::TileMap(QGraphicsItem *parent) : QGraphicsItem(parent) {
    initializeMap();
    createEmptyMap();
}

QRectF TileMap::boundingRect() const {
    return QRectF(0, 0, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE);
}

void TileMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    // 绘制背景图片（等比例填充）
    QPixmap backgroundPixmap(":/Items/Maps/Battlefield/background.png");
    if (!backgroundPixmap.isNull()) {
        painter->drawPixmap(boundingRect(), backgroundPixmap, backgroundPixmap.rect());
    } else {
        // 如果背景图片加载失败，绘制纯色背景
        painter->fillRect(boundingRect(), QColor(135, 206, 235)); // 天蓝色背景
    }
    
    // 根据mapData数组绘制地图实体
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            int tileType = mapData[y][x];
            if (tileType > 0) { // 有实体
                QPointF pixelPos = gridToPixel(x, y);
                QRectF tileRect(pixelPos, QSizeF(TILE_SIZE, TILE_SIZE));
                
                // 根据类型选择纹理
                QString texturePath;
                switch (tileType) {
                    case 1:
                        texturePath = ":/Items/Maps/Tile/Platform/grass/1.png";
                        break;
                    case 2:
                        texturePath = ":/Items/Maps/Tile/Platform/grass/2.png";
                        break;
                    case 3:
                        texturePath = ":/Items/Maps/Tile/Platform/grass/3.png";
                        break;
                    case 4:
                        texturePath = ":/Items/Maps/Tile/Platform/bush/bush.png";
                        break;
                    case 5:
                        texturePath = ":/Items/Maps/Tile/Platform/snow/1.png";
                        break;
                    case 6:
                        texturePath = ":/Items/Maps/Tile/Platform/snow/2.png";
                        break;
                    case 7:
                        texturePath = ":/Items/Maps/Tile/Platform/snow/3.png";
                        break;
                    default:
                        texturePath = ":/Items/Maps/Tile/Platform/grass/1.png";
                        break;
                }
                
                QPixmap texture(texturePath);
                if (!texture.isNull()) {
                    painter->drawPixmap(tileRect, texture, texture.rect());
                } else {
                    // 如果纹理加载失败，绘制绿色矩形
                    painter->fillRect(tileRect, QColor(34, 139, 34)); // 绿色
                }
                
                // 绘制地图实体碰撞箱可视化（蓝色线条）
                painter->setPen(QPen(Qt::blue, 2));
                painter->setBrush(Qt::NoBrush);
                painter->drawRect(tileRect);
            }
        }
    }
    
    // 可选：绘制网格线（调试用）
    // painter->setPen(QPen(Qt::black, 1));
    // for (int x = 0; x <= MAP_WIDTH; ++x) {
    //     painter->drawLine(x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE);
    // }
    // for (int y = 0; y <= MAP_HEIGHT; ++y) {
    //     painter->drawLine(0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE);
    // }
}

void TileMap::initializeMap() {
    tiles.resize(MAP_WIDTH);
    for (int x = 0; x < MAP_WIDTH; ++x) {
        tiles[x].resize(MAP_HEIGHT);
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            tiles[x][y] = nullptr;
        }
    }
}

void TileMap::setTile(int x, int y, TileEntity *entity) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        qDebug() << "Invalid tile coordinates:" << x << y;
        return;
    }
    
    // 清除旧的实体
    if (tiles[x][y]) {
        delete tiles[x][y];
    }
    
    tiles[x][y] = entity;
    if (entity) {
        entity->setPos(gridToPixel(x, y));
    }
}

TileEntity* TileMap::getTile(int x, int y) const {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return nullptr;
    }
    return tiles[x][y];
}

void TileMap::clearTile(int x, int y) {
    setTile(x, y, nullptr);
}

QPointF TileMap::gridToPixel(int gridX, int gridY) {
    return QPointF(gridX * TILE_SIZE, gridY * TILE_SIZE);
}

QPoint TileMap::pixelToGrid(const QPointF &pixelPos) {
    return QPoint(static_cast<int>(pixelPos.x() / TILE_SIZE), 
                  static_cast<int>(pixelPos.y() / TILE_SIZE));
}

bool TileMap::checkCollision(const QRectF &rect) const {
    // 检查与所有实体的碰撞
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            if ((mapData[y][x] > 0)&& (mapData[y][x] !=4)) { // 有实体
                // 计算实体的实际碰撞箱（基于图片边界）
                QPointF pixelPos = gridToPixel(x, y);
                QRectF tileRect(pixelPos, QSizeF(TILE_SIZE, TILE_SIZE));
                
                // 这里可以进一步优化，根据实际的grass图片边界来调整碰撞箱
                // 暂时使用整个格子作为碰撞箱
                if (tileRect.intersects(rect)) {
                    return true;
                }
            }
        }
    }
    return false;
}

Platform* TileMap::getPlatformUnderCharacter(Character* character) const {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            auto* platform = dynamic_cast<Platform*>(getTile(x, y));
            if (platform && platform->sceneBoundingRect().intersects(character->sceneBoundingRect())) {
                return platform;
            }
        }
    }
    return nullptr;
}

void TileMap::applyEffectsToCharacter(Character* character) {
    character->setSpeedMultiplier(1.0); // 先重置
    character->setInvisible(false);     // 先重置
    Platform* platform = getPlatformUnderCharacter(character);
    if (platform) {
        platform->applyEffectToCharacter(character);
    }
}

void TileMap::createEmptyMap() {
    // 创建空地图
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            clearTile(x, y);
        }
    }
}

void TileMap::createTestMap() {
    // 创建测试地图
    createEmptyMap();
    
    // 创建底部地面 - 草地平台
    for (int x = 0; x < MAP_WIDTH; ++x) {
        Platform *ground = new Platform(this);
        ground->setPlatformType(GRASS);
        ground->setPlatformPosition(x, MAP_WIDTH);
        setTile(x, MAP_HEIGHT - 1, ground);
    }
    
    // 创建悬浮平台区域1 - 草地平台
    for (int x = 5; x <= 8; ++x) {
        Platform *platform = new Platform(this);
        platform->setPlatformType(GRASS);
        platform->setPlatformPosition(x - 5, 4); // 4个平台的区域
        setTile(x, MAP_HEIGHT - 4, platform);
    }
    
    // 创建悬浮平台区域2 - 草地平台
    for (int x = 12; x <= 15; ++x) {
        Platform *platform = new Platform(this);
        platform->setPlatformType(GRASS);
        platform->setPlatformPosition(x - 12, 4); // 4个平台的区域
        setTile(x, MAP_HEIGHT - 6, platform);
    }
    
    // 创建悬浮平台区域3 - 草地平台
    for (int x = 2; x <= 4; ++x) {
        Platform *platform = new Platform(this);
        platform->setPlatformType(GRASS);
        platform->setPlatformPosition(x - 2, 3); // 3个平台的区域
        setTile(x, MAP_HEIGHT - 8, platform);
    }
    
    // 创建高处平台 - 草地平台
    for (int x = 16; x <= 18; ++x) {
        Platform *platform = new Platform(this);
        platform->setPlatformType(GRASS);
        platform->setPlatformPosition(x - 16, 3); // 3个平台的区域
        setTile(x, MAP_HEIGHT - 3, platform);
    }
}

void TileMap::saveMapToFile(const QString &filename) {
    QJsonObject mapData;
    QJsonArray tilesArray;
    
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            if (tiles[x][y]) {
                QJsonObject tileData;
                tileData["x"] = x;
                tileData["y"] = y;
                tileData["type"] = tiles[x][y]->getEntityType();
                
                if (auto platform = dynamic_cast<Platform*>(tiles[x][y])) {
                    tileData["speedMultiplier"] = platform->getSpeedMultiplier();
                }
                
                tilesArray.append(tileData);
            }
        }
    }
    
    mapData["tiles"] = tilesArray;
    
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(mapData).toJson());
    }
}

void TileMap::loadMapFromFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open map file:" << filename;
        return;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject mapData = doc.object();
    QJsonArray tilesArray = mapData["tiles"].toArray();
    
    createEmptyMap();
    
    for (const QJsonValue &value : tilesArray) {
        QJsonObject tileData = value.toObject();
        int x = tileData["x"].toInt();
        int y = tileData["y"].toInt();
        QString type = tileData["type"].toString();
        
        if (type == "Platform") {
            Platform *platform = new Platform(this);
            platform->setSpeedMultiplier(tileData["speedMultiplier"].toDouble());
            setTile(x, y, platform);
        }
    }
}

// 地图数据操作方法实现
void TileMap::setMapData(int x, int y, int value) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        mapData[y][x] = value;
    }
}

int TileMap::getMapData(int x, int y) const {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return mapData[y][x];
    }
    return 0;
}

void TileMap::setMapDataArray(const int data[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            mapData[y][x] = data[y][x];
        }
    }
}

// 兼容性方法实现
qreal TileMap::getFloorHeight() {
    // 返回地图底部的高度
    return (MAP_HEIGHT - 1) * TILE_SIZE;
}

QPointF TileMap::getSpawnPos() {
    // 返回角色生成位置（地图中央底部上方一点）
    qreal midX = (MAP_WIDTH * TILE_SIZE) / 3.0;
    qreal spawnY = 768-200-60; // 底部平台上方一格再往上50像素
    return QPointF(midX, spawnY);
} 

