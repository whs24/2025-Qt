cmake_minimum_required(VERSION 3.28)
project(qt_programming_2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_programming_2024 src/main.cpp
        src/MyGame.cpp
        src/MyGame.h
        src/Items/Item.cpp
        src/Items/Item.h
        src/Items/HealthHUD.cpp
        src/Items/HealthHUD.h
        src/Items/Weapons/Weapon.cpp
        src/Items/Weapons/Weapon.h
        src/Items/Weapons/Fist.cpp
        src/Items/Weapons/Fist.h
        src/Items/Weapons/Sword.cpp
        src/Items/Weapons/Sword.h
        src/Items/Weapons/Gun.cpp
        src/Items/Weapons/Gun.h
        src/Items/Weapons/Rifle.cpp
        src/Items/Weapons/Rifle.h
        src/Items/Weapons/RifleBullet.cpp
        src/Items/Weapons/RifleBullet.h
        src/Items/Weapons/Sniper.cpp
        src/Items/Weapons/Sniper.h
        src/Items/Weapons/SniperBullet.cpp
        src/Items/Weapons/SniperBullet.h
        src/Items/Characters/Character.cpp
        src/Items/Characters/Character.h
        src/Items/Characters/Link.cpp
        src/Items/Characters/Link.h
        src/Items/Characters/Red.cpp
        src/Items/Characters/Red.h
        src/Items/Armors/Armor.cpp
        src/Items/Armors/Armor.h
        src/Items/HeadEquipments/HeadEquipment.cpp
        src/Items/HeadEquipments/HeadEquipment.h
        src/Items/LegEquipments/LegEquipment.cpp
        src/Items/LegEquipments/LegEquipment.h
        src/Items/HeadEquipments/CapOfTheHero.cpp
        src/Items/HeadEquipments/CapOfTheHero.h
        src/Items/Armors/OldShirt.cpp
        src/Items/Armors/OldShirt.h
        src/Items/LegEquipments/WellWornTrousers.cpp
        src/Items/LegEquipments/WellWornTrousers.h
        src/Scenes/Scene.cpp
        src/Scenes/Scene.h
        src/Scenes/BattleScene.cpp
        src/Scenes/BattleScene.h
        src/Scenes/MainMenuScene.cpp
        src/Scenes/MainMenuScene.h
        src/Scenes/HelpScene.cpp
        src/Scenes/HelpScene.h
        src/Scenes/WinScene.cpp
        src/Scenes/WinScene.h
        assets/assets.qrc
        src/Items/Maps/Map.cpp
        src/Items/Maps/Map.h
        src/Items/Maps/Battlefield.cpp
        src/Items/Maps/Battlefield.h
        src/Items/Maps/TileEntity.cpp
        src/Items/Maps/TileEntity.h
        src/Items/Maps/Platform.cpp
        src/Items/Maps/Platform.h
        src/Items/Maps/TileMap.cpp
        src/Items/Maps/TileMap.h
        src/Items/Mountable.cpp
        src/Items/Mountable.h
        src/Items/Armors/FlamebreakerArmor.cpp
        src/Items/Armors/FlamebreakerArmor.h
        src/Items/Weapons/SolidBall.cpp
        src/Items/Weapons/SolidBall.h
        src/Items/Weapons/SolidBallProjectile.cpp
        src/Items/Weapons/SolidBallProjectile.h)
target_link_libraries(qt_programming_2024
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

