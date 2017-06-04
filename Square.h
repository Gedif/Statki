#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QList>


enum state
{
    unknown,    //
    miss,       //
    hit,        //
  //  sinked,
    ship   //
};


class Square: public QGraphicsRectItem{
public:
    // constructors
    Square(QGraphicsItem* parent=NULL);
    // getters
    int getState();
    bool getIsPlaced();

    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);



    // setters
    void setState(state satateOfSquare);
    void setIsPlaced(bool isIt);


private:
    bool isPlaced;
    QString owner;
    state state_;

};


#endif // SQUARE_H
