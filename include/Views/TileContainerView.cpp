#include "TileContainerView.hpp"
#include "Configuration.hpp"
void TileContainerView::drawConstraintRectangle(sf::Vector2f position , sf::Vector2f size,sf::Color color){
    constraintsRectangle.emplace_back(sf::RectangleShape(size));
    constraintsRectangle.back().setPosition(position);
    constraintsRectangle.back().setFillColor(color);
}


void TileContainerView::drawConstraintBackground(){
    drawConstraintRectangle(sf::Vector2f(0,0),sf::Vector2f(screen_size_x/2.f,max_coords_y),sf::Color(50,130,171,255));
    drawConstraintRectangle(sf::Vector2f(0,0),sf::Vector2f(max_coords_x,screen_size_y/2),sf::Color(50,130,171,255));
    drawConstraintRectangle(sf::Vector2f((max_coords_x-screen_size_x/2),0.f),sf::Vector2f(screen_size_x/2,(max_coords_y-screen_size_y/2)),sf::Color(50,130,171,255));
    drawConstraintRectangle(sf::Vector2f(0.f,(max_coords_y-screen_size_y/2)),sf::Vector2f(max_coords_x,screen_size_y/2.f),sf::Color(50,130,171,255));
}
void TileContainerView::drawGrids(){
    int countX{screen_size_y/2};
    int countY{screen_size_y/2};
    while(countX <= max_coords_x){
        drawConstraintRectangle(sf::Vector2f(countX,0),sf::Vector2f(20,max_coords_y),sf::Color(109,149,62,255));
        countX+=screen_size_y/2;
    }
    while(countY <= (max_coords_y-screen_size_y/2)){
        drawConstraintRectangle(sf::Vector2f(0,countY),sf::Vector2f(max_coords_x,20),sf::Color(109,149,62,255));
        countY += screen_size_y/2;
    }
}

void TileContainerView::checkProjectileCollision(Player& player,std::shared_ptr<Entity> entity){
    for(auto proj : player.projectile){
        
       if(entity->collides(proj->getBounds())){
           //std::cout << "projectile collided in position " << entity->getPosition().x << " " << entity->getPosition().y << std::endl;
           proj->remove();
       }
       
    }
}