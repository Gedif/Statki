#ifndef KLIENT_H
#define KLIENT_H
#define DEFAULT "default"

#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

typedef boost::shared_ptr<string> string_ptr;
typedef boost::shared_ptr<tcp::socket> socket_ptr;




/**
 * @brief Klasa Klient.
 *
 * Klasa ta odpowiada za utworzenie połączenia po stronie gracza łączącego się z serwerem na podstawie adresu ip oraz portu.
 * W naszej wersji połączenie pomiędzy serwerem a klientem następuje na jednej maszynie, więć adres to "127.0.0.1" a port został przez nas ustalony na 5000.
 *
 */

class Klient{
public:
    /**
     * @brief Metoda uruchamiająca klienta
     *
     * Tworzone w niej są dwa nowe wątki,jeden służący do czytania wiadomości od serwera, drugi służący do wysyłania wiadomości na serwer.
     *
     */
    int startKlient();
    /**
     * @brief Metoda tworząca pętlę czytającą wiadomosći od serwera.
     * @param sock Argument ten to socket służacy do utworzenia połączenia.
     */
    void readThread(socket_ptr sock);
    /**
     * @brief Metoda tworząca petlę wysyłającą wiadomości do serwera.
     * @param sock Argument ten to socket służacy do utworzenia połączenia.
     */
    void writeThread(socket_ptr sock);

private:
    /**
     * @brief Wiadomość od serwera
     */
    string messageFromServer = DEFAULT;
    /**
     * @brief Wiadomości przesyłane do serwera.
     */
    string messageToServer = DEFAULT;
};


#endif // KLIENT_H
