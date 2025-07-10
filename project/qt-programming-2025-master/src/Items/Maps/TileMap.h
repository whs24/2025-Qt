//
// Created by gerw on 8/21/24.
//

#ifndef QT_PROGRAMMING_2024_TILEMAP_H
#define QT_PROGRAMMING_2024_TILEMAP_H

#include <QGraphicsItem>
#include <QVector>
#include <QPainter>
#include "TileEntity.h"
#include "Platform.h"

class TileMap : public QGraphicsItem {
public:
    static const int MAP_WIDTH = 20;   // 20列
    static const int MAP_HEIGHT = 12;  // 12行
    static const int TILE_SIZE = 64;   // 64x64像素
    
    explicit TileMap(QGraphicsItem *parent = nullptr);
    
    // 基础绘图功能
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    
    // 地图操作
    void setTile(int x, int y, TileEntity *entity);
    TileEntity* getTile(int x, int y) const;
    void clearTile(int x, int y);
    
    // 从网格坐标转换为像素坐标
    static QPointF gridToPixel(int gridX, int gridY);
    static QPoint pixelToGrid(const QPointF &pixelPos);
    
    // 碰撞检测
    bool checkCollision(const QRectF &rect) const;
    
    // 对角色应用所有实体的效果
    void applyEffectsToCharacter(Character *character);
    
    // 创建预设地图
    void createEmptyMap();
    void createTestMap(); // 创建测试地图
    
    // 保存和加载地图
    void saveMapToFile(const QString &filename);
    void loadMapFromFile(const QString &filename);
    
    // 地图数据操作
    void setMapData(int x, int y, int value);
    int getMapData(int x, int y) const;
    void setMapDataArray(const int data[MAP_HEIGHT][MAP_WIDTH]);
    
    // 兼容性方法（为了与原有Map类兼容）
    virtual qreal getFloorHeight();
    virtual QPointF getSpawnPos();

    Platform* getPlatformUnderCharacter(Character* character) const;

private:
    QVector<QVector<TileEntity*>> tiles; // 20x12的网格
    QPixmap backgroundTexture;
    
    // 简单的地图数据数组：0=空，1-3=草地平台，4=灌木丛，5-7=雪地平台
    int mapData[MAP_HEIGHT][MAP_WIDTH] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 第0行
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 第1行
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 第2行
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 第3行
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 第4行
        {0,1,2,2,3,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0}, // 第5行
        {0,0,0,0,0,0,0,0,0,1,2,3,0,0,0,0,0,0,0,0}, // 第6行
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 第7行
        {0,0,0,5,6,7,0,0,0,0,0,0,0,0,0,1,3,0,0,0}, // 第8行
        {0,0,0,0,0,0,0,0,0,1,2,3,0,0,0,0,0,0,0,0}, // 第9行
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 第10行
        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3}  // 第11行（最底下一行）
    };
    
    // 初始化地图
    void initializeMap();
};

#endif //QT_PROGRAMMING_2024_TILEMAP_H 
