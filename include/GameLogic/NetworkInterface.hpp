#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "Configuration.hpp"
#include "GameHost.hpp"
#include "GameClient.hpp"
#include "NetworkHandler.hpp"
class NetworkInterface{
    public:
    
        NetworkInterface() = default;
        NetworkInterface(Mode kind):kind(kind){}
        
        char askForModeCLI(){
            char gameMode;
            std::cout << "Enter game mode : (h) for host and (s) for searching a game" << std::endl;
            std::cin >> gameMode;
            
            return gameMode;
        }

        void call(){
            char mode = askForModeCLI();
            switch(mode){
                case 'h':
                {
                    GameHost host;
                    //std::cout << host.getIp() << std::endl;
                    NetworkHandler::get().setIp(host.getIp());
                    NetworkHandler::get().setMode(Mode::Host);
                    NetworkHandler::get().setPort(host.getPort());
                    NetworkHandler::get().setLocalPort(host.getLocalPort());
                    std::cout << "remote ip " << host.getIp().toString() << " " << "remote port " << host.getPort() << " local port " << host.getLocalPort() << std::endl; 
                    break;
                }
                case 's':
                {
                    GameClient client; 
                    //std::cout << client.getIp() << std::endl;
                    NetworkHandler::get().setIp(client.getIp());
                    NetworkHandler::get().setMode(Mode::Client);
                    NetworkHandler::get().setPort(client.getPort());
                    NetworkHandler::get().setLocalPort(client.getLocalPort());
                    std::cout << "remote ip " << client.getIp().toString() << " " << "remote port " << client.getPort() << " local port " << client.getLocalPort() << std::endl; 
                    break;
                }
            }
        }

    private: 
        Mode kind;
        



};
