//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"
#include "../Weapons/Weapon.h"
#include "../Weapons/Fist.h"
#include "../Weapons/Sword.h"
#include "../Weapons/SolidBall.h"

class Character : public Item {
public:
    explicit Character(QGraphicsItem *parent, const QString &characterPixmapPath = "");

    [[nodiscard]] bool isLeftDown() const;

    void setLeftDown(bool leftDown);

    [[nodiscard]] bool isRightDown() const;

    void setRightDown(bool rightDown);

    [[nodiscard]] bool isPickDown() const;

    void setPickDown(bool pickDown);

    [[nodiscard]] bool isDuckDown() const;

    void setDuckDown(bool duckDown);

    [[nodiscard]] bool isJumpDown() const;

    void setJumpDown(bool jumpDown);

    [[nodiscard]] const QPointF &getVelocity() const;

    [[nodiscard]] bool isPicking() const;

    void setVelocity(const QPointF &velocity);

    void processInput();

    Armor* pickupArmor(Armor* newArmor);

    // 碰撞检测方法
    [[nodiscard]] bool collidesWith(const QGraphicsItem *other) const;
    [[nodiscard]] bool collidesWithMap() const;
    [[nodiscard]] QRectF getCollisionRect() const;

    // 简化的动画方法
    void updateAnimation();

    // 跳跃状态控制
    void setJumping(bool jumping);
    void setJumpCount(int count);

    // 生命值相关方法
    void setHealth(int health);
    int getHealth() const { return health; }
    void takeDamage(int damage);
    void heal(int amount);
    bool isAlive() const { return health > 0; }

    // 攻击相关方法
    void setAttackDown(bool attackDown);
    bool isAttackDown() const { return attackDown; }
    void processAttack();
    void takeHit();
    bool isHit() const { return isHitState; }
    
    // 武器相关方法
    void setWeapon(Weapon *weapon);
    Weapon* getWeapon() const { return currentWeapon; }
    void equipSword();
    void equipFist();
    void equipSolidBall();
    void equipRifle();
    void equipSniper();

    // 重写绘制方法
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void setInvisible(bool val);
    bool isInvisible() const;
    void setSpeedMultiplier(qreal multiplier);
    qreal getSpeedMultiplier() const;
    qreal getCurrentSpeed() const;
    bool isCrouching() const;
    bool getIsWalkingRight() const { return isWalkingRight; }
    bool isJumping() const { return _isJumping; }

protected:
    HeadEquipment *headEquipment{};
    LegEquipment *legEquipment{};
    Armor *armor{};
    QPointF velocity{};
    
    // 生命值
    int health{100};
    int maxHealth{100};
    
    // 攻击状态
    bool attackDown{false};
    bool lastAttackDown{false};
    bool isHitState{false};
    int hitAnimationCounter{0};
    
    // 武器
    Weapon *currentWeapon{nullptr};
    
    // 简单的动画状态
    bool isWalking{false};
    bool isWalkingRight{true};
    bool isDucking{false};
    bool _isJumping{false};
    bool isDoubleJumping{false}; // 二段跳状态
    int jumpCount{0}; // 跳跃次数：0=地面，1=第一段跳，2=第二段跳
    int animationFrame{0};
    int animationCounter{0};
    
    // 动画帧
    QPixmap idleFrame;
    QPixmap walkFrame1;
    QPixmap walkFrame2;
    QPixmap duckFrame;
    QPixmap jumpFrame;
    QPixmap hitFrame;
    
    // 虚函数，让子类重写动画帧加载
    virtual void loadAnimationFrames();
    virtual void setInitialFrame();

    qreal baseSpeed = 5.0;
    qreal speedMultiplier = 1.0;
    bool invisible = false;

private:
    bool leftDown{}, rightDown{}, pickDown{}, duckDown{}, jumpDown{};
    bool lastPickDown{};
    bool lastJumpDown{};
    bool picking{};

    void updateTexture();
};


#endif //QT_PROGRAMMING_2024_CHARACTER_H
