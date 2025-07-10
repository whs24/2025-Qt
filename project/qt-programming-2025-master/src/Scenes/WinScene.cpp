#include "WinScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QFont>
#include <QDebug>

WinScene::WinScene(Winner winner, QObject *parent)
    : Scene(parent), backBtn(nullptr), background(nullptr), backBtnProxy(nullptr), winner(winner) {
    setupScene();
}

void WinScene::setupScene() {
    if (background) {
        removeItem(background);
        delete background;
        background = nullptr;
    }
    if (backBtnProxy) {
        removeItem(backBtnProxy);
        delete backBtnProxy;
        backBtnProxy = nullptr;
    }
    QFont btnFont("微软雅黑", 18, QFont::Bold);
    QSize btnSize(220, 70);
    int margin = 40;
    if (winner == Player1) {
        setSceneRect(0, 0, 1011, 712);
        QPixmap bgPixmap(":/Items/scenes/1win.png");
        if (bgPixmap.isNull()) qDebug() << "1win图片加载失败！";
        background = new QGraphicsPixmapItem(bgPixmap.scaled(1011, 712));
        addItem(background);
        backBtn = new QPushButton("返回主标题");
        backBtn->setFont(btnFont);
        backBtn->setFixedSize(btnSize);
        backBtnProxy = addWidget(backBtn);
        int x = (1011 - btnSize.width()) / 2;
        int y = 712 / 2 + 180;
        backBtnProxy->setPos(x, y);
    } else {
        setSceneRect(0, 0, 1112, 690);
        QPixmap bgPixmap(":/Items/scenes/2win.png");
        if (bgPixmap.isNull()) qDebug() << "2win图片加载失败！";
        background = new QGraphicsPixmapItem(bgPixmap.scaled(1112  , 690));
        addItem(background);
        backBtn = new QPushButton("返回主标题");
        backBtn->setFont(btnFont);
        backBtn->setFixedSize(btnSize);
        backBtnProxy = addWidget(backBtn);
        int x = (1112 - btnSize.width()) / 2;
        int y = 690 / 2 + 200;
        backBtnProxy->setPos(x, y);
    }
    connect(backBtn, &QPushButton::clicked, this, &WinScene::backToMainMenuClicked);
} 
