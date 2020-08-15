#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Resources/ResourceHolder.hpp>

class Entity: public sf::Drawable{
    public:
        Entity(sf::Vector2f position, sf::Vector2f size,const int id,bool collideResponse)
        : collisionResponse(collideResponse),
         position(position),
         size(size)
        {
            
        }

    
        virtual void setPosition(sf::Vector2f position)=0;
        virtual sf::Vector2f getPosition()=0;
        virtual void setSize(sf::Vector2f size)=0;
        virtual sf::Vector2f getSize()=0;
        virtual bool collides(sf::FloatRect rect)=0;
        virtual bool contains(sf::Vector2f pos)=0;


    protected:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Texture texture;
        sf::Sprite sprite;
        bool collisionResponse;


};