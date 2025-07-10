//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_RED_H
#define QT_PROGRAMMING_2024_RED_H


#include "Character.h"

class Red : public Character {
public:
    explicit Red(QGraphicsItem *parent = nullptr, const QString &characterPixmapPath = "");

    
    // 重写动画帧加载函数
    void loadAnimationFrames() override;
    void setInitialFrame() override;
    
    // 重写绘制方法，显示不同颜色的碰撞箱
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    
    // AI控制预留函数
    void setAIEnabled(bool enabled);
    bool isAIEnabled() const;
    void updateAI();
    
    
private:
    bool aiEnabled{false};
};


#endif //QT_PROGRAMMING_2024_RED_H 
