#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Resources/ResourceHolder.hpp>
#include <Resources/configuration.hpp>


class Entity: public sf::Drawable{
    public:
        //position for entity current position, id represents Resource Id(Resource id points out which texture to use for particular sprite)
        Entity(sf::Vector2f position,const DefaultResources id,bool collideResponse)
        : collisionResponse(collideResponse),
         position(position),
         resourceId(id)
        {
            
        }
       
        
        virtual void setPosition(sf::Vector2f position)=0;
        virtual sf::Vector2f getPosition()=0;
        virtual void setSize(sf::Vector2f size)=0;
        virtual sf::Vector2f getSize()=0;
        virtual bool collides(sf::FloatRect rect)=0;
        virtual bool contains(sf::Vector2f pos)=0;
        virtual void update()=0; 
   
    protected:
        DefaultResources resourceId;
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Texture texture;
        sf::Sprite sprite;
        bool collisionResponse;


};