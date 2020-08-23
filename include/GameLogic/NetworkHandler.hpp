#include "Configuration.hpp"
#include <SFML/Network.hpp>
#pragma once

class NetworkHandler{
    public:
        NetworkHandler() = default;
        
        NetworkHandler(sf::IpAddress ip, unsigned short port, Mode mode):
         ip(ip),port(port),mode(mode){
        }
        
        static NetworkHandler& get(){
            static NetworkHandler handler;
            return handler;
        }

        Mode getMode(){
            return mode;
        }
        void setIp(sf::IpAddress ipa){
            ip = ipa;
        }
        void setPort(unsigned short port){
            this->port = port;
        }
        void setMode(Mode mode){
            this->mode = mode;
        }
        
        void setLocalPort(unsigned short port){
            localPort = port;
        }

        sf::IpAddress getIp() const {
            return ip;
        }
        unsigned short getPort() const {
            return port;
        }

        unsigned short getLocalPort() const{
            return localPort;
        }
        void setConnected(){
            connected = true;
        }
        bool isConnected(){
            return connected;
        }
        //sf::UdpSocket socket;
    private:
       bool connected{false};
       Mode mode; 
       unsigned short port;
       unsigned short localPort;
       sf::IpAddress ip;
       
       

       
};