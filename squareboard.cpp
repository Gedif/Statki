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
    if (indexOfShip%10 == 0){
        listOfBlockedSquares.append(indexOfShip-9);
        listOfBlockedSquares.append(indexOfShip+11);
    }
    else if (indexOfShip%10 == 9){
        listOfBlockedSquares.append(indexOfShip-11);
        listOfBlockedSquares.append(indexOfShip+9);
    }
    else {
        listOfBlockedSquares.append(indexOfShip-11);
        listOfBlockedSquares.append(indexOfShip-9);
        listOfBlockedSquares.append(indexOfShip+11);
        listOfBlockedSquares.append(indexOfShip+9);
    }
}

void SquareBoard::clearBlockedSquares(int indexOfPickedShip){
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

void SquareBoard::checkNearby(int index){
    int LifePoints = squares.operator [](index)->getLifeOfShip();
    int nearby = 0;
    qDebug() << index;
    for (int j=0; j < game->list.count(); ++j){
        for (int i=0; i < game->list.count(); ++i){
            if (game->list[j]-10 == game->list[i]){
                nearby++;
                if (LifePoints < squares.operator [](game->list[j]-10)->getLifeOfShip() )
                    LifePoints = squares.operator [](game->list[j]-10)->getLifeOfShip();
            }
            else if (game->list[j]+10 == game->list[i]){
                nearby++;
                if (LifePoints < squares.operator [](game->list[j]+10)->getLifeOfShip() )
                    LifePoints = squares.operator [](game->list[j]+10)->getLifeOfShip();
            }
            else if (game->list[j]-1 == game->list[i]){
                nearby++;
                if (LifePoints < squares.operator [](game->list[j]-1)->getLifeOfShip() )
                    LifePoints = squares.operator [](game->list[j]-1)->getLifeOfShip();
            }
            else if (game->list[j]+1 == game->list[i]){
                nearby++;
                if (LifePoints < squares.operator [](game->list[j]+1)->getLifeOfShip() )
                    LifePoints = squares.operator [](game->list[j]+1)->getLifeOfShip();
            }
            else return;
            if (game->list[j] == 0){
                    squares.operator [](game->list[j])->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]+1)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]+10)->setLifeOfShip(nearby+LifePoints);
            }
            else if (game->list[j] < 10){
                    squares.operator [](game->list[j])->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]+1)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]+10)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]-1)->setLifeOfShip(nearby+LifePoints);
            }
            else if (game->list[j] > 10 && game->list[j] < 90){
                    squares.operator [](game->list[j])->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]-10)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]+10)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]-1)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]+1)->setLifeOfShip(nearby+LifePoints);
            }
            else if (game->list[j] == 99){
                    squares.operator [](game->list[j])->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]-10)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]-1)->setLifeOfShip(nearby+LifePoints);
            }
            else {
                    squares.operator [](game->list[j])->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]-10)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]-1)->setLifeOfShip(nearby+LifePoints);
                    squares.operator [](game->list[j]+1)->setLifeOfShip(nearby+LifePoints);
            }
        }
    }
}
