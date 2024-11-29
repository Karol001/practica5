#ifndef FANTASMA_H
#define FANTASMA_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "laberinto.h"

class Fantasma : public QObject {
    Q_OBJECT

public:
    Fantasma(QGraphicsScene *scene, int color, int fila, int columna, Laberinto *laberinto);
    void mover();
    bool hayColision(const QRectF &rect) const;

private:
    QGraphicsEllipseItem *fantasmaItem;
    QGraphicsScene *scene;
    int fila;
    int columna;
    int direccion;
    Laberinto *laberinto;  // Puntero al laberinto

    void cambiarDireccion();  // Método para cambiar de dirección
};

#endif
