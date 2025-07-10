//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_HEALTHHUD_H
#define QT_PROGRAMMING_2024_HEALTHHUD_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QString>

class HealthHUD : public QGraphicsItem {
public:
    explicit HealthHUD(QGraphicsItem *parent = nullptr);
    
    // 设置角色生命值
    void setGreenHealth(int health);
    void setRedHealth(int health);
    
    // 获取角色生命值
    int getGreenHealth() const { return greenHealth; }
    int getRedHealth() const { return redHealth; }
    
    // QGraphicsItem接口
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    
private:
    int greenHealth{100};
    int redHealth{100};
    
    // 素材
    QPixmap greenAvatar;
    QPixmap redAvatar;
    QPixmap heartIcon;
    QPixmap numberIcons[10]; // 0-9的数字图标
    
    // 绘制单个角色的生命值显示
    void drawCharacterHealth(QPainter *painter, const QPixmap &avatar, int health, int x, int y);
    
    // 将数字转换为图标显示
    void drawNumber(QPainter *painter, int number, int x, int y);
};

#endif //QT_PROGRAMMING_2024_HEALTHHUD_H 