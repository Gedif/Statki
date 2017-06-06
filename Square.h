#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include "QBrush"
#include <QRectF>
#include <QVector>
#include <QDebug>


enum state
{
    UNKNOWN,    //
    SHIP   //
};


class Square: public QGraphicsRectItem{
public:
    // constructors
    Square(QGraphicsItem* parent=NULL);
    // getters
    int getState();
    bool getIsPlaced();
    int getLifeOfShip();

    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);



    // setters
    void setState(state satateOfSquare);
    void setIsPlaced(bool isIt);
    void setLifeOfShip(int health_points);

    //Pubic methods



private:
    int lifeOfSship_ = 0;
    bool isPlaced = false;
    QString owner;
    state state_;

};


#endif // SQUARE_H
