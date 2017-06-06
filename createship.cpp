#include "CreateShip.h"
#include "Game.h"

extern Game* game;

CreateShip::CreateShip(){
}

QList<Square *> CreateShip::getShips(){
    return ships;
}

void CreateShip::setNumOfSegments(int num){
    numOfSegments = num;
}

void CreateShip::placeSquares(int x, int y, int numOfSegments, int numOfShips){
    for(int i=0 ; i < numOfShips; ++i){
        Square* square = new Square();
        square->setLifeOfShip(numOfSegments);
        square->setState(SHIP);

        square->setRect(5,5,50*numOfSegments,50);
        square->setPos(x,y);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkGray);
        square->setBrush(brush);
        ships.append(square);
        game->scene->addItem(square);
        setNumOfSegments(numOfSegments);
    }
}
