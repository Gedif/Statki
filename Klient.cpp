#include<iostream>
#include<queue>
#include<string>
#include<cstdlib>

#include<boost/thread.hpp>
#include<boost/bind.hpp>
#include<boost/asio.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/algorithm/string.hpp>
#include "Klient.h"
#include "Game.h"

typedef boost::shared_ptr<string> string_ptr;


extern Game* game;
io_service service;
tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 4521);

enum sleepLen // Time is in milliseconds
{
    sml = 50,
    lon = 50,
};

int Klient::startKlient()
{

    try
    {

        boost::thread_group threads;

        socket_ptr socket(new tcp::socket(service));
        socket->connect(endpoint);



        threads.create_thread(boost::bind(&Klient::readThread,this, socket));
        threads.create_thread(boost::bind(&Klient::writeThread,this, socket));
        cout << "Connection established" << endl;

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

	for (;;)
	{

        messageToServer = to_string(game->indexOfSquare);

        if (messageToServer != "1000" )
		{
            cout << "Strzał Klienta" + messageToServer << endl;
            sock->write_some(buffer(messageToServer, size));
		}

        messageToServer = "default";
        game->indexOfSquare = 1000;
        boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::lon));
	}

}

string Klient::getIpadress() const
{
    return ipadress;
}

void Klient::setIpadress( string value)
{
    ipadress = value;
}

int Klient::getPort() const
{
    return port;
}

void Klient::setPort(int value)
{
    port = value;
}

void Klient::readThread(socket_ptr sock)
{

    int size = 32;
    int bytesRead = 0;
    char enemyOutput[1024] = { 0 };

	for (;;)
	{
        if (sock->available())
        {
			bytesRead = sock->read_some(buffer(enemyOutput, size));
            string_ptr inMessage(new string(enemyOutput, bytesRead));
			
            messageFromServer = *inMessage;

            if(messageFromServer != "default"){
                cout << "Strzał otrzymany od serwera" + messageFromServer << endl;
                game->shootReceived(messageFromServer);
                messageFromServer = "default";
            }

		}

    boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::lon));
	}

}
