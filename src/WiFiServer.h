#ifndef WIFISERVER_H_INCLUDED
#define WIFISERVER_H_INCLUDED
#include <Arduino.h>
#include "Server.h"
#include "WiFiClient.h"
#define TCP_NODELAY    0x01    /* don't delay send to coalesce packets */

class WiFiServer: public Server
    {
private:
    int sockfd;
    int _accepted_sockfd = -1;
    uint16_t _port;
    uint8_t _max_clients;
    bool _listening;
    bool _noDelay = false;
public:
 void listenOnLocalhost(){}

    WiFiServer(uint16_t port=80, uint8_t max_clients=4):sockfd(-1),_accepted_sockfd(-1),_port(port),_max_clients(max_clients),_listening(false),_noDelay(false){}
    ~WiFiServer(){ end();}
    WiFiClient available();
    WiFiClient accept(){return available();}
    void begin(uint16_t port=0);
    void setNoDelay(bool nodelay);
    bool getNoDelay();
    bool hasClient();
    size_t write(const uint8_t *data, size_t len);
    size_t write(uint8_t data){
      return write(&data, 1);
    }
    using Print::write;

    void end();
    void close();
    void stop();
    operator bool(){return _listening;}
    int setTimeout(uint32_t seconds);
    void stopAll();


};

#endif // WIFISERVER_H_INCLUDED
