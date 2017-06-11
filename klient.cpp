#include "klient.h"
#include "game.h"
#define PORT 5000
#define DEFAULT 1000
#define START "START"
#define SHORT_TIME 50
#define LONG_TIME 70



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
            cout << "wiadomosc start wysłana" << endl;
            sock->write_some(buffer(messageToServer, size));
        }else if(messageToServer =="INDEKS"){
            messageToServer = "INDEKS";
            sock->write_some(buffer(messageToServer, size));
            messageToServer = to_string(game->indexOfSquare);
            sock->write_some(buffer(messageToServer, size));
            game->indexOfSquare = 1000;
        }else if(messageToServer =="LIFE"){
            messageToServer = "LIFE";
            sock->write_some(buffer(messageToServer, size));
            messageToServer = to_string(game->indexOfSquare);
            sock->write_some(buffer(messageToServer, size));
        }

        //messageToServer = DEFAULT;
        boost::this_thread::sleep(boost::posix_time::millisec(SHORT_TIME));
	}

}


void Klient::setMessageToServer(const string &value)
{
    messageToServer = value;
}

string Klient::getMessageFromServer() const
{
    return messageFromServer;
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


            if(messageFromServer == START){
                cout << "wiadomosc start odebrana" << endl;
                game->isServerReady = true;
                if(game->isKlientReady == true && game->isServerReady == true){
                    game->doneButton->doubleClicked();
                    messageFromServer = DEFAULT;
                }
            }
            else if(messageFromServer == "INDEKS" ){
                game->shootReceived(messageFromServer);
                messageFromServer = DEFAULT;
            }else if(messageFromServer == "LIFE" ){
                game->shootReceived(messageFromServer);
                messageFromServer = DEFAULT;
            }


            boost::this_thread::sleep(boost::posix_time::millisec(LONG_TIME));
        }

    }
}
