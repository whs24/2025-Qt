#ifndef RIFLEBULLET_H
#define RIFLEBULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include "../Characters/Character.h"

class RifleBullet : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    RifleBullet(QPointF startPos, bool facingRight, int damage, Character* owner, QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithCharacter(Character *target) const;
    int getDamage() const { return damage; }
    Character* getOwner() const { return owner; }
public slots:
    void updatePosition();
private:
    QPointF position;
    QPointF velocity;
    int damage;
    bool active = true;
    QTimer *moveTimer;
    QPixmap bulletPixmap;
    Character* owner;
};

#endif // RIFLEBULLET_H 