#ifndef CREATESHIP_H
#define CREATESHIP_H

#include <QList>
#include "Square.h"
#include "QBrush"

class CreateShip: public Square{
public:
    // constructors
    CreateShip();

    // getters/setters
    QList<Square*> getShips();
    int getNumOfSegments();
    void setNumOfSegments(int num);

    // public methods
    void placeSquares(int x, int y, int numOfSegments);

private:
    QList<Square*> ships;
    int numOfSegments;
};


#endif // CREATESHIP_H
