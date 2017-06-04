#include <QApplication>
#include "Game.h"
#include "Klient.h"
#include "Serwer.h"

Game* game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



   Klient* kli = new Klient();
    kli->setIpadress("127.0.0.1");
    kli->setPort(7002);
   boost::thread t2{&Klient::startKlient,kli};


    //Serwer* ser = new Serwer();
   // ser->setPort(7000);
    //boost::thread t2{&Serwer::startSerwer,ser};

    game = new Game();
    game->show();
    game->displayMainMenu();

    return a.exec();
}

void rungame(){
    if(game->pickedKlient == 0){
        Klient* kli = new Klient();
        kli->setIpadress(game->ipAdress.toStdString());
        kli->setPort(game->port.toInt());
        boost::thread t2{&Klient::startKlient,kli};

    }else{
        Serwer* ser = new Serwer();
        ser->setPort(game->port.toInt());
        boost::thread t2{&Serwer::startSerwer,ser};

    }

}

