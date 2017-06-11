#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include "QBrush"
#include <QRectF>
#include <QVector>
#include <QDebug>


/**
 * @brief Enum stanu kwadratu.

 */
enum state
{
    UNKNOWN,
    SHIP
};
/**
 * @brief Klasa Square.
 *
 * Klasa odpowiadająca pojęciu statku. Jest rozszerzeniem QGraphicsREctItem. Odpowiada za
 * stan, życie oraz umiejscowanie danego kwadratu.
 */
class Square: public QGraphicsRectItem{
public:
    /**
     * @brief Konstruktor klasy Square
     * @param parent klasa bazowa po której Square rozszerza.
     */
    Square();
    /**
     * @brief Getter zwracająca stan danego kwadratu.
     *
     */
    int getState();
    /**
     * @brief Getter zwracający flagę określająca czy kwadrat jest juz umiejscowiony.
     *
     */
    bool getIsPlaced();
    /**
     * @brief Getter zwracająca życie statku.
     *
     */
    int getLifeOfShip();
    /**
     * @brief Metoda odpowiadajaca za zdarzenie jakim jest kliknięcie myszką.
     * @param event Zdarzenie.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief Setter ustawiajacy stan kwadratu.
     * @param stateOfSquare stan kwadratu
     */
    void setState(state satateOfSquare);
    /**
     * @brief Settter ustawiający flagę połozenia kwadratu.
     * @param isIt flaga położenia
     */
    void setIsPlaced(bool isIt);
    /**
     * @brief Setter ustawiajacy punkty życia
     * @param health_pints punkty życia
     */
    void setLifeOfShip(int health_points);


private:
    /**
     * @brief Punkty życia, domyślnie ustawione na 0.
     *
     */
    int lifeOfSship_ = 0;
    /**
     * @brief Flaga mówiąca o ułożeniu
     *
     */
    bool isPlaced = false;
    /**
     * @brief Własciciel.
     *
     */
    QString owner;
    /**
     * @brief Stan kwadratu.
     *
     */
    state state_;
};

#endif // SQUARE_H
