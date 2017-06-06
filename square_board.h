#ifndef SQUAREBOARD_H
#define SQUAREBOARD_H


#include <QList>
#include "square.h"
#include "QBrush"

/**
 * @brief Klasa odpowiadajaca za plansze do gry. Tworzy serię kwadratów na których toczy się rozgrywka.
 *
 *
 */
class SquareBoard{
public:
    /**
     * @brief Konstruktor klasy SquareBoard.
     *
     */
    SquareBoard();

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

private:
    void createSquaresColumn(int x, int y, int numOfRows);
};

#endif // SQUAREBOARD_H
