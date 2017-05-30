#include <QApplication>
#include "Game.h"


Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//raken

    game = new Game();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
