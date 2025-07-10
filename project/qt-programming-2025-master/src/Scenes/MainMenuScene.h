#ifndef QT_PROGRAMMING_2024_MAINMENUSCENE_H
#define QT_PROGRAMMING_2024_MAINMENUSCENE_H

#include "Scene.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>

class MainMenuScene : public Scene {
    Q_OBJECT
public:
    explicit MainMenuScene(QObject *parent = nullptr);

signals:
    void singlePlayerClicked();
    void doublePlayerClicked();
    void tutorialClicked();

private:
    QPushButton *singlePlayerBtn;
    QPushButton *doublePlayerBtn;
    QPushButton *tutorialBtn;
    QGraphicsPixmapItem *background;
    QGraphicsProxyWidget *singleBtnProxy;
    QGraphicsProxyWidget *doubleBtnProxy;
    QGraphicsProxyWidget *tutorialBtnProxy;
};

#endif //QT_PROGRAMMING_2024_MAINMENUSCENE_H 