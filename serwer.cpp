#include "Serwer.h"
#include "klient.h"
#include "game.h"
#define PORT 5005
#define DEFAULT 1000
#define START "START"
#define SHORT_TIME 30
#define LONG_TIME 50


extern Game* game;
io_service service2;
tcp::acceptor acceptor(service2, tcp::endpoint(tcp::v4(),PORT));

int Serwer:: startSerwer()
{
    try
    {
        socket_ptr clientSock(new tcp::socket(service2));
        acceptor.accept(*clientSock);
    
        boost::thread_group threads;
        threads.create_thread(boost::bind(&Serwer::readThread,this,boost::ref(clientSock)));
        boost::this_thread::sleep(boost::posix_time::millisec(SHORT_TIME));
        threads.create_thread(boost::bind(&Serwer::writeThread,this,boost::ref(clientSock)));
        boost::this_thread::sleep(boost::posix_time::millisec(SHORT_TIME));
        threads.join_all();
    }
    catch (std::exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}



void Serwer::readThread(socket_ptr clientSock)
{
    int size = 32;
    int bytesRead = 0;
    char enemyOutput[1024] = { 0 };
    string inMessage;

    for (;;){
        if (clientSock->available()){
            
            bytesRead = clientSock->read_some(buffer(enemyOutput, size));
            string_ptr inMessage(new string(enemyOutput, bytesRead));
            messageFromKlient = *inMessage;
            cout << messageFromKlient << endl;


            if(messageFromKlient == START){
               // cout << "serwer odbiera start" << endl;
                game->isKlientReady = true;
                messageFromKlient = DEFAULT;

            }else if(messageFromKlient == "END"){
                game->gameEnded = true;
                messageFromKlient = "default";
            }
            else{
                game->shootReceived(messageFromKlient);
                cout << "strezal oddany to" + messageFromKlient << endl;
            }
        }

        boost::this_thread::sleep(boost::posix_time::millisec(LONG_TIME));
    }
}




void Serwer::writeThread(socket_ptr clientSock)
{
    int size = 32;
    for (;;)
    {

        if(game->isKlientReady == true && game->isServerReady == true){

            game->doneButton->doubleClicked();
            messageFromKlient = DEFAULT;
        }

        messageToKlient = game->message;
        if(messageToKlient == START){
            clientSock->write_some(buffer(messageToKlient, size));
            messageToKlient = "default";
            game->message = "default";
        }else if(messageToKlient == "INDEKS"){
            messageToKlient = to_string(game->indexOfSquare);
            clientSock->write_some(buffer(messageToKlient, size));
            cout << "strezal oddany to" + messageToKlient << endl;
            game->message = "default";
            game->indexOfSquare = 1000;
        }else if(messageToKlient == "END"){
            clientSock->write_some(buffer(messageToKlient, size));
            messageToKlient = "default";
            game->message = "default";
        }

        boost::this_thread::sleep(boost::posix_time::millisec(LONG_TIME));
    }

}

string Serwer::getMessageFromKlient() const
{
    return messageFromKlient;
}

void Serwer::setMessageToKlient(const string &value)
{
    messageToKlient = value;
}
