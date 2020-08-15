#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <utility>
#include <Entity/Entity.hpp>
#include "Configuration.hpp"
#include <Entity/Configuration.hpp>

class TileMapView : public sf::Drawable{
    public:
       

        TileMapView(const std::string& str);
        bool processTiles();
    private:
        
        bool loadTilesFromFiles();
        void addEntities(int posX, int posY , Entities type);
        char tiles[max_tiles_x][max_tiles_y];
        std::list<std::pair<Entity*,int>> entityList;
        std::string fileName;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};