#pragma once
#include "Entity.hpp"
#include <Event/Action.hpp>
#include <Event/ActionMap.hpp>
#include <Event/ActionTarget.hpp>
#include <Views/Configuration.hpp>
#include "Projectile.hpp"
#include <SFML/Network.hpp>
#include <GameLogic/NetworkHandler.hpp>
#include <Resources/configuration.hpp>

//remember to call setDefaultMovements before instantiating this class

class Player : public Entity
{
public:
    //Note that collide Response has no effect whatsoever to gamePlay . Refactor required
    
    Player(sf::Vector2f pos, const DefaultResources resourceId, bool collideResponse, sf::RenderWindow& window,int sCount,int portCount,bool primary)
        : Entity(pos, resourceId, collideResponse),window(window),eventTarget(keymap),sCount(sCount),portCount(portCount),dataReceiver(&Player::listenNetworkEvents,this)
    
    {
        
        sprite.setTexture(gameResources::ResourceHolder::get().texture.get(resourceId));
       
       //get the default size of image we just loaded
        size.x = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().x;
        size.y = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().y;
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
        sprite.setPosition(position);
       
        
        /* There are two players one is primary and another is secondary.
        one which player is controlling is primary 
        and player controlled by another user over 
        another pc is secondary
        secondary player should receive data from over the internet */
        if(!primary)
            dataReceiver.launch();
        
        
        
    }
        
     /* sbind is related to server binding.
     upon activation the player instance will be able to send packets  */
     void sbind(bool keepOnAsk);
     
    /* networkEvent is called when we receive something from our peer player
    over the network */
    void networkEvent(std::string type,double a, double b);


    
    enum allowedMovement
    {
        left,
        right,
        top,
        down,
        fire
    };

    /* Bind function will bind the id of allowedMovement 
    and a lambda function that is triggered when 
    the event relating to id of allowed movement is fired. */
    void bind();
    
    //when collision takes place, revert the direction of player
    //to its original position
    void reverseDirection(sf::Event event);

    //map unique id and events together
    static void setDefaultMovements();


    void processEvent();

    void update();
    
    void setPosition(sf::Vector2f position) override;
    
    sf::Vector2f getPosition() override;

    void setSize(sf::Vector2f size) override;
   
    sf::Vector2f getSize() override;

    bool collides(sf::FloatRect rect) override;
   
    bool contains(sf::Vector2f pos) override;

    float getVelocity();

    allowedMovement direction;

    sf::FloatRect getBounds()
    {
        return sprite.getGlobalBounds();
    }
    int getCount(){
        return sCount;
    }
    void stopRendering(){
        allowRendering = false;
    }
    void startRendering(){
        allowRendering = true;
    }

    bool isRendering(){
        return allowRendering;
    }
    void listenNetworkEvents();
    
    void setEventPlayMode(){

        eventTarget.setPlayMode();
        
    }
    void setUserControlMode(){
        eventTarget.setRecordMode();
    }
    std::vector<std::shared_ptr<Projectile>> projectile;
    std::vector<std::shared_ptr<Projectile>> preservedProjectile;
    int count{0};
    bool noEvent{false};
    int  noEventCount{0};
protected:
    float health{100};
    float velocity{.1f};
    int sCount;
    static ActionMap<int> keymap;
    ActionTarget<int> eventTarget;
    sf::TcpListener sListener;
    

private:

    sf::TcpSocket sSocket;
    int portCount;
    bool allowRendering{true};
    int rateCount{0};
    sf::Clock rateFireCountClock;
    sf::RenderWindow& window;
    sf::Thread dataReceiver;

    

    bool stopProcessing{false};

    void draw(sf::RenderTarget &target, sf::RenderStates) const
    {
       if(allowRendering){
        for (auto &proj : projectile)
        {
            target.draw(*proj);
        }
        target.draw(sprite);
        }
    }
};