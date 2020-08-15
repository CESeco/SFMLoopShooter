#include "Entity.hpp"

class Projectile : public Entity{
    public:
        Projectile(sf::Vector2f pos, sf::Vector2f size, int resourceID, bool collideResponse)
        :Entity(pos,size,resourceId,collideResponse)
        {
            
        }
        void trigger();

        //what can be done with projectiles. they have startpos when they are fired and they have to travel to position defined by the 
        // 
};
