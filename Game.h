#ifndef GAME_H
#define GAME_H
#include "button.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <string>
#include <QTextEdit>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QApplication>
#include "square_board.h"
#include "square.h"
#include "create_ship.h"
#include "button.h"
#include "dialog.h"
#include "klient.h"
#include "Serwer.h"

/**
 * @brief Klasa game.
 *
 * Klasa odpowiada za całą mechanikę gry oraz zmianę sceny i elementów na niej występujących
 *
 */
class Game: public QGraphicsView{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy game.
     *
     * Ustawia wielkość okna oraz ustala scene w tej samej pozycji co okno
     *
     */
    Game();

    /**
     * @brief Event
     *
     * Jeśli kwadrat został podniesiony to ma przenosić się razem z ruchami myszy
     *
     */
    void mouseMoveEvent(QMouseEvent* event);
    void Game::mousePressEvent(QMouseEvent *event);

    // public methods


    QList<int> getStates(SquareBoard* board);
    /**
     * @brief Metoda podnosząca statek
     *
     * Podnosi statek i zapisuje sobie jego pierwotną pozycję .
     * Lewy przycisk myszy sprawia, że statek wraca na pierwotną pozycję.
     *
     */
    void pickUpShip(Square* square);
    /**
     * @brief Metoda umieszczająca statek na planszy
     *
     * Umieszcza statek na planszy oraz blokuje możliwość położenia nowego statku w okolicy
     *
     */
    void placeShip(Square *squareToReplace);
    void shoot(Square* squareToShoot);   
    /**
     * @brief Metoda strzelająca
     *
     * Strzela w wybrany punt na planszy i sprawdza czy jest tam statek,
     * jesli statek się tam znajduje zmienia kolor kwadratu na czerwony na planszy strzelającego
     *
     *
     *
     */
    void shootAdd(Square* squareToShoot);
    /**
     * @brief Metoda przekazujaca strzał odebrany
     *
     * Strzela w wybrany punt na planszy i sprawdza czy jest tam statek,
     * Statek po stronie odbierającego zmienia swój kolor zaleznie od liczby punktów zdrowia które mu pozostały.
     *
     *
     */
    void shootReceived(std::string index);
    /**
     * @brief Metoda zmieniająca truę
     *
     * Zmienia turę gracza z PLAYER1 na PLAYER2 i odwrotnie
     *
     */
    void changeTurn();
    const int OFFSET = 1;
    // public attributes
    string message = "default";
    int indexOfSquare = 1000;
    int temporaryShot;
    int counter = 1;
    bool pickedKlient;
    bool gameEnded = false;
    bool isKlientReady = false;
    bool isServerReady = false;
    QString getWhosTurn();
    QString ipAdress;
    QList<int> list;
    QList<int> listOfShootedInedxes;
    QGraphicsScene* scene;
    SquareBoard* squareBoard;
    CreateShip* ship1;
    CreateShip* ship2;
    CreateShip* ship3;
    CreateShip* ship4;
    QString whosTurn;
    QPointF originalPos;
    Square* squareToPlace = NULL;
     //to edit
    Button* doneButton;

    int getPort();
    void setPort(int value);

public slots:
    /**
     * @brief Modyfikacja sceny służąca do układania statków
     *
     * Zmienia scenę tak aby można było układać statki na planszy
     *
     */
    void start();
    void readyGame();
    /**
     * @brief Modyfikacja sceny służąca do wyświetlenia końca gry dla wygranego
     *
     * Oznajmia koniec gry
     *
     */
    void endScreen();
    /**
     * @brief Modyfikacja sceny służąca do wyświetlenia końca gry dla wygranego
     *
     * Oznajmia koniec gry
     *
     */
    void displayMainMenu();
    /**
     * @brief Modyfikacja sceny służąca prowadzenia właściwej gry
     *
     */
    void displayGameWindow();
    /**
     * @brief Wyświetla okno dialogowe służące do wyboru opcji prowadzenia gry klient/serwer
     *
     */
    void displayLoggWindow();
    void startGame();
private:
    int port;
};

#endif // GAME_H
