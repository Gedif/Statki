#include "SquareBoard.h"
#include "Game.h"

extern Game* game;

SquareBoard::SquareBoard(){
}

QList<Square *> SquareBoard::getSquares(){
    return squares;
}

void SquareBoard::placeSquares(int x, int y, int cols, int rows){
    int X_SHIFT = 50;
    for (size_t i = 0, n = cols; i < n; i++){
        createSquaresColumn(x+X_SHIFT*i,y,rows);
    }
}



void SquareBoard::createSquaresColumn(int x, int y, int numOfRows){
    // creates a column of Squares at the specified location with the specified
    // number of rows
    for (size_t i = 0, n = numOfRows; i < n; i++){
        Square* square = new Square();
        square->setPos(x,y+50*i);
        //square->setIsPlaced(true);
        square->setState(unknown);
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::darkBlue);
            square->setBrush(brush);

        squares.append(square);
        game->scene->addItem(square);
    }
}

void SquareBoard::setListOfBlockedSquares(int indexOfShip, int numOfSegments){
    for (int i = 1; i <= numOfSegments; ++i){
    if (indexOfShip%10 == 0){
        listOfBlockedSquares.append(indexOfShip-9);
        listOfBlockedSquares.append(indexOfShip-10);
        listOfBlockedSquares.append(indexOfShip+1);
        listOfBlockedSquares.append(indexOfShip+10);
        listOfBlockedSquares.append(indexOfShip+11);
    }
    else if (indexOfShip%10 == 9){
        listOfBlockedSquares.append(indexOfShip-11);
        listOfBlockedSquares.append(indexOfShip+9);
    }
    else {
        listOfBlockedSquares.append(indexOfShip-1);
        listOfBlockedSquares.append(indexOfShip-9);
        listOfBlockedSquares.append(indexOfShip-10);
        listOfBlockedSquares.append(indexOfShip-11);
        listOfBlockedSquares.append(indexOfShip+1);
        listOfBlockedSquares.append(indexOfShip+9);
        listOfBlockedSquares.append(indexOfShip+10);
        listOfBlockedSquares.append(indexOfShip+11);
    }
    }
}

void SquareBoard::clearBlockedSquares(int indexOfPickedShip){
    if (indexOfPickedShip == -2)
        listOfBlockedSquares.clear();
    else{
    if (indexOfPickedShip%10 == 0){
        listOfBlockedSquares.removeOne(indexOfPickedShip-9);
        listOfBlockedSquares.removeOne(indexOfPickedShip+11);
    }
    else if (indexOfPickedShip%10 == 9){
        listOfBlockedSquares.removeOne(indexOfPickedShip-11);
        listOfBlockedSquares.removeOne(indexOfPickedShip+9);
    }
    else {
        listOfBlockedSquares.removeOne(indexOfPickedShip-11);
        listOfBlockedSquares.removeOne(indexOfPickedShip-9);
        listOfBlockedSquares.removeOne(indexOfPickedShip+11);
        listOfBlockedSquares.removeOne(indexOfPickedShip+9);
    }
    }
}

