#ifndef CREATESHIP_H
#define CREATESHIP_H

#include <QList>
#include "square.h"
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
    void placeSquares(int x, int y, int num_of_segment, int numOfShips);

private:
    QList<Square*> ships;
    int numOfSegments;
};


#endif // CREATESHIP_H
