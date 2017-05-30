#include "CreateShip.h"
#include "Game.h"

extern Game* game;

CreateShip::CreateShip(){
}

QList<Square *> CreateShip::getSquares(){
    return squares;
}

void CreateShip::setNumOfSegments(int num){
    numOfSegments = num;
}

void CreateShip::placeSquares(int x, int y, int numOfSegments){
    int X_SHIFT = 50;
    for (size_t i = 0, n = numOfSegments; i < n; i++){
        Square* square = new Square();
        square->setState(ship);
        square->setPos(x+X_SHIFT*i,y);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkGray);
        square->setBrush(brush);
        squares.append(square);
        game->scene->addItem(square);
    }
        setNumOfSegments(numOfSegments);
}
