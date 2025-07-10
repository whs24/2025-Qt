#include "MainMenuScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QFont>
#include <QDebug>

MainMenuScene::MainMenuScene(QObject *parent) : Scene(parent) {
    // 设置场景大小
    setSceneRect(0, 0, 1248, 832);
    // 设置背景
    QPixmap bgPixmap(":/Items/scenes/main.png");
    if (bgPixmap.isNull()) {
        qDebug() << "主菜单背景图片加载失败！";
    }
    background = new QGraphicsPixmapItem(bgPixmap.scaled(1248, 832));
    addItem(background);

    // 按钮样式
    QFont btnFont("微软雅黑", 18, QFont::Bold);
    QSize btnSize(180, 60);

    // 单人模式按钮
    singlePlayerBtn = new QPushButton("单人模式");
    singlePlayerBtn->setFont(btnFont);
    singlePlayerBtn->setFixedSize(btnSize);
    singleBtnProxy = addWidget(singlePlayerBtn);
    // 双人模式按钮
    doublePlayerBtn = new QPushButton("双人模式");
    doublePlayerBtn->setFont(btnFont);
    doublePlayerBtn->setFixedSize(btnSize);
    doubleBtnProxy = addWidget(doublePlayerBtn);
    // 教程按钮
    tutorialBtn = new QPushButton("教程");
    tutorialBtn->setFont(btnFont);
    tutorialBtn->setFixedSize(btnSize);
    tutorialBtnProxy = addWidget(tutorialBtn);

    // 按钮竖直排列，右下角
    int margin = 40;
    int spacing = 30;
    int totalHeight = btnSize.height() * 3 + spacing * 2;
    int startY = 832 - margin - totalHeight;
    int x = 1248 - margin - btnSize.width();
    singleBtnProxy->setPos(x, startY);
    doubleBtnProxy->setPos(x, startY + btnSize.height() + spacing);
    tutorialBtnProxy->setPos(x, startY + (btnSize.height() + spacing) * 2);

    // 信号连接
    connect(singlePlayerBtn, &QPushButton::clicked, this, &MainMenuScene::singlePlayerClicked);
    connect(doublePlayerBtn, &QPushButton::clicked, this, &MainMenuScene::doublePlayerClicked);
    connect(tutorialBtn, &QPushButton::clicked, this, &MainMenuScene::tutorialClicked);
} 
