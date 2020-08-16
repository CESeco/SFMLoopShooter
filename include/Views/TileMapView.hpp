#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <utility>
#include <Entity/Entity.hpp>
#include "Configuration.hpp"
#include <Entity/Configuration.hpp>
#include <vector>

//have to call processTiles

class TileMapView : public sf::Drawable{
    public:
       
        
        TileMapView(const std::string& str);
        bool processTiles();
        
        
    private:
        friend class TileContainerView;
        bool loadTilesFromFiles();
        void addEntities(int posX, int posY , Entities type);
        char tiles[max_tiles_x][max_tiles_y];
        
        std::string fileName;
        std::vector<std::shared_ptr<Entity>> entityList;

       
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{

            for(auto c : entityList){
                //std::cout << c->getPosition().x << c->getPosition().y << std::endl;

                //check for collision with player right here

                target.draw(*c);
            }
        }

};