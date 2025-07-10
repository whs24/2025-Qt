//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_MYGAME_H
#define QT_PROGRAMMING_2024_MYGAME_H

#include <QGraphicsView>  //Qt图形视图类
#include <QMainWindow>   //Qt主窗口类
#include "Scenes/Scene.h" //自定义场景类
#include "Scenes/MainMenuScene.h" // 新增主菜单场景
#include "Scenes/HelpScene.h" // 新增帮助页面场景
#include "Scenes/WinScene.h" // 新增结算页面场景
#include "Scenes/BattleScene.h" // 新增：确保头文件可用

class MyGame : public QMainWindow {  //MyGame类继承自QMainWindow类
Q_OBJECT

public:
    explicit MyGame(QWidget *parent = nullptr);

private:
    BattleScene *battleScene; //战斗场景（类型修正）
    MainMenuScene *mainMenuScene; //主菜单场景
    HelpScene *helpScene; //帮助页面场景
    WinScene *winScene; //结算页面场景
    QGraphicsView *view; //图形视图
    void showMainMenu(); //显示主菜单

private slots:
    void onPlayer1Win();
    void onPlayer2Win();
};


#endif //QT_PROGRAMMING_2024_MYGAME_H
