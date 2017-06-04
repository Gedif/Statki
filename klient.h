#ifndef KLIENT_H
#define KLIENT_H
#include<boost/thread.hpp>
#include<boost/bind.hpp>
#include<boost/asio.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

typedef boost::shared_ptr<tcp::socket> socket_ptr;


class Klient{
public:
    string ipadress;
    int port ;
    int startKlient();
    void readThread(socket_ptr sock);
    void writeThread(socket_ptr sock);
    string getIpadress() const;
    void setIpadress( string value);
    int getPort() const;
    void setPort(int value);

private:

    string messageFromServer = "1000";
    string messageToServer = "1000";
};


#endif // KLIENT_H
