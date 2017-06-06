#include "Serwer.h"
#include "klient.h"
#include "game.h"
#define PORT 5000
#define DEFAULT "default"
#define START "START"
#define SHORT_TIME 50
#define LONG_TIME 70
#define DEFAULT_INDEX "1000"


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
            if(messageFromKlient == "START"){
                game->isKlientReady = true;
                if(game->isKlientReady == true && game->isServerReady == true){
                    game->doneButton->doubleClicked();
                    messageFromKlient = "default";
                }
            }else{
                game->shootReceived(messageFromKlient);
                messageFromKlient = "default";
            }
        }

        boost::this_thread::sleep(boost::posix_time::millisec(LONG_TIME));
    }
}




void Serwer::writeThread(socket_ptr clientSock)
{
    int size = 32;
    for (;;){
         if(game->isServerReady == true){
         messageToKlient = "START";
         }else{
            messageToKlient = to_string(game->indexOfSquare);
         }

         if (messageToKlient != DEFAULT_INDEX){
                cout << "Strzał serwera" + messageToKlient << endl;
                clientSock->write_some(buffer(messageToKlient, size));
         }


        messageToKlient = DEFAULT;
        game->indexOfSquare = std::stoi(DEFAULT_INDEX);;

        boost::this_thread::sleep(boost::posix_time::millisec(LONG_TIME));
    }

}




