#include "Entity.hpp"
#include <Event/Action.hpp>
#include <Event/ActionMap.hpp>
#include <Event/ActionTarget.hpp>

//remember to call setDefaultMovements before instantiating this class


class Player : public Entity{
    //constructor
public:
    Player(sf::Vector2f pos, sf::Vector2f size,const int resourceId,bool collideResponse)
    :Entity(pos,size,resourceId,collideResponse),
     eventTarget(keymap)
    {
        sprite.setTexture(gameResources::ResourceHolder::get().texture.get(resourceId));
        sprite.setTextureRect(sf::IntRect(0,0,gameResources::ResourceHolder::get().texture.get(resourceId).getSize().x,gameResources::ResourceHolder::get().texture.get(resourceId).getSize().y));
       
        eventTarget.bind(allowedMovement::left,[&](const sf::Event&){position.x -= .1f;});
        eventTarget.bind(allowedMovement::right,[&](const sf::Event&){position.x += .1f;});
        eventTarget.bind(allowedMovement::top,[&](const sf::Event&){position.y -= .1f;});
        eventTarget.bind(allowedMovement::down,[&](const sf::Event&){position.y += .1f;});
    }
    
    static void setDefaultMovements();
    void processEvent();
    void update();


    void setPosition(sf::Vector2f position) ;
    sf::Vector2f getPosition() ;
    void setSize(sf::Vector2f size) ;
    sf::Vector2f getSize() ;

    bool collides(sf::FloatRect rect) ;
    bool contains(sf::Vector2f pos) ;

    void setHealth(float healthVal);
    float getHealth();

    float getVelocity();
    
    protected:
        float health{100};
        float velocity{.2f};
        enum allowedMovement{
            left,right,top,down
        };
        static ActionMap<int> keymap;
        ActionTarget<int> eventTarget;
        
   
    private:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Texture texture;
        sf::Sprite sprite;
         void draw(sf::RenderTarget& target, sf::RenderStates) const
        {
            target.draw(sprite);
    
        }

        



    


};