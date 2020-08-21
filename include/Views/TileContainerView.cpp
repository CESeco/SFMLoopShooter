#include "TileContainerView.hpp"
#include "Configuration.hpp"
void TileContainerView::drawConstraintRectangle(sf::Vector2f position , sf::Vector2f size,sf::Color color){
    constraintsRectangle.emplace_back(sf::RectangleShape(size));
    constraintsRectangle.back().setPosition(position);
    constraintsRectangle.back().setFillColor(color);
}


void TileContainerView::drawConstraintBackground(){
    drawConstraintRectangle(sf::Vector2f(0,0),sf::Vector2f(600.f,2400.f),sf::Color(50,130,171,255));
    drawConstraintRectangle(sf::Vector2f(0,0),sf::Vector2f(3600,400),sf::Color(50,130,171,255));
    drawConstraintRectangle(sf::Vector2f(3000.f,0.f),sf::Vector2f(600,2000),sf::Color(50,130,171,255));
    drawConstraintRectangle(sf::Vector2f(0.f,2000.f),sf::Vector2f(3600.f,400.f),sf::Color(50,130,171,255));
}
void TileContainerView::drawGrids(){
    int countX{400};
    int countY{400};
    while(countX <= 3600){
        drawConstraintRectangle(sf::Vector2f(countX,0),sf::Vector2f(20,2400),sf::Color(109,149,62,255));
        countX+=400;
    }
    while(countY <= 2000){
        drawConstraintRectangle(sf::Vector2f(0,countY),sf::Vector2f(3600,20),sf::Color(109,149,62,255));
        countY += 400;
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