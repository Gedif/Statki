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
    void setListOfBlockedSquares(int index, int numOfSegments);
    void clearBlockedSquares();

    // public methods

    void placeSquares(int x, int y, int cols, int rows);
    //void checkNearby();
    void checkNearby(int index);

    //public attributes

    QList<Square*> squares;
    QList<int> listOfBlockedSquares;
    QList<int> ship1;
    QList<int> ship2;
    QList<int> ship3;
    QList<int> ship4;
private:
    void createSquaresColumn(int x, int y, int numOfRows);

};


#endif // SQUAREBOARD_H
