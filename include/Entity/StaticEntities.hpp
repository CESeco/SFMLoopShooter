#pragma once
#include "Entity.hpp"


// Static Entities don't move

class StaticEntities : public Entity{
    public:
    StaticEntities(sf::Vector2f pos,const DefaultResources resourceId,bool collideResponse)
    :Entity(pos,resourceId,collideResponse)
    {
        //std::cout << "new Sprite Created with " << pos.x << " " << pos.y << std::endl;
        sprite.setTexture(gameResources::ResourceHolder::get().texture.get(resourceId));
        size.x = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().x;
        size.y = gameResources::ResourceHolder::get().texture.get(resourceId).getSize().y;
        sprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
        sprite.setPosition(position);
        
    }
    void update(){
        sprite.setPosition(position);
    }
    void test();

void setPosition(sf::Vector2f pos){
    position = pos;
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

    private:
         virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const

        {
            target.draw(sprite);
        }
};

