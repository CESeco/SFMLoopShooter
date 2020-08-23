// a bullet is a projectile
#pragma once
#include "Entity.hpp"
#include <cmath>
class Projectile: public Entity{

public:
Projectile(sf::Vector2f pos,sf::Vector2f destination, const DefaultResources resourceId,bool collideResponse,float velocity , float damage, int sCount)
    :Entity(pos,resourceId,collideResponse),destination(destination),velocity(velocity),damage(damage),sCount(sCount)
    {
        //std::cout << "new projectile Created with " << pos.x << " " << pos.y << " with a destination of " << destination.x << " " << destination.y << std::endl;
        sprite.setTexture(gameResources::ResourceHolder::get().texture.get(resourceId));
        size.x = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().x;
        size.y = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().y;
        sprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
        sprite.setPosition(position);
        angle = calculateAngle();
    }
   

    void update(){
        position.x += velocity*cos(angle);
        position.y += velocity*sin(angle);
        sprite.setPosition(position);
    }


float calculateAngle(){
    float y{destination.y - position.y };
    float x{destination.x - position.x };
    float angleRadians{static_cast<float>(atan(y/x))};
    float angleDegrees{angleRadians};
    //what if our angle is negative. in case where mouse pointer is closer to origin than the player
    //to compensate for our negative angle
   if(destination.x < position.x){
       angleDegrees+=3.14159265f;
   }
    //std::cout << "the angle is " << angleDegrees << std::endl;
    return angleDegrees;
}



void setPosition(sf::Vector2f pos){
    position = pos;
}
int getCount(){
    return sCount;
}

sf::Vector2f getPosition(){
    return position;
}

sf::Vector2f getSize(){
    return size;
}
void setSize(sf::Vector2f si){
    size = si;
}

bool collides(sf::FloatRect rect){
    return sprite.getGlobalBounds().intersects(rect);
}

bool contains(sf::Vector2f pos){
    return sprite.getGlobalBounds().contains(pos);
};

sf::FloatRect getBounds(){
    if(sprite.getPosition() != sf::Vector2f(0,0)){
        return sprite.getGlobalBounds();
    }
    return sf::FloatRect(0,0,0,0);
}

bool toRemove(){
    return deleteProjectile;
}
void remove(){
    deleteProjectile = true;
}
sf::Vector2f getDestination(){
    return destination;
}
private:
         int sCount;
         bool deleteProjectile{false};
         float velocity;
         float damage;
         float angle;
         sf::Vector2f destination;

         virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(sprite);
        }
};
