#include <QApplication>
#include "Game.h"
#include "Klient.cpp"

//Klient* klie;
Game* game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //aleOSoChozi

    game = new Game();
    game->show();
    game->displayMainMenu();
   // klie = new Klient();
    //klie->startKlient();
    return a.exec();
}
