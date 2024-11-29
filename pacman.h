#ifndef PACMAN_H
#define PACMAN_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include "laberinto.h"
#include "fantasma.h"  // Incluyendo correctamente la cabecera de Fantasma

class Pacman : public QMainWindow {
    Q_OBJECT

public:
    Pacman(QWidget *parent = nullptr);  // Constructor
    ~Pacman();  // Destructor

protected:
    void keyPressEvent(QKeyEvent *event) override;  // Manejo de eventos de teclado

private:
    QGraphicsScene *scene;  // Escena gráfica
    QGraphicsView *view;    // Vista gráfica
    QGraphicsEllipseItem *pacman;  // Pacman representado como un elipse
    QTimer *gameTimer;  // Temporizador del juego
    Laberinto *laberinto;  // Instancia del laberinto
    QVector<Fantasma*> fantasmas;  // Vector de fantasmas
    int direction;  // Dirección de Pacman
    const int STEP = 3;  // Paso de movimiento
    int puntuacion;  // Puntuación del jugador

private slots:
    void updateGame();  // Actualiza el estado del juego en cada tick del temporizador
    void setupGame();   // Configura el juego inicial
};

#endif
