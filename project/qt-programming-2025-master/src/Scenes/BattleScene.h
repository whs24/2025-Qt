//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_BATTLESCENE_H
#define QT_PROGRAMMING_2024_BATTLESCENE_H

#include <QKeyEvent>
#include "Scene.h"
#include "../Items/Maps/TileMap.h"
#include "../Items/Characters/Character.h"
#include "../Items/Characters/Link.h"
#include "../Items/Characters/Red.h"
#include "../Items/Mountable.h"
#include "../Items/Armors/Armor.h"
#include "../Items/HealthHUD.h"
#include <QTimer>
#include <vector>
#include "../Items/Weapons/Weapon.h"

class BattleScene : public Scene {
Q_OBJECT

public:
    explicit BattleScene(QObject *parent);

    void processInput() override;

    void processMovement() override;

    void processPicking() override;

    void resetGame();

signals:
    void player1Win();
    void player2Win();

protected slots:

    void update() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:

    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());

    static Mountable * pickupMountable(Character *character, Mountable *mountable);
    
    void processCharacterMovement(Character *character);
    
    void processProjectileCollisions(); 
    
    void updateHealthHUD();
    
    void processAttackDetection();

    TileMap *map;
    Link *character1; // 第一个角色（Link）
    Red *character2;  // 第二个角色（Red）
    Armor *spareArmor;
    HealthHUD *healthHUD; // 生命值HUD
    bool gameEnded = false;
    QTimer *weaponSpawnTimer = nullptr;
    double weaponSpawnInterval = 10000;
    std::vector<std::pair<QString, double>> weaponProbTable = {
        {"Sword", 0.3},
        {"Rifle", 0.25},
        {"Sniper", 0.25},
        {"SolidBall", 0.2}
    };
    std::vector<Weapon*> fallingWeapons;
    void spawnRandomWeapon();
    void updateFallingWeapons();
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
