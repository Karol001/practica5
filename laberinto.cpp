#include "laberinto.h"
#include <QPen>
#include <QBrush>

// Definición del diseño lógico del laberinto
int Laberinto::disenoLaberinto[FILAS][COLUMNAS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,1},
    {1,2,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,1,1,0,0,0,0,1,1,0,0,0,0,1,1,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,0,0,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,0,2,2,2,2,1,0,4,4,4,4,0,1,2,2,2,2,0,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,1,1,1,1},
    {1,3,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,3,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,1},
    {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
    {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Constructor
Laberinto::Laberinto(QGraphicsScene *scene) : scene(scene) {}

// Método para crear el laberinto
void Laberinto::crear() {
    QPen paredPen(Qt::blue);
    QBrush paredBrush(Qt::blue);

    QPen pastillaPen(Qt::yellow);
    QBrush pastillaBrush(Qt::yellow);

    QPen pastillaPen1(Qt::red);
    QBrush pastillaBrush1(Qt::red);

    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            if (disenoLaberinto[fila][columna] == 1) {
                // Pared
                QGraphicsRectItem *pared = scene->addRect(
                    columna * CELL_SIZE,  // Posición horizontal
                    fila * CELL_SIZE,     // Posición vertical
                    CELL_SIZE,            // Ancho
                    CELL_SIZE,            // Alto
                    paredPen,             // Color del borde
                    paredBrush           // Color de relleno
                    );
                paredes.append(pared);
            } else if (disenoLaberinto[fila][columna] == 2) {
                // Pastilla normal
                QGraphicsEllipseItem *pastilla = scene->addEllipse(
                    columna * CELL_SIZE + (CELL_SIZE / 4),
                    fila * CELL_SIZE + (CELL_SIZE / 4),
                    CELL_SIZE / 2,
                    CELL_SIZE / 2,
                    pastillaPen,
                    pastillaBrush
                    );
                pastillas.append(pastilla);
            } else if (disenoLaberinto[fila][columna] == 3) {
                // Pastilla especial (puedes usar otro color)
                QGraphicsEllipseItem *pastilla = scene->addEllipse(
                    columna * CELL_SIZE + (CELL_SIZE / 4),
                    fila * CELL_SIZE + (CELL_SIZE / 4),
                    CELL_SIZE / 2,
                    CELL_SIZE / 2,
                    pastillaPen1,
                    pastillaBrush1
                    );
                pastillas.append(pastilla);
            }
        }
    }
}

bool Laberinto::hayColision(const QRectF &rect) const {
    for (const auto &pared : paredes) {
        if (pared->boundingRect().intersects(rect)) {
            return true;
        }
    }
    return false;
}

// Método para obtener las pastillas
QVector<QGraphicsEllipseItem*>& Laberinto::getPastillas() {
    return pastillas;
}
