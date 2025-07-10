//
// Created by gerw on 8/20/24.
//

#include <QDebug>
#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Characters/Red.h"
#include "../Items/Maps/TileMap.h"
#include "../Items/Maps/Platform.h"
#include "../Items/Armors/FlamebreakerArmor.h"
#include "../Items/HealthHUD.h"
#include "../Items/Weapons/SolidBallProjectile.h"
#include "../Items/Weapons/RifleBullet.h"
#include "../Items/Weapons/SniperBullet.h"
#include <QTimer>
#include "../Items/Weapons/Sword.h"
#include "../Items/Weapons/Rifle.h"
#include "../Items/Weapons/Sniper.h"
#include "../Items/Weapons/Fist.h"
#include "../Items/Weapons/SolidBall.h"
#include <QRandomGenerator>

std::vector<std::pair<QString, double>> weaponProbTable = {
    {"Sword", 0.3},
    {"Rifle", 0.25},
    {"Sniper", 0.25},
    {"SolidBall", 0.2}
};

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 768);
    map = new TileMap();

    // 创建第一个角色（Link）
    character1 = new Link(nullptr, ":/Items/Characters/Link/green.png");

    // 创建第二个角色（Red）
    character2 = new Red(nullptr, ":/Items/Characters/Red/Red.png");

    // 创建生命值HUD
    healthHUD = new HealthHUD();

    spareArmor = new FlamebreakerArmor();
    addItem(map);
    addItem(character1);
    addItem(character2);
    addItem(healthHUD);
    // addItem(spareArmor);

    // 创建测试地图
    // map->createTestMap();

    // 设置角色初始位置
    QPointF spawnPos = map->getSpawnPos();
    character1->setPos(spawnPos);
    // 第二个角色放在右边300像素的位置
    character2->setPos(spawnPos + QPointF(320, 0));

    // 初始化武器
    // character2->equipSniper(); // 左侧角色默认装备拳头
    // character1->equipRifle(); // 右侧角色默认装备剑
    character1->equipFist();
    character2->equipFist();
    // 初始化武器生成定时器
    weaponSpawnTimer = new QTimer(this);
    connect(weaponSpawnTimer, &QTimer::timeout, this, &BattleScene::spawnRandomWeapon);
    weaponSpawnTimer->start(weaponSpawnInterval);

    // 初始化生命值HUD
    updateHealthHUD();

    // 输出调试信息
    qDebug() << "BattleScene initialized";
    qDebug() << "Map size:" << map->boundingRect();
    qDebug() << "Character1 spawn position:" << spawnPos;
    qDebug() << "Character2 spawn position:" << (spawnPos + QPointF(300, 0));
    qDebug() << "Floor height:" << map->getFloorHeight();
    // spareArmor->unmount();
    // spareArmor->setPos(sceneRect().left() + (sceneRect().right() - sceneRect().left()) * 0.75, map->getFloorHeight());
}

void BattleScene::processInput() {
    if (gameEnded) return; // 结束后不再处理输入
    Scene::processInput();
    if (character1 != nullptr) {
        character1->processInput();
        character1->updateAnimation();
        if (character1->getWeapon()) {
            character1->getWeapon()->update();
        }
    }
    if (character2 != nullptr) {
        character2->processInput();
        character2->updateAnimation();
        character2->updateAI();
        if (character2->getWeapon()) {
            character2->getWeapon()->update();
        }
    }
    processAttackDetection();
    updateHealthHUD();
}

void BattleScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        // 第一个角色的控制（WASD）
        case Qt::Key_A:
            if (character1 != nullptr) {
                character1->setLeftDown(true);
            }
            break;
        case Qt::Key_D:
            if (character1 != nullptr) {
                character1->setRightDown(true);
            }
            break;
        case Qt::Key_S:
            if (character1 != nullptr) {
                // 互斥：跳跃时不能下蹲
                if (!character1->isJumpDown() && !character1->isJumping()) {
                    character1->setDuckDown(true);
                }
                character1->setPickDown(true);
            }
            break;
        case Qt::Key_W:
            if (character1 != nullptr) {
                // 互斥：下蹲时不能跳跃
                if (!character1->isDuckDown()) {
                    character1->setJumpDown(true);
                }
            }
            break;
        case Qt::Key_F:
            if (character1 != nullptr) {
                character1->setAttackDown(true);
            }
            break;

        // 第二个角色的控制（小键盘）
        case Qt::Key_Left:
            if (character2 != nullptr) {
                character2->setLeftDown(true);
            }
            break;
        case Qt::Key_Right:
            if (character2 != nullptr) {
                character2->setRightDown(true);
            }
            break;
        case Qt::Key_Down:
            if (character2 != nullptr) {
                // 互斥：跳跃时不能下蹲
                if (!character2->isJumpDown() && !character2->isJumping()) {
                    character2->setDuckDown(true);
                }
                character2->setPickDown(true);
            }
            break;
        case Qt::Key_Up:
            if (character2 != nullptr) {
                // 互斥：下蹲时不能跳跃
                if (!character2->isDuckDown()) {
                    character2->setJumpDown(true);
                }
            }
            break;
        case Qt::Key_0:
            if (character2 != nullptr) {
                character2->setAttackDown(true);
            }
            break;

        // 生命值测试功能
        case Qt::Key_1:
            // 减少绿色角色生命值
            if (character1 != nullptr) {
                character1->takeDamage(10);
                qDebug() << "Green character health:" << character1->getHealth();
            }
            break;
        case Qt::Key_2:
            // 增加绿色角色生命值
            if (character1 != nullptr) {
                character1->heal(10);
                qDebug() << "Green character health:" << character1->getHealth();
            }
            break;
        case Qt::Key_3:
            // 减少红色角色生命值
            if (character2 != nullptr) {
                character2->takeDamage(10);
                qDebug() << "Red character health:" << character2->getHealth();
            }
            break;
        case Qt::Key_4:
            // 增加红色角色生命值
            if (character2 != nullptr) {
                character2->heal(10);
                qDebug() << "Red character health:" << character2->getHealth();
            }
            break;
        default:
            Scene::keyPressEvent(event);
    }
}

void BattleScene::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        // 第一个角色的控制（WASD）
        case Qt::Key_A:
            if (character1 != nullptr) {
                character1->setLeftDown(false);
            }
            break;
        case Qt::Key_D:
            if (character1 != nullptr) {
                character1->setRightDown(false);
            }
            break;
        case Qt::Key_S:
            if (character1 != nullptr) {
                character1->setDuckDown(false);
                character1->setPickDown(false);
            }
            break;
        case Qt::Key_W:
            if (character1 != nullptr) {
                character1->setJumpDown(false);
            }
            break;
        case Qt::Key_F:
            if (character1 != nullptr) {
                character1->setAttackDown(false);
            }
            break;

        // 第二个角色的控制（小键盘）
        case Qt::Key_Left:
            if (character2 != nullptr) {
                character2->setLeftDown(false);
            }
            break;
        case Qt::Key_Right:
            if (character2 != nullptr) {
                character2->setRightDown(false);
            }
            break;
        case Qt::Key_Down:
            if (character2 != nullptr) {
                character2->setDuckDown(false);
                character2->setPickDown(false);
            }
            break;
        case Qt::Key_Up:
            if (character2 != nullptr) {
                character2->setJumpDown(false);
            }
            break;
        case Qt::Key_0:
            if (character2 != nullptr) {
                character2->setAttackDown(false);
            }
            break;
        default:
            Scene::keyReleaseEvent(event);
    }
}

void BattleScene::update() {
    if (gameEnded) return; // 已经结束就不再判定和处理
    Scene::update();
    updateFallingWeapons();
    if (character1 && character1->getHealth() <= 0) {
        gameEnded = true;
        emit player2Win();
        return;
    } else if (character2 && character2->getHealth() <= 0) {
        gameEnded = true;
        emit player1Win();
        return;
    }
    // 其它 update 逻辑...
}

void BattleScene::processMovement() {
    if (gameEnded) return; // 结束后不再处理移动
    Scene::processMovement();
    if (character1 != nullptr) {
        processCharacterMovement(character1);
    }
    if (character2 != nullptr) {
        processCharacterMovement(character2);
    }
}

void BattleScene::processCharacterMovement(Character *character) {
    // 应用地图实体的效果（先于移动）
    map->applyEffectsToCharacter(character);
    // 计算新位置
    QPointF newPos = character->pos() + character->getVelocity() * (double) deltaTime;

    // 边界检测：防止角色走出窗口范围
    QRectF characterRect = character->getCollisionRect();
    QRectF sceneRect = this->sceneRect();

    // 限制X轴范围
    if (newPos.x() + characterRect.left() < sceneRect.left()) {
        newPos.setX(sceneRect.left() - characterRect.left());
    }
    if (newPos.x() + characterRect.right() > sceneRect.right()) {
        newPos.setX(sceneRect.right() - characterRect.right());
    }

    // 限制Y轴范围
    if (newPos.y() + characterRect.top() < sceneRect.top()) {
        newPos.setY(sceneRect.top() - characterRect.top());
    }
    if (newPos.y() + characterRect.bottom() > sceneRect.bottom()) {
        newPos.setY(sceneRect.bottom() - characterRect.bottom());
    }

    // 检查与地图的碰撞，使用角色的实际碰撞箱
    characterRect.translate(newPos);
    bool hasCollision = map->checkCollision(characterRect);

    if (!hasCollision) {
        // 没有碰撞，更新位置
        character->setPos(newPos);
    } else {
        // 有碰撞，分别检查X和Y轴移动
        QPointF horizontalOnly = character->pos();
        horizontalOnly.setX(newPos.x());
        QRectF horizontalRect = character->getCollisionRect();
        horizontalRect.translate(horizontalOnly);

        if (!map->checkCollision(horizontalRect)) {
            character->setPos(horizontalOnly);
        }

        QPointF verticalOnly = character->pos();
        verticalOnly.setY(newPos.y());
        QRectF verticalRect = character->getCollisionRect();
        verticalRect.translate(verticalOnly);

        if (!map->checkCollision(verticalRect)) {
            character->setPos(verticalOnly);
        } else {
            // 垂直方向也有碰撞，说明角色落地了
            if (character->getVelocity().y() > 0) {
                // 重置跳跃状态和Y速度
                character->setVelocity(QPointF(character->getVelocity().x(), 0));
                // 直接重置跳跃状态，确保动画恢复
                character->setJumping(false);
                character->setJumpCount(0);
            }
        }
    }
}

void BattleScene::processPicking() {
    if (gameEnded) return; // 结束后不再处理拾取
    Scene::processPicking();
    qDebug() << "[PICK-STATE] c1 isPicking:" << character1->isPicking() << ", isDuckDown:" << character1->isDuckDown();
    qDebug() << "[PICK-STATE] c2 isPicking:" << character2->isPicking() << ", isDuckDown:" << character2->isDuckDown();
    // 角色1拾取武器
    if (character1->isPicking() && character1->isDuckDown()) {
        for (QGraphicsItem* item : items()) {
            Weapon* weapon = dynamic_cast<Weapon*>(item);
            if (weapon && weapon->parentItem() == nullptr) {
                QRectF cRect = character1->sceneBoundingRect();
                QRectF wRect = weapon->sceneBoundingRect();
                bool intersect = cRect.intersects(wRect);
                qDebug() << "[PICK1] cRect:" << cRect << ", wRect:" << wRect << ", intersect:" << intersect;
                if (intersect) {
                    qDebug() << "[PICK1] 拾取武器:" << weapon->getWeaponType();
                    QString type = weapon->getWeaponType();
                    removeItem(weapon);
                    delete weapon;
                    Weapon* newWeapon = nullptr;
                    if (type == "Sword") newWeapon = new Sword();
                    else if (type == "Rifle") newWeapon = new Rifle();
                    else if (type == "Sniper") newWeapon = new Sniper();
                    else if (type == "SolidBall") newWeapon = new SolidBall();
                    if (newWeapon) {
                        character1->setWeapon(newWeapon);
                    } else {
                        qDebug() << "[ERROR] newWeapon is nullptr, type=" << type;
                    }
                    break;
                }
            }
        }
    }
    // 角色2同理
    if (character2->isPicking() && character2->isDuckDown()) {
        for (QGraphicsItem* item : items()) {
            Weapon* weapon = dynamic_cast<Weapon*>(item);
            if (weapon && weapon->parentItem() == nullptr) {
                QRectF cRect = character2->sceneBoundingRect();
                QRectF wRect = weapon->sceneBoundingRect();
                bool intersect = cRect.intersects(wRect);
                qDebug() << "[PICK2] cRect:" << cRect << ", wRect:" << wRect << ", intersect:" << intersect;
                if (intersect) {
                    qDebug() << "[PICK2] 拾取武器:" << weapon->getWeaponType();
                    QString type = weapon->getWeaponType();
                    removeItem(weapon);
                    delete weapon;
                    Weapon* newWeapon = nullptr;
                    if (type == "Sword") newWeapon = new Sword();
                    else if (type == "Rifle") newWeapon = new Rifle();
                    else if (type == "Sniper") newWeapon = new Sniper();
                    else if (type == "SolidBall") newWeapon = new SolidBall();
                    if (newWeapon) {
                        character2->setWeapon(newWeapon);
                    } else {
                        qDebug() << "[ERROR] newWeapon is nullptr, type=" << type;
                    }
                    break;
                }
            }
        }
    }
    // 盔甲拾取逻辑保持不变
    if (character1->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character1->pos(), 100.);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character1, mountable));
        }
    }
    if (character2->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character2->pos(), 100.);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character2, mountable));
        }
    }
}

Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold) {
    Mountable *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem *item: items()) {
        if (auto mountable = dynamic_cast<Mountable *>(item)) {
            if (!mountable->isMounted()) {
                qreal distance = QLineF(pos, item->pos()).length();
                if (distance < minDistance) {
                    minDistance = distance;
                    nearest = mountable;
                }
            }
        }
    }

    return nearest;
}

Mountable *BattleScene::pickupMountable(Character *character, Mountable *mountable) {
    // Limitation: currently only supports armor
    if (auto armor = dynamic_cast<Armor *>(mountable)) {
        return character->pickupArmor(armor);
    }
    return nullptr;
}

void BattleScene::updateHealthHUD() {
    if (healthHUD != nullptr) {
        if (character1 != nullptr) {
            healthHUD->setGreenHealth(character1->getHealth());
        }
        if (character2 != nullptr) {
            healthHUD->setRedHealth(character2->getHealth());
        }
    }
}

void BattleScene::processAttackDetection() {
    // 调试输出当前武器类型
    if (character1 && character1->getWeapon()) {
        qDebug() << "[DEBUG] processAttackDetection character1 weapon type:" << character1->getWeapon()->getWeaponType();
    }
    if (character2 && character2->getWeapon()) {
        qDebug() << "[DEBUG] processAttackDetection character2 weapon type:" << character2->getWeapon()->getWeaponType();
    }

    // 只检测攻击结果，不直接调用attack()
    // 检查角色1的攻击
    if (character1 && character1->getWeapon()) {
        if (character1->getWeapon()->getWeaponType() != "SolidBall") {
            if (character1->getWeapon()->isAttacking()) {
                if (character2 && character1->getWeapon()->collidesWithCharacter(character2)) {
                    character2->takeDamage(character1->getWeapon()->getDamage());
                    character2->takeHit();
                    qDebug() << "Character2 took damage:" << character1->getWeapon()->getDamage();
                }
            }
        }
    }
    // 检查角色2的攻击
    if (character2 && character2->getWeapon()) {
        if (character2->getWeapon()->getWeaponType() != "SolidBall") {
            if (character2->getWeapon()->isAttacking()) {
                if (character1 && character2->getWeapon()->collidesWithCharacter(character1)) {
                    character1->takeDamage(character2->getWeapon()->getDamage());
                    character1->takeHit();
                    qDebug() << "Character1 took damage:" << character2->getWeapon()->getDamage();
                }
            }
        }
    }
    processProjectileCollisions();
}

void BattleScene::processProjectileCollisions() {
    // 获取场景中的所有子弹
    QList<QGraphicsItem*> items = this->items();
    for (QGraphicsItem* item : items) {
        // 实心球
        if (SolidBallProjectile* projectile = dynamic_cast<SolidBallProjectile*>(item)) {
            if (character1 && projectile->collidesWithCharacter(character1) && character1 != projectile->getOwner()) {
                character1->takeDamage(projectile->getDamage());
                character1->takeHit();
            } else if (character2 && projectile->collidesWithCharacter(character2) && character2 != projectile->getOwner()) {
                character2->takeDamage(projectile->getDamage());
                character2->takeHit();
            }
        }
        // 步枪子弹
        if (RifleBullet* bullet = dynamic_cast<RifleBullet*>(item)) {
            if (character1 && bullet->collidesWithCharacter(character1) && character1 != bullet->getOwner()) {
                character1->takeDamage(bullet->getDamage());
                character1->takeHit();
            } else if (character2 && bullet->collidesWithCharacter(character2) && character2 != bullet->getOwner()) {
                character2->takeDamage(bullet->getDamage());
                character2->takeHit();
            }
        }
        // 狙击枪子弹
        if (SniperBullet* bullet = dynamic_cast<SniperBullet*>(item)) {
            if (character1 && bullet->collidesWithCharacter(character1) && character1 != bullet->getOwner()) {
                character1->takeDamage(bullet->getDamage());
                character1->takeHit();
            } else if (character2 && bullet->collidesWithCharacter(character2) && character2 != bullet->getOwner()) {
                character2->takeDamage(bullet->getDamage());
                character2->takeHit();
            }
        }
    }
}

void BattleScene::spawnRandomWeapon() {
    // 随机选择武器类型
    double r = QRandomGenerator::global()->generateDouble(); // [0,1)
    double acc = 0;
    QString weaponType;
    for (const auto &p : weaponProbTable) {
        acc += p.second;
        if (r <= acc) {
            weaponType = p.first;
            break;
        }
    }
    Weapon *weapon = nullptr;
    if (weaponType == "Sword") weapon = new Sword();
    else if (weaponType == "Rifle") weapon = new Rifle();
    else if (weaponType == "Sniper") weapon = new Sniper();
    else if (weaponType == "SolidBall") weapon = new SolidBall();
    if (!weapon) return;
    // 随机X坐标，Y在顶部
    qreal x = sceneRect().left() + QRandomGenerator::global()->bounded((int)(sceneRect().width() - 64));
    qreal y = sceneRect().top() + 10;
    weapon->setPos(x, y);
    addItem(weapon);
    // 设置武器为掉落状态（可在Weapon类扩展重力属性）
    weapon->setOwner(nullptr);
    weapon->setFalling(true);
    weapon->setVelocity(QPointF(0, 0));
    fallingWeapons.push_back(weapon);
}

void BattleScene::updateFallingWeapons() {
    // 获取所有平台
    QList<QGraphicsItem*> platforms;
    for (QGraphicsItem* item : items()) {
        if (dynamic_cast<Platform*>(item)) platforms.append(item);
    }
    // 遍历所有下落武器
    for (auto it = fallingWeapons.begin(); it != fallingWeapons.end(); ) {
        Weapon* weapon = *it;
        if (weapon->getFalling()) {
            weapon->fallUpdate(platforms);
            ++it;
        } else {
            // 停止下落后移除出列表
            it = fallingWeapons.erase(it);
        }
    }
}

void BattleScene::resetGame() {
    gameEnded = false;
    if (character1) {
        character1->setHealth(100);
        // character1->equipSniper();
        // 可选：重置动画、按键等状态
    }
    if (character2) {
        character2->setHealth(100);
        // character2->equipRifle();
        // 可选：重置动画、按键等状态
    }
    if (map && character1 && character2) {
        QPointF spawnPos = map->getSpawnPos();
        character1->setPos(spawnPos);
        character2->setPos(spawnPos + QPointF(320, 0));
    }
    updateHealthHUD();
    // 可选：重置其它自定义状态
}
