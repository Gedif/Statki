#include "Game.h"
#include "Button.h"
#include "squareboard.h"
#include "Dialog.h"
#include <QGraphicsTextItem>
#include <QDebug>

#include "Klient.h"
#include "Serwer.h"



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
        squareToPlace = square;
        originalPos = square->pos();
}

void Game::placeShip(Square *squareToReplace){
    //replaces the specified square with the square to place
    qDebug() << "statek przed" << squareBoard->getSquares().indexOf(squareToPlace);

    qDebug() << "index to replace"<< squareBoard->getSquares().indexOf(squareToReplace);
    qDebug() << squareBoard->listOfBlockedSquares.isEmpty();
    if (squareBoard->listOfBlockedSquares.indexOf(squareBoard->getSquares().indexOf(squareToReplace))== -1 || squareBoard->listOfBlockedSquares.isEmpty() ){
        squareToPlace->setPos(squareToReplace->pos());
        //block corner squares
        squareBoard->setListOfBlockedSquares(squareBoard->getSquares().indexOf(squareToReplace),squareToPlace->getLifeOfShip());
        qDebug() << squareBoard->listOfBlockedSquares;

        //replace
        squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToReplace)) = squareToPlace;
        qDebug() << "index square to place" << squareBoard->squares.indexOf(squareToPlace);
        for (int i = 0; i < squareToPlace->getLifeOfShip(); ++i){
        squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToPlace)+i*10) = squareToPlace;
        qDebug() << "index square to place" << squareBoard->squares.indexOf(squareToPlace);
        //squareBoard->checkNearby(squareBoard->getSquares().indexOf(squareToPlace));
        qDebug() << "index square to replace" << squareBoard->squares.indexOf(squareToReplace);
        }
        //squareBoard->getSquares().removeAll(squareToReplace);
        //scene->removeItem(squareToReplace);

        qDebug() << "stan statek" << squareToPlace->getState();
        qDebug() << "hp statek" << squareToPlace->getLifeOfShip();
        //squareToPlace->setIsPlaced(true);
        squareToPlace->setIsPlaced(true);
        //list = getStates(squareBoard);


    }
    else{

    qDebug() << "nie można";
    return;
    }
    squareToPlace = NULL;    
}

void Game::shoot(Square *squareToShoot){
    qDebug() << squareBoard->squares.indexOf(squareToShoot);
    qDebug() << squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToShoot)-100)->getLifeOfShip();
    if (squareBoard->squares.indexOf(squareToShoot) < 100 ){
        return;
    }
    else if (list.contains(squareBoard->squares.indexOf(squareToShoot)-100) &&

             (counter == squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToShoot)-100)->getLifeOfShip())){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        squareToShoot->setBrush(brush);
        counter = 1;
        }
    else if (list.contains(squareBoard->squares.indexOf(squareToShoot)-100) &&
             squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToShoot)-100)->getLifeOfShip() > 1 &&
             (counter < squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToShoot)-100)->getLifeOfShip())){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::yellow);
        squareToShoot->setBrush(brush);
        counter++;

    }
    else{
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::green);
        squareToShoot->setBrush(brush);
    }
}


void Game::shootAdd(Square *squareToShoot){
    if(whosTurn == "PLAYER1"){

        indexOfSquare = squareBoard->squares.indexOf(squareToShoot);
        cout << indexOfSquare << endl;
        temporaryShot = indexOfSquare;
    }

}

void Game::shootReceived(string indexReceived){

    if(whosTurn.toStdString() == "PLAYER2"){
        if (list.contains(std::stoi(indexReceived)-100)){
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::red);
            Square* squareShooted = new Square();
            squareShooted->setPos(squareBoard->squares.operator[](std::stoi(indexReceived)-100)->pos());
            squareShooted->setBrush(brush);
            indexOfSquare = std::stoi(indexReceived);

        }else{
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::green);
            squareBoard->squares.operator[](std::stoi(indexReceived)-100)->setBrush(brush);
            indexOfSquare = std::stoi(indexReceived) + OFFSET;
         }
    }else{
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if(std::stoi(indexReceived) == temporaryShot){
            brush.setColor(Qt::red);
            squareBoard->squares.operator[](std::stoi(indexReceived))->setBrush(brush);
            //changeTurn();
        }else{
            brush.setColor(Qt::green);
            squareBoard->squares.operator[](std::stoi(indexReceived)-OFFSET)->setBrush(brush);
            //changeTurn();
        }

    }
}

QString Game::getWhosTurn(){
return whosTurn;
}

void Game::changeTurn(){
    if(whosTurn == "NOONE" || whosTurn == "PLAYER1"){
    whosTurn = "PLAYER2";
    }
    else{
    whosTurn = "PLAYER1";
    }
}



void Game::start(){


    scene->clear();
    whosTurn = "NOONE";

    squareBoard = new SquareBoard();
    squareBoard->placeSquares(10,10,10,10);
    squareBoard->clearBlockedSquares(-2);

    ship1 = new CreateShip();
    ship1->placeSquares(600,20,1,4);
    ship2 = new CreateShip();
    ship2->placeSquares(600,20+50*2,2,3);
    ship3 = new CreateShip();
    ship3->placeSquares(600,20+50*4,3,2);
    ship4 = new CreateShip();
    ship4->placeSquares(600,20+50*6,4,1);

    // create the clear button
    Button* clearButton = new Button(QString("Clear Setup"));
    int bxPos = this->width()/2 - clearButton->boundingRect().width()/2;
    int byPos = 600;
    clearButton->setPos(bxPos,byPos);
    connect(clearButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(clearButton);

    // create the done placing ships button
    doneButton = new Button(QString("Done"));
    int dxPos = this->width()/2 - doneButton->boundingRect().width()/2 + 250;
    int dyPos = 600;
    doneButton->setPos(dxPos,dyPos);

    connect(doneButton,SIGNAL(clicked()),this,SLOT(startGame()));

    scene->addItem(doneButton);

}

void Game::startGame(){
    isReady = true;
    if(pickedKlient  == 0){
    whosTurn = "PLAYER2";
    }else{
     whosTurn = "PLAYER1";
    }
    displayGameWindow();
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
    connect(playButton,SIGNAL(clicked()),this,SLOT(displayLoggWindow()));
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

void Game::displayGameWindow(){
    list = getStates(squareBoard);
    qDebug() << "Lista indeksów:" << list;

    //squareBoard->checkNearby();

    squareBoard->placeSquares(520,10,10,10);

}

void Game::displayLoggWindow(){
    Dialog MyDialog;
    MyDialog.setModal(true);
    MyDialog.exec();


    pickedKlient = MyDialog.getPickedKlient();
    if(pickedKlient == 0){
        ipAdress = MyDialog.getIpAdress();
        port = MyDialog.getPort();
        Klient* kli = new Klient();
        kli->setIpadress(ipAdress.toStdString());
        kli->setPort(port.toInt());
       boost::thread t2{&Klient::startKlient,kli};
    }else{
        port = MyDialog.getPort();
         Serwer* ser = new Serwer();
         ser->setPort(port.toInt());
         boost::thread t2{&Serwer::startSerwer,ser};

     }

}

QList<int> Game::getStates(SquareBoard* board){
    list.clear();
    for (int i = 0; i < board->getSquares().size(); ++i) {
        if (board->getSquares().at(i)->getState() == 3)
            list.append(i);
         }
    return list;
}


