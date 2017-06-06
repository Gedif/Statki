#ifndef SERWER_H
#define SERWER_H
#define DEFAULT "default"

#include<iostream>
#include<cstdlib>
#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<boost/asio/ip/tcp.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

typedef boost::shared_ptr<tcp::socket> socket_ptr;
typedef boost::shared_ptr<string> string_ptr;

/**
 * @brief Klasa Serwer.
 *
 * Klasa odpowiada za utworzenie połączenie po stronie serwera na podstawie portu ustawione domyślnie na 5000.
 */
class Serwer{
public:
    /**
     * @brief Metoda uruchamiająca klienta
     *
     * Tworzone w niej są dwa nowe wątki,jeden służący do czytania wiadomości od klienta, drugi służący do wysyłania wiadomości do klienta.
     *
     */
    int startSerwer();
    /**
     * @brief Metoda tworząca pętlę czytającą wiadomosći od klienta.
     * @param sock Argument ten to socket służacy do utworzenia połączenia.
     */
    void readThread(socket_ptr clientSock);
    /**
     * @brief Metoda tworząca pętlę wysyłającą wiadomosći do klienta.
     * @param sock Argument ten to socket służacy do utworzenia połączenia.
     */
    void writeThread(socket_ptr clientSock);


private:
    /**
     * @brief Wiadomość od klienta.
     */
    string messageFromKlient = DEFAULT;
    /**
     * @brief Wiadomość do klienta.
     */
    string messageToKlient = DEFAULT;

};

#endif // SERWER_H
