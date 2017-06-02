#include <QApplication>
#include "Game.h"
#include "Klient.h"
#include "Serwer.h"

Game* game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     cout << "rak1" << endl;
    Serwer* serw = new Serwer();
     cout << "rak2" << endl;
    serw->startSerwer();
     cout << "rak3" << endl;
    //Klient* kli = new Klient();
    cout << "rak4" << endl;
    //kli -> startKlient();
    cout << "rak5" << endl;
    game = new Game();
    game->show();
    game->displayMainMenu();


    return a.exec();
}
