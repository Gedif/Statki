#include "klient.h"
#include "game.h"
#define PORT 5000
#define DEFAULT "default"
#define START "START"
#define SHORT_TIME 50
#define LONG_TIME 70
#define DEFAULT_INDEX "1000"



extern Game* game;
io_service service;
tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), PORT);


int Klient::startKlient()
{

    try
    {
        boost::thread_group threads;
        socket_ptr socket(new tcp::socket(service));
        socket->connect(endpoint);

        threads.create_thread(boost::bind(&Klient::readThread,this, socket));
        threads.create_thread(boost::bind(&Klient::writeThread,this, socket));
        threads.join_all();
    }
    catch (std::exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}



void Klient::writeThread(socket_ptr sock)
{
	int size = 32;
	for (;;){

            if(game->isKlientReady == true){
                messageToServer = START;
            }else{
                messageToServer = to_string(game->indexOfSquare);
            }

            if (messageToServer != DEFAULT_INDEX ){
                    sock->write_some(buffer(messageToServer, size));
            }

            messageToServer = DEFAULT;
            game->indexOfSquare = std::stoi(DEFAULT_INDEX);
            boost::this_thread::sleep(boost::posix_time::millisec(SHORT_TIME));
	}

}

void Klient::readThread(socket_ptr sock)
{

    int size = 32;
    int bytesRead = 0;
    char enemyOutput[1024] = { 0 };

	for (;;){

        if (sock->available()){

            bytesRead = sock->read_some(buffer(enemyOutput, size));
            string_ptr inMessage(new string(enemyOutput, bytesRead));
            messageFromServer = *inMessage;

            if(messageFromServer != DEFAULT){
                if(messageFromServer == START){
                    game->isServerReady = true;
                    if(game->isKlientReady == true && game->isServerReady == true){
                        game->doneButton->doubleClicked();
                        messageFromServer = DEFAULT;
                    }
                }else{
                    game->shootReceived(messageFromServer);
                    messageFromServer = DEFAULT;
                }

            }
            boost::this_thread::sleep(boost::posix_time::millisec(LONG_TIME));
        }

    }
}
