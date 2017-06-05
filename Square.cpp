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

bool Square::getIsPlaced(){
    return isPlaced;
}

int Square::getLifeOfShip(){
    return lifeOfSship_;
}



void Square::mousePressEvent(QGraphicsSceneMouseEvent* event){
    qDebug() << getState();
    if(game->whosTurn == "NOONE"){
        //układanie statkow
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
    else{
        //strzelanie
        qDebug() << "szczela";

    game->shoot(this);

    }
}

void Square::setState(state stateOfSquare){
    state_ = stateOfSquare;
}

void Square::setIsPlaced(bool isIt){
    isPlaced = isIt;
}

void Square::incrementLifeOfShip(){
    lifeOfSship_++;
}

void Square::checkNearby(int index){
    if (game->list.contains(index-10)){
            lifeOfSship_++;
    }
    if (game->list.contains(index+10)){
           lifeOfSship_++;
    }
    if (game->list.contains(index-1)){
            lifeOfSship_++;
    }
    if (game->list.contains(index+1)){
            lifeOfSship_++;
    }
}




