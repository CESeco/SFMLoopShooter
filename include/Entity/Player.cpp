#include "Player.hpp"

ActionMap<int> Player::keymap;

void Player::setDefaultMovements(){
    keymap.map(allowedMovement::left,Action(sf::Keyboard::A));
    keymap.map(allowedMovement::right,Action(sf::Keyboard::D));
    keymap.map(allowedMovement::top,Action(sf::Keyboard::W));
    keymap.map(allowedMovement::down,Action(sf::Keyboard::S));
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
    std::cout << direction << std::endl;
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