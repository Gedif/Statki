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
    int startKlient();
    void readThread(socket_ptr sock);
    void writeThread(socket_ptr sock);
};


#endif // KLIENT_H
