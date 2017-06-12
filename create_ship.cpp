#include "create_ship.h"
#include "game.h"

extern Game* game;

CreateShip::CreateShip(){
}

QList<Square *> CreateShip::getShips(){
    return ships;
}

void CreateShip::setNumOfSegments(int num){
    numOfSegments = num;
}

void CreateShip::placeSquares(int x, int y, int numOfSegment, int numOfShips){
    for(int i=0 ; i < numOfShips; ++i){
        Square* square = new Square();
        square->setLifeOfShip(numOfSegment);
        square->setState(SHIP);
        square->setRect(5,5,50*numOfSegment,50);
        square->setPos(x,y);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkGray);
        square->setBrush(brush);
        ships.append(square);
        game->scene->addItem(square);
        setNumOfSegments(numOfSegment);
    }
}
