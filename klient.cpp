#include "klient.h"
#include "game.h"
#define PORT 5005
#define START "START"
#define SHORT_TIME 30
#define LONG_TIME 50



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

            if(game->isKlientReady == true && game->isServerReady == true){
                game->doneButton->doubleClicked();

            }

        messageToServer = game->message;
        if(messageToServer == "START"){
            sock->write_some(buffer(messageToServer, size));
            messageToServer = "default";
            game->message = "default";
        }else if(messageToServer == "INDEKS"){
            messageToServer = to_string(game->indexOfSquare);
            cout << "strezal oddany to" + messageToServer << endl;
            sock->write_some(buffer(messageToServer, size));
            game->message = "default";
        }else if(messageToServer == "END"){
            sock->write_some(buffer(messageToServer, size));
            messageToServer = "default";
            game->message = "default";
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
                game->isServerReady = true;
                messageFromServer = "default";

            }else if(messageFromServer == "END"){
                game->gameEnded = true;
                messageFromServer = "default";
            }
            else{
                game->shootReceived(messageFromServer);
                cout << "strezal otrzymany to" + messageFromServer << endl;


            \
        }
        boost::this_thread::sleep(boost::posix_time::millisec(LONG_TIME));
    }
}
}
