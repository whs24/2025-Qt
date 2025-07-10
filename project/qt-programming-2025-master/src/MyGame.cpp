//
// Created by gerw on 8/20/24.
//
#include "MyGame.h"
#include "Scenes/BattleScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/HelpScene.h"
#include "Scenes/WinScene.h"

MyGame::MyGame(QWidget *parent) : QMainWindow(parent) {
    mainMenuScene = new MainMenuScene(this);
    battleScene = new BattleScene(this);
    helpScene = new HelpScene(this);
    winScene = nullptr;
    view = new QGraphicsView(this);
    view->setScene(mainMenuScene); // 初始显示主菜单
    view->setFixedSize((int) mainMenuScene->sceneRect().width(), (int) mainMenuScene->sceneRect().height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view);
    setFixedSize(view->sizeHint());
    // 连接主菜单按钮
    connect(mainMenuScene, &MainMenuScene::singlePlayerClicked, this, [this]() {
        // TODO: 设置red为AI，重置状态
        view->setScene(battleScene);
        view->setFixedSize((int) battleScene->sceneRect().width(), (int) battleScene->sceneRect().height());
        setFixedSize(view->sizeHint());
        battleScene->resetGame();
        battleScene->startLoop();
    });
    connect(mainMenuScene, &MainMenuScene::doublePlayerClicked, this, [this]() {
        // TODO: 双人模式，重置状态
        view->setScene(battleScene);
        view->setFixedSize((int) battleScene->sceneRect().width(), (int) battleScene->sceneRect().height());
        setFixedSize(view->sizeHint());
        battleScene->resetGame();
        battleScene->startLoop();
    });
    connect(mainMenuScene, &MainMenuScene::tutorialClicked, this, [this]() {
        // 跳转到帮助页面
        view->setScene(helpScene);
        view->setFixedSize((int) helpScene->sceneRect().width(), (int) helpScene->sceneRect().height());
        setFixedSize(view->sizeHint());
    });
    // 帮助页面返回主菜单
    connect(helpScene, &HelpScene::backToMainMenuClicked, this, [this]() {
        showMainMenu();
    });
    // 结算页面跳转
    connect(battleScene, &BattleScene::player1Win, this, &MyGame::onPlayer1Win);
    connect(battleScene, &BattleScene::player2Win, this, &MyGame::onPlayer2Win);
}

void MyGame::showMainMenu() {
    view->setScene(mainMenuScene);
    view->setFixedSize((int) mainMenuScene->sceneRect().width(), (int) mainMenuScene->sceneRect().height());
    setFixedSize(view->sizeHint());
}

void MyGame::onPlayer1Win() {
    if (winScene) delete winScene;
    winScene = new WinScene(WinScene::Player1, this);
    connect(winScene, &WinScene::backToMainMenuClicked, this, &MyGame::showMainMenu);
    view->setScene(winScene);
    view->setFixedSize((int)winScene->sceneRect().width(), (int)winScene->sceneRect().height());
    setFixedSize(view->sizeHint());
}

void MyGame::onPlayer2Win() {
    if (winScene) delete winScene;
    winScene = new WinScene(WinScene::Player2, this);
    connect(winScene, &WinScene::backToMainMenuClicked, this, &MyGame::showMainMenu);
    view->setScene(winScene);
    view->setFixedSize((int)winScene->sceneRect().width(), (int)winScene->sceneRect().height());
    setFixedSize(view->sizeHint());
}
