#include <QApplication>
#include "game.h"

Game* game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->displayMainMenu();

    return a.exec();
}

void rungame(){
    if(game->pickedKlient == 0){
        Klient* kli = new Klient();
        boost::thread t2{&Klient::startKlient,kli};
    }
    else{
        Serwer* ser = new Serwer();
        boost::thread t2{&Serwer::startSerwer,ser};
    }
}
