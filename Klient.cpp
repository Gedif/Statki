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


typedef boost::shared_ptr<string> string_ptr;


io_service service;
tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 6003);

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
	char userInput[32] = { 0 };
	string outMessage;

	for (;;)
	{
		cin.getline(userInput, size);
		outMessage = (string)userInput;

		if (!outMessage.empty())
		{
			sock->write_some(buffer(outMessage, size));
		}

		
		if (outMessage.find("exit") != string::npos)
			exit(1); 

		outMessage.clear();
		
	}

}

void Klient::readThread(socket_ptr sock)
{

	int size = 32;
	int bytesRead = 0;
	char enemyOutput[1024] = { 0 };
	//string inMessage ;

	for (;;)
	{
		if (sock->available())
		{
			bytesRead = sock->read_some(buffer(enemyOutput, size));
			string_ptr inMessage(new string(enemyOutput, bytesRead));
			
			cout <<  *inMessage  << endl;
		}

	
	}

}
