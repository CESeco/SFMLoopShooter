//what should it do?

//when check for projectile collision with players
#pragma once
#include <Views/Configuration.hpp>
#include <vector>
#include <memory>
#include <Entity/Player.hpp>
#include <utility>
#include "Configuration.hpp"
#include "NetworkHandler.hpp"
#include <SFML/Network.hpp>


//if focus instance dies, either add new instance or if all instance are already added
// stop the game


class GameLogic : public sf::Drawable{
    public: 
    
        GameLogic(sf::RenderWindow& window):window(window){
            Player::setDefaultMovements();
            addPlayerInstance();
            
        }
        Player& getPrimaryPlayer(){
            std::shared_ptr<Player> player;
            switch(checkConnectionMode()){
                    case Mode::Client:
                        player = playerInstance.back().second;
                        break;
                    case Mode::Host:
                        player = playerInstance.back().first;
                        break;
                }
                return *player;
        }
        Player& getSecondaryPlayer(){
            std::shared_ptr<Player> player;
            switch(checkConnectionMode()){
                    case Mode::Client:
                        player = playerInstance.back().first;
                        break;
                    case Mode::Host:
                        player = playerInstance.back().second;
                        break;
                }
                return *player;
        }
    

        void addPlayerInstance(){
            if(availableInstance < maxInstance){
                availableInstance++;
                int bufCount{0};
                if(!playerInstance.empty()){
                    for(auto& a:playerInstance){
                        
                        a.first->setPosition(sf::Vector2f(screen_size_x/2,screen_size_y/2+bufCount*200));
                        a.second->setPosition(sf::Vector2f(max_coords_x - screen_size_x/2,screen_size_y/2+bufCount*200));
                        a.first->startRendering();
                        a.second->startRendering();

                        switch(checkConnectionMode()){
                            case Mode::Client:
                                a.second->setEventPlayMode();
                            case Mode::Host:
                                a.first->setEventPlayMode();
                        }
                        bufCount++;
                    }
                }
                portCount++;
                bool primary{false};
                switch(checkConnectionMode()){
                    case Mode::Client:
                        primary = false;
                        break;
                    case Mode::Host:
                        primary = true;
                        break;
                }

                playerInstance.emplace_back(std::make_pair(new Player(sf::Vector2f(screen_size_x/2,screen_size_y/2+instanceOffset),1,true,window,++count,portCount,primary),
                                                           new Player(sf::Vector2f(max_coords_x - screen_size_x/2,screen_size_y/2+instanceOffset),1,true,window,++count,portCount,!primary)));
                
                switch(checkConnectionMode()){
                    case Mode::Host:
                      {
                        //playerInstance.back().second->cbind();
                        playerInstance.back().first->sbind();
                        //std::cout << "ok" << std::endl;
                        break;
                      }
                    case Mode::Client:
                        //playerInstance.back().first->cbind();
                        playerInstance.back().second->sbind();
                        break;
                        
                }
                
                
                instanceOffset+=200;
                getPrimaryPlayer().bind();
                
            }
        }

        sf::Vector2f getPrimaryPlayerPosition(){
           return getPrimaryPlayer().getPosition();
        }
        
       Mode checkConnectionMode(){
           return NetworkHandler::get().getMode();
       } 
        
        void stopInstanceRendering(Player& player){
            player.stopRendering();
        }
        
        void startInstanceRendering(Player& player){
            player.startRendering();
        }

        void checkForGameOver(){
            if(!getPrimaryPlayer().isRendering() or !getSecondaryPlayer().isRendering()){
                addPlayerInstance();
            }
            
            
        }
        void checkKill(){
            std::vector<std::shared_ptr<Projectile>> listOfProjectile;
            for(auto& instance:playerInstance){
                listOfProjectile.insert(listOfProjectile.end(),instance.first->projectile.begin(),instance.first->projectile.end());
                listOfProjectile.insert(listOfProjectile.end(),instance.second->projectile.begin(),instance.second->projectile.end());
            }
            for(auto& instance:playerInstance){
                for(auto& proj:listOfProjectile){
                    if(instance.first->collides(proj->getBounds()) and instance.first->getCount() != proj->getCount()){
                        instance.first->stopRendering();
                        proj->remove();
                        //proj->setPosition(sf::Vector2f(-100,-100));
                        update();
                    }
                    if(instance.second->collides(proj->getBounds()) and instance.second->getCount() != proj->getCount()){
                        instance.second->stopRendering();
                        proj->remove();
                        update();
                        //std::cout << "getting killed for no reason " << std::endl;
                    }
                }

            }
            
            
        }
        
    /*     void sendData(){
            packet << stringifiedPosition;
            
        }
        void parsePositionData(std::string& receivedData){
            int instanceAmount = playerInstance.size();
            int pos;
            int ipos{0}; //initial position
            std::string chunk{};
            while((pos = receivedData.find_first_of(" ")) != std::string::npos){
                chunk = receivedData.substr(ipos,pos);
                ipos = pos+1;
            } 
            
        }
         */

        
        void update(){
            for(auto& players:playerInstance){
                switch(checkConnectionMode()){
                    case Mode::Client:
                        
                        stringifiedPosition += std::to_string(players.second->getPosition().x) + std::string(",") + std::to_string(players.second->getPosition().y)+ std::string(" ");
                        break;
                    case Mode::Host:
                        stringifiedPosition += std::to_string(players.first->getPosition().x) + std::string(",") + std::to_string(players.first->getPosition().y)+ std::string(" "); 
                        break;
                }
                players.first->update();
                players.second->update();
            }
        }

        std::vector<std::pair<std::shared_ptr<Player>,std::shared_ptr<Player>>> playerInstance;
        
        

    private:
        int portCount;
        sf::TcpListener rSock; //receive socket
        sf::TcpSocket sSock; //send socket

        sf::IpAddress ip;
        unsigned short port;

        sf::Packet packet;
        sf::RenderWindow& window;
        int instanceOffset{0};
        bool gameOver{false};
        bool nextInstance{false};
        std::string stringifiedPosition;
        unsigned int maxInstance{3};
        unsigned int availableInstance{};

        int count{0};

        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
           for(auto& playerPair: playerInstance){
               target.draw(*playerPair.first);
               target.draw(*playerPair.second);
           }
        }


       
};