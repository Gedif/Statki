
#ifndef SERWER_H
#define SERWER_H

#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<boost/asio/ip/tcp.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

typedef boost::shared_ptr<tcp::socket> socket_ptr;


class Serwer{
public:


    int startSerwer();
    void readThread(socket_ptr clientSock);
    void writeThread(socket_ptr clientSock);
    int getPort() const;
    void setPort(int value);



    string getMessageFromKlient() const;
    void setMessageFromKlient(const string &value);

    string getMessageToKlient() const;
    void setMessageToKlient(const string &value);

private:
    int port;
    string messageFromKlient;
    string messageToKlient;

};






#endif // SERWER_H
