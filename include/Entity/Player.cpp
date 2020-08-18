#include "Player.hpp"

ActionMap<int> Player::keymap;

void Player::setDefaultMovements(){
    keymap.map(allowedMovement::left,Action(sf::Keyboard::A));
    keymap.map(allowedMovement::right,Action(sf::Keyboard::D));
    keymap.map(allowedMovement::top,Action(sf::Keyboard::W));
    keymap.map(allowedMovement::down,Action(sf::Keyboard::S));
    keymap.map(allowedMovement::fire,Action(sf::Mouse::Left));

}

void Player::processEvent(){
        eventTarget.processEvents();
}

void Player::setPosition(sf::Vector2f pos){
    position = pos;
}

sf::Vector2f Player::getPosition(){
    return position;
}
void Player::update(){
    sprite.setPosition(position);
    if(rateFireCountClock.getElapsedTime().asSeconds() > 0.5f){
        rateCount=0;
    }

    if(!projectile.empty()){
    for(auto proj{projectile.begin()};proj < projectile.end() ; proj++ ){
        sf::Vector2f pos{(*proj)->getPosition()};
        if(pos.x > max_coords_x or pos.y > max_coords_y or pos.x < 0 or pos.y <0 or (*proj)->toRemove()){
            projectile.erase(proj);
            continue;
        }
        (*proj)->update();
        
      }
    }
}

sf::Vector2f Player::getSize(){
    return size;
}
void Player::setSize(sf::Vector2f si){
    size = si;
}
bool Player::collides(sf::FloatRect rect){
    return sprite.getGlobalBounds().intersects(rect);
}
bool Player::contains(sf::Vector2f pos){
    return sprite.getGlobalBounds().contains(pos);
}

void Player::reverseDirection(){
   //setPosition(sf::Vector2f(601,401));
    //eventTarget.setPlayMode();
    
    if(direction == allowedMovement::right) {
        position.x -= velocity;
    }else if(direction == allowedMovement::left){
        position.x += velocity;
    }else if(direction == allowedMovement::top){
        position.y += velocity;
    }else{
        position.y -= velocity;
    }
    
}