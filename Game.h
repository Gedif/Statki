#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "squareboard.h"
#include "Square.h"
#include "CreateShip.h"
#include <QTextEdit>
#include <QDialog>
#include <QString>

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
    //void removeUsedShip(Square square, int quantity);
    // public attributes

    QString ipAdress;
    QString port;
    bool pickedKlient;
    QList<int> list;
    QGraphicsScene* scene;
    SquareBoard* squareBoard;
    CreateShip* ship1;
    CreateShip* ship2;
    CreateShip* ship3;
    CreateShip* ship4;
    QString whosTurn;
    //QList<Square*> squares;
    QPointF originalPos;
    Square* squareToPlace = NULL;
public slots:
    void start();
    void RulesWindow();
    void displayMainMenu();
    void displayGameWindow();
    void displayLoggWindow();
};

#endif // GAME_H
