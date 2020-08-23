#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <GUI/Button.hpp>
#include <GUI/Text.hpp>
#include <GUI/TextBox.hpp>
#include "NetworkHandler.hpp"

class GameClient : public sf::Drawable{
    public:
        GameClient(const sf::RenderWindow& window)
        :ipLabel(sf::Vector2f(350,100),DefaultFont::comic),
         portLabel(sf::Vector2f(350,350),DefaultFont::comic),
         ipHolder(sf::Vector2f(350,150),sf::Vector2f(400,150),DefaultFont::comic,window,ipString),
         portHolder(sf::Vector2f(350,400),sf::Vector2f(400,150),DefaultFont::comic,window,portString),
         connectButton(sf::Vector2f(350,600),sf::Vector2f(200,100),DefaultFont::comic,window),
         window(window)
        {
            ipLabel.setText(std::string("Enter Ip address"),50,sf::Color::Red);
            portLabel.setText(std::string("Enter port address"),50,sf::Color::Red);

            connectButton.setText(sf::String{"Connect"},50,sf::Color::White);
            connectButton.setBackgroundColor(sf::Color::Red, sf::Color::Green);
            connectButton.addFunction([&]()->void{
                std::cout << "acknowledged" << std::endl;
                ip = sf::IpAddress(ipString);
                port = std::stoi(portString);
                listenCLI();
            });

            ipHolder.setColor(sf::Color::Red, sf::Color::White);
            portHolder.setColor(sf::Color::Red,sf::Color::White);
        }


        void listenCLI(){
            socket.connect(ip,port);
            socket.receive(packet);
            std::string data;
            packet >> data;
            if(data == "cts")
                std::cout << "connected to server" << std::endl;
            lport = socket.getLocalPort();

            NetworkHandler::get().setIp(getIp());
            NetworkHandler::get().setMode(Mode::Client);
            NetworkHandler::get().setPort(getPort());
            NetworkHandler::get().setLocalPort(getLocalPort());
            NetworkHandler::get().setConnected();
            socket.disconnect();
            std::cout << "stuff done here" << std::endl;
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

        void processEvent(sf::Event event){
            ipHolder.processEvent(event,window);
            portHolder.processEvent(event,window);
            connectButton.processEvent(event,window);
        }
        
    private:
        sf::TcpSocket socket;
        sf::Packet packet;
        std::size_t received;
        sf::IpAddress ip;
        unsigned short port;
        unsigned short lport;


        std::string ipString;
        std::string portString;



        //GUI elements if GUI call is made
        const sf::RenderWindow& window;
        sf::Event event;

        Button connectButton;
        TextBox ipHolder;
        TextBox portHolder;
        Text ipLabel;
        Text portLabel;

        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const{
            target.draw(ipLabel);
            target.draw(portLabel);
            target.draw(ipHolder);
            target.draw(portHolder);
            target.draw(connectButton);

        }
        
};