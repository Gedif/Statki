
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<cstdlib>

#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<boost/asio/ip/tcp.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

typedef boost::shared_ptr<tcp::socket> socket_ptr;
typedef boost::shared_ptr<string> string_ptr;
typedef map<socket_ptr, string_ptr> clientMap;
typedef boost::shared_ptr<clientMap> clientMap_ptr;
typedef boost::shared_ptr< list<socket_ptr> > clientList_ptr;
typedef boost::shared_ptr< queue<clientMap_ptr> > messageQueue_ptr;


io_service service;
tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), 6000));
clientList_ptr clientList(new list<socket_ptr>);


enum sleepLen // Time is in milliseconds
{
    sml = 100,
    lon = 200
};

void acceptorLoop();
void readThread(socket_ptr);
void writeThread(socket_ptr);


int main()
{

    cout << "Waiting for clients..." << endl;


        socket_ptr clientSock(new tcp::socket(service));

        acceptor.accept(*clientSock);

        cout << "New client joined! ";




    boost::thread_group threads;



    threads.create_thread(boost::bind(readThread,clientSock));
    //boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::sml));

    threads.create_thread(boost::bind(writeThread,clientSock));
    //boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::sml));

    threads.join_all();


    return 0;
}

void acceptorLoop()
{
    cout << "Waiting for clients..." << endl;

    for (;;)
    {
        socket_ptr clientSock(new tcp::socket(service));

        acceptor.accept(*clientSock);

        cout << "New client joined! ";

    }
}

void readThread(socket_ptr clientSock)
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

                    cout << *inMessage<< endl;
                }

        //boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::lon));
    }
}



void writeThread(socket_ptr clientSock)
{
    for (;;)
    {
        int size = 32;
        char userInput[32] = { 0 };
        string outMessage;


            cin.getline(userInput, size);
            outMessage = (string)userInput;

            if (!outMessage.empty())
            {
                clientSock->write_some(buffer(outMessage, size));
            }


            outMessage.clear();

        //boost::this_thread::sleep(boost::posix_time::millisec(sleepLen::lon));
    }
}

