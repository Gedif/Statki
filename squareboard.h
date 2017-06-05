#ifndef SQUAREBOARD_H
#define SQUAREBOARD_H


#include <QList>
#include "Square.h"
#include "QBrush"
/**
 * @brief The SquareBoard class.
 *
 * @note to  jest notka
 *
 * @param x
 *
 * @return
 *
 * @author Mateusz
 */
class SquareBoard{
public:
    // constructors
    SquareBoard();

    // getters/setters
    QList<Square*> getSquares();
    QList<int> getListOfBlockedSquares(); ///<fhf
    void setListOfBlockedSquares(int indexOfShip);
    void clearBlockedSquares(int indexOfPickedShip);

    // public methods

    void placeSquares(int x, int y, int cols, int rows,state state);
    void checkNearby(int index);

    //public attributes

    QList<Square*> squares;
    QList<int> listOfBlockedSquares;
private:
    int nearby;
    void createSquaresColumn(int x, int y, int numOfRows,state state);

};


#endif // SQUAREBOARD_H
