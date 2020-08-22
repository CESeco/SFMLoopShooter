#pragma once
#include "TileMapView.hpp"
#include <GameLogic/GameLogic.hpp>


class TileContainerView: public sf::Drawable {
    public:
        TileContainerView(const std::string& str,sf::RenderWindow& window):
        view(str),
        gamePlayers(window)
        
        {
            view.processTiles();
           
            cameraView.reset(sf::FloatRect(0.f,0.f,screen_size_x,screen_size_y));
            
            
            center = cameraView.getCenter();
            drawGrids();
            drawConstraintBackground();

            /*  */
            
        }
        void changeCenter(float newPosA,float newPosB){
            cameraView.setCenter(newPosA,newPosB);
            center.x = newPosA;
            center.y = newPosB;
        }
        void processEvents(sf::Event& event){
        /* bool gainedFocus{false};
        if(event.type == sf::Event::GainedFocus){
            gainedFocus = true;
        } */
        
           
            fixCollision(gamePlayers.getPrimaryPlayer());

            fixCollision(gamePlayers.getSecondaryPlayer());
            //fixCollision(*player.second);
            sf::Vector2f prevPos{gamePlayers.getPrimaryPlayerPosition()};
            Player& player = gamePlayers.getPrimaryPlayer();
            Player& secPlayer = gamePlayers.getSecondaryPlayer();
            if(toMove(prevPos)){
                gamePlayers.getPrimaryPlayer().processEvent();
                changeCenter(gamePlayers.getPrimaryPlayer().getPosition().x, gamePlayers.getPrimaryPlayer().getPosition().y);
            
            }else{
                if(player.getPosition().x < screen_size_x/2){
                    player.setPosition(sf::Vector2f(screen_size_x/2,player.getPosition().y));
                }else if(player.getPosition().y < screen_size_y/2){
                    player.setPosition(sf::Vector2f(player.getPosition().x,screen_size_y/2));
                }else if(player.getPosition().x > (max_coords_x-screen_size_x/2)){
                    player.setPosition(sf::Vector2f((max_coords_x-screen_size_x/2),player.getPosition().y));
                }else if(player.getPosition().y > (max_coords_y-screen_size_y/2)){
                    player.setPosition(sf::Vector2f(player.getPosition().x,(max_coords_y-screen_size_y/2)));
                }
                
                 if(secPlayer.getPosition().x < screen_size_x/2){
                    secPlayer.setPosition(sf::Vector2f(screen_size_x/2,secPlayer.getPosition().y));
                }else if(secPlayer.getPosition().y < screen_size_y/2){
                    secPlayer.setPosition(sf::Vector2f(secPlayer.getPosition().x,screen_size_y/2));
                }else if(secPlayer.getPosition().x > (max_coords_x-screen_size_x/2)){
                    secPlayer.setPosition(sf::Vector2f((max_coords_x-screen_size_x/2),secPlayer.getPosition().y));
                }else if(secPlayer.getPosition().y > (max_coords_y-screen_size_y/2)){
                    secPlayer.setPosition(sf::Vector2f(secPlayer.getPosition().x,(max_coords_y-screen_size_y/2)));
                }
                
            
            }
            if(gamePlayers.playerInstance.size() > 1){
                //std::cout << "ok " << std::endl;
                for(auto i{gamePlayers.playerInstance.begin()};i<gamePlayers.playerInstance.end()-1;i++){
                    if(gamePlayers.checkConnectionMode() == Mode::Client){
                        (*i).second->processEvent();
                        //(*i).first->listenNetworkEvents();
                    }else{
                        (*i).first->processEvent();
                        //(*i).second->listenNetworkEvents();
                    }
                }
            }
            //secPlayer.listenNetworkEvents();
            

           
        
        }
        void drawGrids();
        void drawConstraintRectangle(sf::Vector2f pos, sf::Vector2f size,sf::Color color);
        void drawConstraintBackground();

        void checkProjectileCollision(Player& player,std::shared_ptr<Entity> entity);
         
    

        //for movement reasons build a large rectangle around the the regions where we don't want player to go and if player collides with those rectangles player can't move
        void buildConstrainingRectangles(){
            sf::RectangleShape rect(sf::Vector2f(0,0));
        }

        bool fixCollision(Player& player){
            gamePlayers.checkKill();
            gamePlayers.checkForGameOver();
            for(auto& entity: view.entityList){
                checkProjectileCollision(player,entity);
                if(entity->collides(player.getBounds())){
                    player.reverseDirection();
                    return true;
                }
            }
        return true;
        }

        bool toMove(sf::Vector2f position){
          float windowHW = screen_size_x/2;  //window half width
          float windowHH = screen_size_y/2; //window half height

          if(position.x >= windowHW and position.y >= windowHH  and position.x <= (max_coords_x-screen_size_x/2) and position.y <= (max_coords_y-screen_size_y/2)){
            return true;
          }
        return false;          
        }


        void update(){
            //std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;
            //std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;
            gamePlayers.update();
        
        }
      

    private:
        std::vector<sf::RectangleShape> constraintsRectangle;
        
        TileMapView view;
        sf::Vector2f center;
        GameLogic gamePlayers;
        sf::View cameraView;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
            target.clear(sf::Color(128,175,73));
            target.setView(cameraView);
            for(auto& rect: constraintsRectangle){
                target.draw(rect);
            }
            target.draw(view);
            target.draw(gamePlayers);
            
        }
};