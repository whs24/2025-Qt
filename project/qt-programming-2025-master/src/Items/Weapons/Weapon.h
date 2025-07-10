//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_WEAPON_H
#define QT_PROGRAMMING_2024_WEAPON_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

class Character;

class Weapon : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit Weapon(QGraphicsItem *parent = nullptr);
    
    // 获取武器类型（纯虚函数）
    virtual QString getWeaponType() const = 0;
    
    // 获取武器缩放比例（纯虚函数）
    virtual qreal getWeaponScale() const = 0;
    
    // 获取攻击距离（纯虚函数）
    virtual qreal getAttackDistance() const = 0;
    
    // 获取攻击时的垂直偏移（纯虚函数）
    virtual qreal getAttackOffsetY() const = 0;
    
    // 获取默认位置的垂直偏移（纯虚函数）
    virtual qreal getDefaultOffsetY() const = 0;
    
    // 获取武器伤害值（纯虚函数）
    virtual int getDamage() const = 0;
    
    // 是否在默认状态下可见（纯虚函数）
    virtual bool isVisibleByDefault() const = 0;
    
    // 攻击相关
    void startAttack(bool facingRight);
    void stopAttack();
    bool isAttacking() const { return attacking; }
    
    // 设置伤害值
    void setDamage(int damage) { this->damage = damage; }
    
    // 设置拥有者
    void setOwner(Character *owner) { this->owner = owner; }
    Character* getOwner() const { return owner; }
    
    // 碰撞检测
    bool collidesWithCharacter(Character *target) const;
    
    // QGraphicsItem接口
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    
    // 更新武器位置和朝向
    void updatePosition(bool facingRight, bool isDucking);
    
    virtual void attack();
    virtual void update();
    
    // 掉落物理属性
    void setFalling(bool falling) { isFalling = falling; }
    bool getFalling() const { return isFalling; }
    void setVelocity(const QPointF &v) { velocity = v; }
    QPointF getVelocity() const { return velocity; }
    void fallUpdate(const QList<QGraphicsItem*>& platforms, qreal gravity = 0.08, qreal maxFallSpeed = 1.5);
    
private slots:
    void onAttackFinished();
    
protected:
    bool attacking{false};
    bool facingRight{true};
    int damage{5};
    Character *owner{nullptr};
    
    // 攻击冷却机制
    bool hasDealtDamage{false};
    
    // 武器图片
    QPixmap weaponPixmap;
    
    // 攻击计时器
    QTimer *attackTimer;
    
    // 加载武器图片（纯虚函数）
    virtual void loadWeaponPixmaps() = 0;
    
    // 计算武器位置
    virtual QPointF calculateWeaponPosition(bool facingRight, bool isDucking) const;
    QRectF calculateWeaponRect(bool facingRight, bool isDucking) const;
    
    QPointF velocity{0, 0};
    bool isFalling{false};
};

#endif //QT_PROGRAMMING_2024_WEAPON_H 
