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
    isPlaced = false;

}

int Square::getState(){
    return state_;
}

bool Square::getIsPlaced(){
    return isPlaced;
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent* event){
    qDebug() << getState();
    if (getState() == ship){
        qDebug() << "ifdupaa" << getIsPlaced() << getState();
        game->pickUpShip(this);
    }
    else if (getState() == unknown && game->squareToPlace != NULL){
       qDebug() << "ifdupa";
       game->placeShip(this);
    }
    else {
        return;
    }
}





void Square::setState(state stateOfSquare){
    state_ = stateOfSquare;
}

void Square::setIsPlaced(bool isIt){
    isPlaced = isIt;
}
