#ifndef PACMAN_H
#define PACMAN_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include "laberinto.h"

class Pacman : public QMainWindow {
    Q_OBJECT

public:
    Pacman(QWidget *parent = nullptr);
    ~Pacman();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsEllipseItem *pacman;
    QTimer *gameTimer;
    Laberinto *laberinto;
    int direction;
    const int STEP = 3;
    int puntuacion;


private slots:
    void updateGame();
    void setupGame();
};

#endif
