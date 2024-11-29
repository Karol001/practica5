#include "pacman.h"
#include <QGraphicsEllipseItem>
#include <QBrush>
#include "laberinto.h"
#include "fantasma.h"


Pacman::Pacman(QWidget *parent)
    : QMainWindow(parent), direction(0), puntuacion(0) {
    setWindowTitle("PacMan en Qt - Puntuación: " + QString::number(puntuacion));
    resize(600, 400);

    // Crear y configurar la escena y vista
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Configurar los límites de la escena
    scene->setSceneRect(0, 0, 580, 380);

    // Crear e inicializar el laberinto
    laberinto = new Laberinto(scene);
    laberinto->crear();

    // Timer del juego
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Pacman::updateGame);
    gameTimer->start(40);  // ~60 FPS

    setupGame();
}

void Pacman::setupGame() {
    puntuacion = 0;

    // Crea a Pac-Man con tamaño ajustado para evitar colisiones
    pacman = scene->addEllipse(0, 0, Laberinto::CELL_SIZE - 12, Laberinto::CELL_SIZE - 12, QPen(Qt::black), QBrush(Qt::yellow));

    // Ajusta la posición inicial de Pac-Man
    pacman->setPos(Laberinto::CELL_SIZE * 1 + 2, Laberinto::CELL_SIZE * 1 + 2);  // Pequeño desplazamiento para evitar bordes

    // Verificar si Pac-Man está colisionando con un muro en la posición inicial
    QRectF pacmanRect(pacman->pos(), QSizeF(Laberinto::CELL_SIZE - 12, Laberinto::CELL_SIZE - 12));
    if (laberinto->hayColision(pacmanRect)) {
        qDebug() << "Pac-Man está colisionando con un muro en la posición inicial";
    }

    fantasmas.append(new Fantasma(scene, 0, 5, 5, laberinto));  // Fantasma rojo
    fantasmas.append(new Fantasma(scene, 1, 5, 6, laberinto));  // Fantasma rosa
    fantasmas.append(new Fantasma(scene, 2, 5, 7, laberinto));  // Fantasma azul
    fantasmas.append(new Fantasma(scene, 3, 5, 8, laberinto));  // Fantasma naranja

}


void Pacman::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_D:  // Derecha
        direction = 0;
        qDebug() << "Dirección: Derecha";
        break;
    case Qt::Key_S:  // Abajo
        direction = 1;
        qDebug() << "Dirección: Abajo";
        break;
    case Qt::Key_A:  // Izquierda
        direction = 2;
        qDebug() << "Dirección: Izquierda";
        break;
    case Qt::Key_W:  // Arriba
        direction = 3;
        qDebug() << "Dirección: Arriba";
        break;
    }
}

void Pacman::updateGame() {
    QPointF pos = pacman->pos();  // Posición actual
    QPointF newPos = pos;

    // Calcular nueva posición según la dirección
    switch (direction) {
    case 0:  // Derecha
        newPos.setX(pos.x() + STEP);
        break;
    case 1:  // Abajo
        newPos.setY(pos.y() + STEP);
        break;
    case 2:  // Izquierda
        newPos.setX(pos.x() - STEP);
        break;
    case 3:  // Arriba
        newPos.setY(pos.y() - STEP);
        break;
    }

    // Crear un rectángulo representando la nueva posición de Pac-Man
    QRectF pacmanRect(newPos, QSizeF(Laberinto::CELL_SIZE - 8, Laberinto::CELL_SIZE - 8));  // Tamaño ajustado de Pac-Man

    // Verificar colisión con muros
    if (!laberinto->hayColision(pacmanRect)) {
        pacman->setPos(newPos);  // Mover a la nueva posición si no hay colisión
    }

    // Detectar colisión con pastillas
    for (int fila = 0; fila < Laberinto::FILAS; fila++) {
        for (int columna = 0; columna < Laberinto::COLUMNAS; columna++) {
            if (Laberinto::disenoLaberinto[fila][columna] == 2) {
                QRectF pastillaRect(
                    columna * Laberinto::CELL_SIZE + (Laberinto::CELL_SIZE / 4),
                    fila * Laberinto::CELL_SIZE + (Laberinto::CELL_SIZE / 4),
                    Laberinto::CELL_SIZE / 2,
                    Laberinto::CELL_SIZE / 2
                    );

                if (pacmanRect.intersects(pastillaRect)) {
                    Laberinto::disenoLaberinto[fila][columna] = 0;  // Actualizar matriz

                    auto &pastillas = laberinto->getPastillas();
                    for (int i = 0; i < pastillas.size(); ++i) {
                        QGraphicsEllipseItem *pastilla = pastillas[i];
                        if (pastilla->sceneBoundingRect().intersects(pastillaRect)) {
                            scene->removeItem(pastilla);  // Eliminar de la escena
                            delete pastilla;             // Liberar memoria
                            pastillas.removeAt(i);       // Eliminar del contenedor
                            break;
                        }
                    }
                    puntuacion += 10;  // Actualizar puntuación
                }
            }
        }
    }

    // Actualizar el título con la puntuación
    setWindowTitle("PacMan en Qt - Puntuación: " + QString::number(puntuacion));
}

Pacman::~Pacman() {
    delete laberinto;
}
