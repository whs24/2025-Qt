#ifndef QT_PROGRAMMING_2024_WINSCENE_H
#define QT_PROGRAMMING_2024_WINSCENE_H

#include "Scene.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>

class WinScene : public Scene {
    Q_OBJECT
public:
    enum Winner { Player1, Player2 };
    explicit WinScene(Winner winner, QObject *parent = nullptr);

signals:
    void backToMainMenuClicked();

private:
    QPushButton *backBtn = nullptr;
    QGraphicsPixmapItem *background = nullptr;
    QGraphicsProxyWidget *backBtnProxy = nullptr;
    Winner winner;
    void setupScene();
};

#endif //QT_PROGRAMMING_2024_WINSCENE_H 