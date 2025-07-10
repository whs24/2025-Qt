#ifndef RIFLE_H
#define RIFLE_H

#include "Gun.h"

class Rifle : public Gun {
    Q_OBJECT
public:
    explicit Rifle(QGraphicsItem* parent = nullptr);
    QString getWeaponType() const override { return "Rifle"; }
    QRectF boundingRect() const override {
        if (!weaponPixmap.isNull()) {
            qreal scale = getWeaponScale();
            if (facingRight) {
                return QRectF(-30, 0, weaponPixmap.width() * scale, weaponPixmap.height() * scale);
            } else {
                return QRectF(0, 0, weaponPixmap.width() * scale, weaponPixmap.height() * scale);
            }
        }
        return QRectF(0, 0, 60, 20);
    }
    qreal getWeaponScale() const override { return 1.0; }
    qreal getAttackDistance() const override { return 0; }
    qreal getAttackOffsetY() const override { return 0; }
    qreal getDefaultOffsetY() const override { return 60; }
    int getDamage() const override { return 12; }
    bool isVisibleByDefault() const override { return true; }
    void shoot(bool facingRight) override;
    void attack() override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    void loadWeaponPixmaps() override;
};

#endif // RIFLE_H 