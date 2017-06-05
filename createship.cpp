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

void CreateShip::placeSquares(int x, int y, int num_of_egments){
    int X_SHIFT = 50;
    for (size_t i = 0, n = num_of_egments; i < n; i++){
        Square* square = new Square();
       // square->setLifeOfShip(num_of_egments);
        square->setState(ship);
        square->setPos(x+X_SHIFT*i,y);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkGray);
        square->setBrush(brush);
        ships.append(square);
        game->scene->addItem(square);
    }
        setNumOfSegments(num_of_egments);
}
