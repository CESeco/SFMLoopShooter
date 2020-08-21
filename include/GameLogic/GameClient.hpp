#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

class GameClient{
    public:
        GameClient(sf::IpAddress ip, unsigned short port):ip(ip),port(port){
            listenCLI();
        }

        GameClient(){
            
            std::cout << "You are a client " << std::endl;
            std::cout << "enter host ip address " << std::endl;
            std::string ipAddr;
            std::cin >> ipAddr;
            ip = sf::IpAddress(ipAddr);
            std::cout << "enter host port " << std::endl;
            std::cin >> port;
            
            listenCLI();
        }
        void listenCLI(){
            socket.connect(ip,port);
            socket.receive(packet);
            std::string data;
            packet >> data;
            if(data == "cts")
                std::cout << "connected to server" << std::endl;
            lport = socket.getLocalPort();
            }

        sf::IpAddress getIp(){
            return ip;
        }
        unsigned short getPort(){
            return port;

        }
        unsigned short getLocalPort(){
            return lport;
        }

        
    private:
        sf::TcpSocket socket;
        sf::Packet packet;

        std::size_t received;
        sf::IpAddress ip;
        unsigned short port;

        
        unsigned short lport;

        
};