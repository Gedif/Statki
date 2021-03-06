
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<cstdlib>

#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<boost/asio/ip/tcp.hpp>
#include "Serwer.h"
#include "Klient.h"
#include "Game.h"

typedef boost::shared_ptr<string> string_ptr;
typedef map<socket_ptr, string_ptr> clientMap;
typedef boost::shared_ptr<clientMap> clientMap_ptr;
typedef boost::shared_ptr< list<socket_ptr> > clientList_ptr;


clientList_ptr clientList(new list<socket_ptr>);

enum sleepLen // Time is in milliseconds
{
    sml = 50,
    lon = 50
};

extern Game* game;
io_service service2;
tcp::acceptor acceptor(service2, tcp::endpoint(tcp::v4(),4521));

int Serwer:: startSerwer()
{

    cout << "Waiting for clients..." << endl;

        socket_ptr clientSock(new tcp::socket(service2));
        cout << "1" << endl;
        acceptor.accept(*clientSock);
        cout << "New client joined! " << endl;
        cout << "2" << endl;





    boost::thread_group threads;
    cout << "5" << endl;


   threads.create_thread(boost::bind(&Serwer::readThread,this,boost::ref(clientSock)));
    boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::sml));
    cout << "4" << endl;
   threads.create_thread(boost::bind(&Serwer::writeThread,this,boost::ref(clientSock)));
    boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::sml));
    cout << "3" << endl;
    //threads.join_all();


    return 0;
}



void Serwer::readThread(socket_ptr clientSock)
{
    int size = 32;
    int bytesRead = 0;
    char enemyOutput[1024] = { 0 };
    string inMessage;

    for (;;)
    {
                if (clientSock->available())
                {
                    bytesRead = clientSock->read_some(buffer(enemyOutput, size));

                    string_ptr inMessage(new string(enemyOutput, bytesRead));
                    cout << "Debuging1" << endl;
                    messageFromKlient = *inMessage;
                    if(messageFromKlient == "START"){
                        cout << "Debuging2" << endl;
                        game->isKlientReady = true;
                        cout << "Debuging3" << endl;
                        if(game->isKlientReady == true && game->isServerReady == true){
                            cout << "Debuging4" << endl;
                            game->doneButton->doubleClicked();
                            messageFromKlient = "default";
                        }

                    }else{
                        game->shootReceived(messageFromKlient);
                        messageFromKlient = "default";
                    }
                }

       boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::lon));
    }
}




void Serwer::writeThread(socket_ptr clientSock)
{
    for (;;)
    {
        int size = 32;

            if(game->isServerReady == true){
                 messageToKlient = "START";
             }else{
                 messageToKlient = to_string(game->indexOfSquare);
             }
            if (messageToKlient != "1000")
            {
                cout << "Strzał serwera" + messageToKlient << endl;
                clientSock->write_some(buffer(messageToKlient, size));
            }


        messageToKlient = "default";
        game->indexOfSquare = 1000;

        boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::lon));
    }

}


int Serwer::getPort() const
{
    return port;
}

void Serwer::setPort(int value)
{
    port = value;
}

string Serwer::getMessageFromKlient() const
{
    return messageFromKlient;
}

void Serwer::setMessageFromKlient(const string &value)
{
    messageFromKlient = value;
}

string Serwer::getMessageToKlient() const
{
    return messageToKlient;
}

void Serwer::setMessageToKlient(const string &value)
{
    messageToKlient = value;
}



