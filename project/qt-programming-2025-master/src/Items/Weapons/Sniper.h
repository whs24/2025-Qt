#ifndef SNIPER_H
#define SNIPER_H

#include "Gun.h"

class Sniper : public Gun {
    Q_OBJECT
public:
    explicit Sniper(QGraphicsItem* parent = nullptr);
    QString getWeaponType() const override { return "Sniper"; }
    qreal getWeaponScale() const override { return 1.0; }
    qreal getAttackDistance() const override { return 0; }
    qreal getAttackOffsetY() const override { return 0; }
    qreal getDefaultOffsetY() const override { return 60; }
    int getDamage() const override { return 40; }
    bool isVisibleByDefault() const override { return true; }
    void shoot(bool facingRight) override;
    void attack() override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override {
        if (!weaponPixmap.isNull()) {
            qreal scale = getWeaponScale();
            if (facingRight) {
                return QRectF(-70, 0, weaponPixmap.width() * scale, weaponPixmap.height() * scale);
            } else {
                return QRectF(0, 0, weaponPixmap.width() * scale, weaponPixmap.height() * scale);
            }
        }
        if (facingRight) return QRectF(-70, 0, 60, 20);
        return QRectF(0, 0, 60, 20);
    }
private:
    void loadWeaponPixmaps() override;
};

#endif // SNIPER_H 