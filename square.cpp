#include "square.h"
#include "game.h"

extern Game* game;

Square::Square(){
    setRect(5,5,50,50);
    setState(UNKNOWN);
    setAcceptHoverEvents(true);
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
    if(game->whosTurn == "NOONE" && event != NULL){
        if (getState() == SHIP && isPlaced==false){
            game->pickUpShip(this);
        }
        else if (getState() == UNKNOWN && game->squareToPlace != NULL ) {
            game->placeShip(this);
        }
        else {
            return;
        }
    }
    else{
    game->shootAdd(this);
    }
}

void Square::setState(state stateOfSquare){
    state_ = stateOfSquare;
}

void Square::setIsPlaced(bool isIt){
    isPlaced = isIt;
}

void Square::setLifeOfShip(int health_points){
    lifeOfSship_ = health_points;
}
