#ifndef LABERINTO_H
#define LABERINTO_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QVector>

class Laberinto {
public:
    Laberinto(QGraphicsScene *scene);
    void crear();
    bool hayColision(const QRectF &rect) const;  // Declaración correcta

    static const int CELL_SIZE = 22;
    static const int FILAS = 22;
    static const int COLUMNAS = 28;
    static int disenoLaberinto[FILAS][COLUMNAS];

    QVector<QGraphicsEllipseItem*>& getPastillas();  // Método público para acceder a pastillas

private:
    QGraphicsScene *scene;
    QVector<QGraphicsRectItem*> paredes;
    QVector<QGraphicsEllipseItem*> pastillas;
};

#endif
