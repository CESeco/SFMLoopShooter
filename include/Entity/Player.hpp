#pragma once
#include "Entity.hpp"
#include <Event/Action.hpp>
#include <Event/ActionMap.hpp>
#include <Event/ActionTarget.hpp>

//remember to call setDefaultMovements before instantiating this class


class Player : public Entity{
    //constructor
public:
    Player(sf::Vector2f pos,const int resourceId,bool collideResponse)
    :Entity(pos,resourceId,collideResponse),
     eventTarget(keymap)
    {
        sprite.setTexture(gameResources::ResourceHolder::get().texture.get(resourceId));
        size.x = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().x;
        size.y = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().y;
        sprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
        eventTarget.bind(allowedMovement::left,[&](const sf::Event&){position.x -= .1f;direction=allowedMovement::left;});
        eventTarget.bind(allowedMovement::right,[&](const sf::Event&){position.x += .1f;direction=allowedMovement::right;});
        eventTarget.bind(allowedMovement::top,[&](const sf::Event&){position.y -= .1f;direction=allowedMovement::top;});
        eventTarget.bind(allowedMovement::down,[&](const sf::Event&){position.y += .1f;direction=allowedMovement::down;});
        sprite.setPosition(position);

        
    }
    enum allowedMovement{
            left,right,top,down
        };

    void reverseDirection();

    static void setDefaultMovements();
    void processEvent();
    void update();

    void setPosition(sf::Vector2f position) override ;
    sf::Vector2f getPosition() override;

    void setSize(sf::Vector2f size) override;
    sf::Vector2f getSize() override;

    bool collides(sf::FloatRect rect) override ;
    bool contains(sf::Vector2f pos) override;

    void setHealth(float healthVal);
    float getHealth();

    float getVelocity();
    
    allowedMovement direction;

    sf::FloatRect getBounds(){
        return sprite.getGlobalBounds();
    }
    
    protected:
        float health{100};
        float velocity{.1f};

        static ActionMap<int> keymap;
        ActionTarget<int> eventTarget;
         
   
    private:
       
         void draw(sf::RenderTarget& target, sf::RenderStates) const
        {
            target.draw(sprite);
    
        }

        



    


};