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
    /**
     * @brief KMetoda pobierajaca kwadraty.
     *
     */
    QList<Square*> getSquares();
    /**
     * @brief Metoda pobierająca indeksy zablokowanych kwadratów.
     *
     */
    QList<int> getListOfBlockedSquares();
    /**
     * @brief Setterustawiajacy listę blokowanych kwadratów.
     *
     * @param index Indeks kwadratu.
     * @param numOfSegments Liczba kwasdratów w ciagu.
     *
     */
    void setListOfBlockedSquares(int index, int numOfSegments);
    /**
     * @brief Metoda czyszczaca zablokowane kwadraty.
     *
     */
    void clearBlockedSquares();
    /**
     * @brief Metoa ustawiajaca kwadraty.
     *
     * @param x Współrzędna x.
     * @param y Współrzędna y.
     * @param cols Kolumny
     * @param rows Wiersze.
     *
     */
    void placeSquares(int x, int y, int cols, int rows);
    /**
     * @brief Metoda sprawdzająca okolice danego indeksu.
     *
     */
    void checkNearby(int index);
    /**
     * @brief Lista utworzonych kwadratów.
     *
     */
    QList<Square*> squares;
    /**
     * @brief Lista zablokowanych kwadratów na których nie można stawiać innych statków,tworzą obramowwanie na około postawionego statku.
     *
     */
    QList<int> listOfBlockedSquares;

private:
    /**
     * @brief Metoda tworząca kolumny kwadratów.
     *
     */
    void createSquaresColumn(int x, int y, int numOfRows);
};

#endif // SQUAREBOARD_H
