#ifndef QT_PROGRAMMING_2024_HELPSCENE_H
#define QT_PROGRAMMING_2024_HELPSCENE_H

#include "Scene.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>

class HelpScene : public Scene {
    Q_OBJECT
public:
    explicit HelpScene(QObject *parent = nullptr);

signals:
    void backToMainMenuClicked();

private:
    QPushButton *backBtn;
    QGraphicsPixmapItem *background;
    QGraphicsProxyWidget *backBtnProxy;
};

#endif //QT_PROGRAMMING_2024_HELPSCENE_H 