#include <SFML/Network.hpp>
#include <iostream>
#include <queue>

class DataReceiver{
    public:
        DataReceiver(sf::IpAddress ip, unsigned short listenPort)
        :ip(ip), port(listenPort)
        {

        }
        static void receiveData(){
            
        }
        
        
    private:
        unsigned short port;
        sf::IpAddress ip;
        std::queue<

};