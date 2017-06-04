#include "Square.h"
#include <QRectF>
#include <QVector>
#include "Game.h"
#include <QDebug>

extern Game* game;

Square::Square(QGraphicsItem *parent){
    // draw the square

    setRect(5,5,50,50);
    setState(unknown);
    // allow responding to hover events
    setAcceptHoverEvents(true);
//    isPlaced = false;

}

int Square::getState(){
    return state_;
}



void Square::mousePressEvent(QGraphicsSceneMouseEvent* event){
    qDebug() << getState();
    if (getState() == ship){
        qDebug() << "jesli to statek podnies"  << getState();
        game->pickUpShip(this);
    }
    else if (getState() == unknown && game->squareToPlace != NULL ) {
       qDebug() << "jesli to woda, masz co położyć";
       game->placeShip(this);
    }
    else {
        return;
    }
}

void Square::setState(state stateOfSquare){
    state_ = stateOfSquare;
}



