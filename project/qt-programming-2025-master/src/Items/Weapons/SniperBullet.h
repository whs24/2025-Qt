#ifndef SNIPERBULLET_H
#define SNIPERBULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include "../Characters/Character.h"

class SniperBullet : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    SniperBullet(QPointF startPos, bool facingRight, int damage, Character* owner, QGraphicsItem* parent = nullptr);
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

#endif // SNIPERBULLET_H 