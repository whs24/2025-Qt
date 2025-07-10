#include "HelpScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QFont>
#include <QDebug>

HelpScene::HelpScene(QObject *parent) : Scene(parent) {
    // 设置场景大小
    setSceneRect(0, 0, 1011, 712);
    // 设置背景
    QPixmap bgPixmap(":/Items/scenes/help.png");
    if (bgPixmap.isNull()) {
        qDebug() << "帮助页面背景图片加载失败！";
    }
    background = new QGraphicsPixmapItem(bgPixmap.scaled(1011, 712));
    addItem(background);

    // 按钮样式
    QFont btnFont("微软雅黑", 18, QFont::Bold);
    QSize btnSize(200, 60);

    // 返回主标题按钮
    backBtn = new QPushButton("返回主标题");
    backBtn->setFont(btnFont);
    backBtn->setFixedSize(btnSize);
    backBtnProxy = addWidget(backBtn);
    // 右下角
    int margin = 40;
    int x = 1011 - margin - btnSize.width();
    int y = 712 - margin - btnSize.height();
    backBtnProxy->setPos(x, y);

    connect(backBtn, &QPushButton::clicked, this, &HelpScene::backToMainMenuClicked);
} 
