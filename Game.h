#ifndef GAME_H
#define GAME_H
#include "Button.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <string>
#include <QTextEdit>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QGraphicsTextItem>
#include "squareboard.h"
#include "Square.h"
#include "CreateShip.h"
#include "Button.h"
#include "squareboard.h"
#include "Dialog.h"
#include "Klient.h"
#include "Serwer.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    //events
    void mouseMoveEvent(QMouseEvent* event);
    void Game::mousePressEvent(QMouseEvent *event);

    // public methods


    QList<int> getStates(SquareBoard* board);
    void pickUpShip(Square* square);
    void placeShip(Square *squareToReplace);
    void shoot(Square* squareToShoot);   
    void shootAdd(Square* squareToShoot);
    void shootReceived(std::string index);
    void changeTurn();
    const int OFFSET = 1;
    // public attributes
    int indexOfSquare = 1000;
    int temporaryShot;
    int counter = 1;
    bool pickedKlient;
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
    Button* doneButton;

    int getPort() const;
    void setPort(int value);

public slots:
    void start();
    void readyGame();
    void endScreen();
    void RulesWindow();
    void displayMainMenu();
    void displayGameWindow();
    void displayLoggWindow();
    void startGame();
private:
    int port;
};

#endif // GAME_H
