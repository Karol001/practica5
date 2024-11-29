#include "pacman.h"
#include <QGraphicsEllipseItem>
#include <QBrush>
#include "laberinto.h"

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

    // Inicializa Pac-Man en una posición libre
    pacman = scene->addEllipse(0, 0, Laberinto::CELL_SIZE - 4, Laberinto::CELL_SIZE - 4, QPen(Qt::black), QBrush(Qt::yellow));
    pacman->setPos(Laberinto::CELL_SIZE * 1, Laberinto::CELL_SIZE * 1);  // Posición inicial segura

    // Verificar si Pac-Man está colisionando con un muro en la posición inicial
    QRectF pacmanRect(pacman->pos(), QSizeF(17, 17));  // Asegúrate de que Pac-Man tenga un tamaño adecuado
    if (laberinto->hayColision(pacmanRect)) {
        qDebug() << "Pac-Man está colisionando con un muro en la posición inicial";
    }
}

void Pacman::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_D:  // Derecha
        direction = 0;
        break;
    case Qt::Key_S:  // Abajo
        direction = 1;
        break;
    case Qt::Key_A:  // Izquierda
        direction = 2;
        break;
    case Qt::Key_W:  // Arriba
        direction = 3;
        break;
    }
}

void Pacman::updateGame() {
    QPointF pos = pacman->pos();  // Posición actual
    QPointF newPos = pos;         // Nueva posición tentativa

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
    QRectF pacmanRect(newPos, QSizeF(Laberinto::CELL_SIZE - 4, Laberinto::CELL_SIZE - 4));  // Tamaño de Pac-Man

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
