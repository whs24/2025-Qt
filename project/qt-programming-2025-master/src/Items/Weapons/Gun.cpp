#include "Gun.h"
#include "../Characters/Character.h"
#include <QDebug>

Gun::Gun(int bulletCount, int intervalMs, QGraphicsItem* parent)
    : Weapon(parent), bullets(bulletCount), maxBullets(bulletCount), intervalMs(intervalMs) {
    intervalTimer = new QTimer(this);
    intervalTimer->setSingleShot(true);
    connect(intervalTimer, &QTimer::timeout, this, &Gun::onCooldownFinished);
}

void Gun::setOwner(Character* owner) {
    Weapon::setOwner(owner);
}

void Gun::startCooldown() {
    coolingDown = true;
    intervalTimer->start(intervalMs);
}

void Gun::onCooldownFinished() {
    coolingDown = false;
} 