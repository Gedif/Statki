#ifndef CREATESHIP_H
#define CREATESHIP_H

#include <QList>
#include "square.h"
#include "QBrush"

/**
 * @brief Klasa create_ship.
 *
 * Klasa odpowiada za utworzenie statków dziedziczących po klasie Square.
 * Obiekt ten tworzy prostokąt o odpowiedniej szerokości .
 */

class CreateShip: public Square{
public:
    /**
     * @brief Konstruktor klasy create_ship
     *
     * Stworzony obiekt jest pusty dopiero metoda tworząca i rozmieszczająca statki na planszy
     * sprawia, że obiekt tej klasy tworzy listę kwadratów składających się na statek oraz liczbę
     * segmentów w danym statku
     */
    CreateShip();

    /**
     * @brief Getter statków skłądających się na obiekt
     *
     * Zwraca listę obiekrtów klasy Square, które składają się na statek
     */
    QList<Square*> getShips();
    int getNumOfSegments();
    void setNumOfSegments(int num);

    /**
     * @brief Publiczna metoda
     *
     * Rozmieszcza daną ilość kwadratów w danym miejscu sceny
     * @param x Argument to pozycja x
     * @param y Argument to pozycja y
     * @param num_of_segment Argument to liczba segmentów statku
     * @param numOfShips Argument to liczba statków
     */
    void placeSquares(int x, int y, int numOfSegment, int numOfShips);

private:
    QList<Square*> ships;
    int numOfSegments;
};


#endif // CREATESHIP_H
