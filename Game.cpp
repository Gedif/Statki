#include "Game.h"
#include "Button.h"
#include "squareboard.h"
#include <QGraphicsTextItem>
#include <QDebug>


Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);
}

void Game::mouseMoveEvent(QMouseEvent *event){
    if (squareToPlace){
    squareToPlace->setPos(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}
void Game::mousePressEvent(QMouseEvent *event){
    // make right click return squareToPlace to originalPos
    if (event->button() == Qt::RightButton){
        if (squareToPlace){
            squareToPlace->setPos(originalPos);
            squareToPlace = NULL;
            return;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void Game::pickUpShip(Square* square){
    //pick up specified ship
    if (squareToPlace == NULL){
    squareToPlace = square;
    originalPos = square->pos();
   // squareToPlace->setIsPlaced(true);
    return;
    }
}

void Game::placeShip(Square *squareToReplace){
    //replaces the specified square with the square to place
   // qDebug() << "dupa" << squareBoard->getSquares();
    squareToPlace->setPos(squareToReplace->pos());
    squareBoard->getSquares().removeAll(squareToReplace);
    squareToPlace->setState(ship);
    qDebug() << "resdaada" << squareToPlace->getState();
    squareBoard->getSquares().append(squareToPlace);
    qDebug() << "a" << squareToPlace->getState();
    qDebug() << "resdaada" << squareBoard->getSquares().at(0)->getState();
    //scene->removeItem(squareToReplace);
    squareToPlace->setIsPlaced(true);
    squareToPlace = NULL;

    //removeUsedShip
}

void Game::start(){
    // clear the screen
    scene->clear();
        qDebug() << "dupa";
    // test code TODO remove

    squareBoard = new SquareBoard();
    squareBoard->placeSquares(10,10,10,10,unknown);

    ship1 = new CreateShip();
    ship1->placeSquares(600,20,1);
    ship2 = new CreateShip();
    ship2->placeSquares(600,20+50*2,2);
    ship3 = new CreateShip();
    ship3->placeSquares(600,20+50*4,3);
    ship4 = new CreateShip();
    ship4->placeSquares(600,20+50*6,4);

    // create the back button
    Button* backButton = new Button(QString("Back"));
    int bxPos = this->width()/2 - backButton->boundingRect().width()/2;
    int byPos = 600;
    backButton->setPos(bxPos,byPos);
    connect(backButton,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    scene->addItem(backButton);

    // create the done placing ships button
    Button* doneButton = new Button(QString("Done"));
    int dxPos = this->width()/2 - doneButton->boundingRect().width()/2 + 250;
    int dyPos = 600;
    doneButton->setPos(dxPos,dyPos);
    connect(doneButton,SIGNAL(clicked()),this,SLOT(displayGameWindow()));
    scene->addItem(doneButton);

}

void Game::RulesWindow(){
    // clear the screen
    scene->clear();
    // create the rules text
    QGraphicsTextItem* rulesText = new QGraphicsTextItem(QString("Rules"));
    QFont rulesFont("comic sans",50);
    rulesText->setFont(rulesFont);
    int rxPos = this->width()/2 - rulesText->boundingRect().width()/2;
    int ryPos = 150;
    rulesText->setPos(rxPos,ryPos);
    scene->addItem(rulesText);

    // create the back button
    Button* backButton = new Button(QString("Back"));
    int bxPos = this->width()/2 - backButton->boundingRect().width()/2;
    int byPos = 600;
    backButton->setPos(bxPos,byPos);
    connect(backButton,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    scene->addItem(backButton);

}

void Game::displayMainMenu(){
    scene->clear();
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Battleship"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // creat the rules button
    Button* rulesButton = new Button(QString("Rules"));
    int rxPos = this->width()/2 - rulesButton->boundingRect().width()/2;
    int ryPos = 350;
    rulesButton->setPos(rxPos,ryPos);
    connect(rulesButton,SIGNAL(clicked()),this,SLOT(RulesWindow()));
    scene->addItem(rulesButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 425;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displayGameWindow()
{
    list = getStates(squareBoard);
    qDebug() << "da" << list;

    //squareBoard->placeSquares(520,10,10,10,unknown);

}

QList<int> Game::getStates(SquareBoard* board){
    for (int i = 0; i < board->getSquares().size(); ++i) {
        qDebug() << "rea" << i << board->getSquares().at(i)->getState();
        if (board->getSquares().at(i)->getState() == 3)
            list.append(i);
         }

    return list;
}
