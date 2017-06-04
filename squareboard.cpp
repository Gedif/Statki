#include "SquareBoard.h"
#include "Game.h"

extern Game* game;

SquareBoard::SquareBoard(){

}

QList<Square *> SquareBoard::getSquares(){
    return squares;
}



void SquareBoard::placeSquares(int x, int y, int cols, int rows,state state){

    int X_SHIFT = 50;
    for (size_t i = 0, n = cols; i < n; i++){
        createSquaresColumn(x+X_SHIFT*i,y,rows,state);
    }

}



void SquareBoard::createSquaresColumn(int x, int y, int numOfRows, state state){
    // creates a column of Squares at the specified location with the specified
    // number of rows
    for (size_t i = 0, n = numOfRows; i < n; i++){
        Square* square = new Square();
        square->setPos(x,y+50*i);
        //square->setIsPlaced(true);
        if (state == unknown){
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::darkBlue);
            square->setBrush(brush);
        }
        else if (state == ship) {
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::darkGray);
            square->setBrush(brush);
        }
        squares.append(square);
        game->scene->addItem(square);
    }
}

void SquareBoard::setListOfBlockedSquares(int indexOfShip){
    listOfBlockedSquares.append(indexOfShip-11);
    listOfBlockedSquares.append(indexOfShip-9);
    listOfBlockedSquares.append(indexOfShip+11);
    listOfBlockedSquares.append(indexOfShip+9);
    // QDebug << listOfBlockedSquares;
}

void SquareBoard::clearBlockedSquares(int indexOfPickedShip){
    listOfBlockedSquares.removeOne(indexOfPickedShip-11);
    listOfBlockedSquares.removeOne(indexOfPickedShip-9);
    listOfBlockedSquares.removeOne(indexOfPickedShip+11);
    listOfBlockedSquares.removeOne(indexOfPickedShip+9);
}
