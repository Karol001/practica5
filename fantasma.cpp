#include "fantasma.h"
#include <QBrush>
#include <QPen>
#include <QTimer>
#include <QRandomGenerator>


Fantasma::Fantasma(QGraphicsScene *scene, int color, int fila, int columna, Laberinto *laberinto)
    : scene(scene), fila(fila), columna(columna), laberinto(laberinto), direccion(0) {

    fantasmaItem = scene->addEllipse(0, 0, Laberinto::CELL_SIZE - 12, Laberinto::CELL_SIZE - 12,
                                     QPen(Qt::black), QBrush(Qt::red));  // Color por defecto rojo

    if (color == 0) {
        fantasmaItem->setBrush(QBrush(Qt::red));  // Fantasma rojo
    }
    else if (color == 1) {
        fantasmaItem->setBrush(QBrush(QColor(255, 105, 180)));
    }
    else if (color == 2) {
        fantasmaItem->setBrush(QBrush(Qt::blue));  // Fantasma azul
    }
    else if (color == 3) {
        fantasmaItem->setBrush(QBrush(QColor(255, 165, 0)));
    }

    fantasmaItem->setPos(columna * Laberinto::CELL_SIZE, fila * Laberinto::CELL_SIZE);

    // Temporizador para mover el fantasma
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fantasma::mover);
    timer->start(100);
}

bool Fantasma::hayColision(const QRectF &rect) const {
    return laberinto->hayColision(rect);  // Verificar colisión con el laberinto
}

void Fantasma::mover() {
    // Lógica para mover el fantasma y evitar colisiones
    QRectF rectFantasma = fantasmaItem->boundingRect();
    rectFantasma.moveTo(fantasmaItem->pos());

    if (!hayColision(rectFantasma)) {
        // Lógica para mover el fantasma en la dirección actual
        if (direccion == 0) {
            fantasmaItem->moveBy(Laberinto::CELL_SIZE, 0);  // Mover a la derecha
        }
        // Agregar más direcciones para moverse (arriba, abajo, izquierda)
    } else {
        cambiarDireccion();  // Cambiar la dirección si hay colisión
    }
}

void Fantasma::cambiarDireccion() {
    // Lógica para cambiar la dirección del fantasma aleatoriamente
    direccion = QRandomGenerator::global()->bounded(4);  // Genera un número aleatorio entre 0 y 3
}
