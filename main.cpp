<<<<<<< HEAD
#include <QApplication>
#include "Game.h"


Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //aleOSoChozi
    game = new Game();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
=======
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
>>>>>>> 47dc5de93a46a2f7e4f41a938b3187e6dec262cd
