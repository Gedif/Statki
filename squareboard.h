#ifndef SQUAREBOARD_H
#define SQUAREBOARD_H


#include <QList>
#include "Square.h"
#include "QBrush"

class SquareBoard{
public:
    // constructors
    SquareBoard();

    // getters/setters
    QList<Square*> getSquares();

    //public attributes

    // public methods

    void placeSquares(int x, int y, int cols, int rows,state state);

private:
    void createSquaresColumn(int x, int y, int numOfRows,state state);
    QList<Square*> squares;
};


#endif // SQUAREBOARD_H
