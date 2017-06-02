#include <QApplication>
#include "Game.h"
#include "Klient.h"
#include "Serwer.h"

Game* game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Serwer* serw = new Serwer();
    boost::thread t1{&Serwer::startSerwer,serw};
   // Klient* kli = new Klient();
    //boost::thread t2{&Klient::startKlient,kli};


    game = new Game();
    game->show();
    game->displayMainMenu();


    return a.exec();
}
