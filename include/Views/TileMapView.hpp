#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <utility>
#include <Entity/Entity.hpp>

class TileMapView : public sf::Drawable{
    public:
        TileMapView(const std::string& str);
    private:
        std::list<std::pair<Entity,int>
        
};