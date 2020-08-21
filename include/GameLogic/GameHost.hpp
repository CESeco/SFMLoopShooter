#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>


class GameHost{


    public:
        GameHost(){
            listener.listen(sf::Socket::AnyPort);
        
            //socket.bind(sf::Socket::AnyPort);
            //socket.setBlocking(false);
            std::cout << "You are a host " << std::endl;
            std::cout << "your local ip address is " << sf::IpAddress::getLocalAddress().toString() << std::endl;
            std::cout << " The port allocated is " << listener.getLocalPort() << std::endl;
            port = listener.getLocalPort();
            listenCLI();
            listener.close();
            
        }
        GameHost(sf::IpAddress ip, unsigned short port):ip(ip),port(port){
            listenCLI();
        }

        
        void listenCLI(){
            std::string str{"cts"};
            packet << str;
            bool running{true};
            while(running){
                
                if(listener.accept(client) == sf::Socket::Done){
                    std::cout << " New client connected " << std::endl;
                     cip = client.getRemoteAddress();
                     cport = client.getRemotePort();
                     std::cout << cip << " " << cport << std::endl;
                     client.send(packet);
                     running = false;
                }

            }
            
        }
       

        sf::IpAddress getIp(){
            return cip;
        }
        unsigned short getPort(){
            return cport;

        }
        unsigned short getLocalPort(){
            return port;
        }
    private:
        sf::TcpListener listener;
        sf::TcpSocket client;
        sf::Packet packet;
        std::size_t received;
        sf::IpAddress ip;
        sf::IpAddress cip;
        unsigned short cport;
        unsigned short port;

};