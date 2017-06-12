#include "game.h"
#include "button.h"
#include "square_board.h"
#include "dialog.h"
#include <QGraphicsTextItem>
#include <QDebug>
#include <QtGui>
#include "klient.h"
#include "Serwer.h"


Klient* client;
Serwer* host;

Game::Game(){
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);

    shipSinkedSound = new QMediaPlayer();
    shipSinkedSound->setMedia(QUrl("qrc:/Sounds/WilhemScream.wav"));
    bombSound = new QMediaPlayer();
    bombSound->setMedia(QUrl("qrc:/Sounds/bomb.wav"));
}

void Game::mouseMoveEvent(QMouseEvent *event){
    if (squareToPlace){
    squareToPlace->setPos(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
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
        squareToPlace = square;
        originalPos = square->pos();
}

void Game::placeShip(Square *squareToReplace){
    if ((squareBoard->listOfBlockedSquares.indexOf(squareBoard->getSquares().indexOf(squareToReplace))== -1 ||
         squareBoard->listOfBlockedSquares.isEmpty()) &&
         (squareBoard->squares.indexOf(squareToReplace)+ 10*squareToPlace->getLifeOfShip()) < 110){
        squareToPlace->setPos(squareToReplace->pos());
        squareBoard->setListOfBlockedSquares(squareBoard->getSquares().indexOf(squareToReplace),squareToPlace->getLifeOfShip());
        squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToReplace)) = squareToPlace;
        for (int i = 0; i < squareToPlace->getLifeOfShip(); ++i){
        squareBoard->squares.operator [](squareBoard->squares.indexOf(squareToPlace)+i*10) = squareToPlace;
        }
        squareToPlace->setIsPlaced(true);
    }
    else if ((squareBoard->listOfBlockedSquares.indexOf(squareBoard->getSquares().indexOf(squareToReplace))== -1 ||
              squareBoard->listOfBlockedSquares.isEmpty()) &&
              (squareBoard->squares.indexOf(squareToReplace)+ 10*squareToPlace->getLifeOfShip()) >= 110){
        QMessageBox::warning(this,"Złe ustawienie","Ustaw swoje statki w obrębie planszy");
        return;
    }
    else {
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
    if(listOfShootedInedxes.size() == list.size()){
        QMessageBox::information(this,"Info","KONIEC GRY");
        message = "END";
    }else if(gameEnded == true){
       QMessageBox::information(this,"Info","KONIEC GRY");
    }
    else if(whosTurn == "PLAYER1"){
        indexOfSquare = squareBoard->squares.indexOf(squareToShoot);
        if(indexOfSquare >= 100 && !listOfShootedInedxes.contains(indexOfSquare)){
        message = "INDEKS";
        temporaryShot = indexOfSquare;
        }else{
           QMessageBox::information(this,"Info","Nie mozesz tutaj strzelac");
        }
    }

}

void Game::shootReceived(string indexReceived){
    qDebug() << "lista" << list;
    if(whosTurn.toStdString() == "PLAYER2"){
        if (list.contains(std::stoi(indexReceived)-100) &&
           (1 == squareBoard->squares.operator [](std::stoi(indexReceived)-100)->getLifeOfShip())){
                QBrush brush;
                brush.setStyle(Qt::SolidPattern);
                brush.setColor(Qt::red);
                squareBoard->squares.operator[](std::stoi(indexReceived)-100)->setBrush(brush);
                message = "INDEKS";
                indexOfSquare = 0;
                }
            else if (list.contains(std::stoi(indexReceived)-100) &&
                     squareBoard->squares.operator [](std::stoi(indexReceived)-100)->getLifeOfShip() > 1){
                QBrush brush;
                brush.setStyle(Qt::SolidPattern);
                if(squareBoard->squares.operator [](std::stoi(indexReceived)-100)->getLifeOfShip() == 4){
                brush.setColor(Qt::darkYellow);
                }
                else if(squareBoard->squares.operator [](std::stoi(indexReceived)-100)->getLifeOfShip() == 3){
                brush.setColor(Qt::yellow);
                }
                else if(squareBoard->squares.operator [](std::stoi(indexReceived)-100)->getLifeOfShip() == 2){
                brush.setColor(Qt::darkRed);
                }
                squareBoard->squares.operator [](std::stoi(indexReceived)-100)->
                setLifeOfShip(squareBoard->squares.operator [](std::stoi(indexReceived)-100)->getLifeOfShip()-1);
                squareBoard->squares.operator[](std::stoi(indexReceived)-100)->setBrush(brush);
                message = "INDEKS";
               indexOfSquare = (squareBoard->squares.operator [](std::stoi(indexReceived)-100)->getLifeOfShip());
            }
            else{
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::green);
            squareBoard->squares.operator[](std::stoi(indexReceived)-100)->setBrush(brush);
            message = "INDEKS";
            indexOfSquare = 5;
            cout << "zmiana tur zielony" << endl;
            changeTurn();
         }
    }else
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if(std::stoi(indexReceived) == 0){
            listOfShootedInedxes.append(temporaryShot);
            brush.setColor(Qt::red);
            squareBoard->squares.operator[](temporaryShot)->setBrush(brush);
            if(shipSinkedSound->state()==QMediaPlayer::PlayingState){
                    shipSinkedSound->setPosition(0);
                }
            else if(shipSinkedSound->state()==QMediaPlayer::StoppedState){
                    shipSinkedSound->play();
                }
        }else if(std::stoi(indexReceived) > 0 && std::stoi(indexReceived) < 5){
            listOfShootedInedxes.append(temporaryShot);
            brush.setColor(Qt::yellow);
            squareBoard->squares.operator[](temporaryShot)->setBrush(brush);
            if(bombSound->state()==QMediaPlayer::PlayingState){
                    bombSound->setPosition(0);
                }
            else if(bombSound->state()==QMediaPlayer::StoppedState){
                    bombSound->play();
                }
        }else{
            brush.setColor(Qt::green);
            squareBoard->squares.operator[](temporaryShot)->setBrush(brush);
            cout << "zmiana tur" << endl;
            changeTurn();
        }
    }
    if(listOfShootedInedxes.size() == list.size()){
       // endScreen();
       // close();

        cout <<"koniec" << endl;
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
    squareBoard->clearBlockedSquares();
    ship1 = new CreateShip();
    ship1->placeSquares(600,20,1,4);
    ship2 = new CreateShip();
    ship2->placeSquares(600,20+50*2,2,3);
    ship3 = new CreateShip();
    ship3->placeSquares(600,20+50*4,3,2);
    ship4 = new CreateShip();
    ship4->placeSquares(600,20+50*6,4,1);
    // create the clear button
    clearButton = new Button(QString("Clear Setup"));
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
    connect(doneButton,SIGNAL(clicked()),this,SLOT(readyGame()));

    scene->addItem(doneButton);
}

void Game::readyGame(){
    list = getStates(squareBoard);
    if(list.size() != 20){
    scene->removeItem(doneButton);
    scene->removeItem(clearButton);
    // create the done placing ships button
    Button* mainButton = new Button(QString("Back to main menu"));
    int dxPos = this->width()/2 - mainButton->boundingRect().width()/2;
    int dyPos = 600;
    mainButton->setPos(dxPos,dyPos);
    connect(mainButton,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    scene->addItem(mainButton);

        if(pickedKlient == 0){
            isKlientReady = true;
            whosTurn = "PLAYER2";
        }else{
            isServerReady = true;

            whosTurn = "PLAYER1";
        }
        displayGameWindow();
        QMessageBox::information(this,"Info","Wait for your opponent");
    }else{
        QMessageBox::information(this,"Info","Not all ships are placed");
    }
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


    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displayGameWindow(){
    //list = getStates(squareBoard);
    squareBoard->placeSquares(520,10,10,10);
}

void Game::displayLoggWindow(){
    Dialog MyDialog;
    MyDialog.setModal(true);
    MyDialog.exec();
    pickedKlient = MyDialog.getPickedKlient();
    if(pickedKlient == 0){
        client = new Klient();
        boost::thread t2{&Klient::startKlient,client};
    }else{
         host = new Serwer();
         boost::thread t2{&Serwer::startSerwer,host};
     }
}

QList<int> Game::getStates(SquareBoard* board){
    list.clear();
    for (int i = 0; i < board->getSquares().size(); ++i) {
        if (board->getSquares().at(i)->getState() > 0)
            list.append(i);
         }
    return list;
}
