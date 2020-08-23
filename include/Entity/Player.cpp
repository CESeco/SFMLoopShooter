#include "Player.hpp"
#ifdef _WIN32
    #include <windows.h>

    void sleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void sleep(int milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif
ActionMap<int> Player::keymap;

void Player::setDefaultMovements(){
    keymap.map(allowedMovement::left,Action(sf::Keyboard::A));
    keymap.map(allowedMovement::right,Action(sf::Keyboard::D));
    keymap.map(allowedMovement::top,Action(sf::Keyboard::W));
    keymap.map(allowedMovement::down,Action(sf::Keyboard::S));
    keymap.map(allowedMovement::fire,Action(sf::Mouse::Left));

}


/* void Player::cbind(){
     sListener.listen(NetworkHandler::get().getLocalPort()+portCount);
     
} */

void Player::sbind(bool keepOnAsk){
    sSocket.setBlocking(true); 
   // std::cout << NetworkHandler::get().getIp().toString() << " " << NetworkHandler::get().getPort()+portCount << std::endl;
    sf::Socket::Status status;
    //if(keepOnAsk){
        sleep(400);
    //}
    
   status =  sSocket.connect(NetworkHandler::get().getIp(),NetworkHandler::get().getPort()+portCount);
    
    sSocket.setBlocking(false);
}

void Player::listenNetworkEvents(){
 //std::cout << "i am working " << std::endl;
 sListener.listen(NetworkHandler::get().getLocalPort()+portCount);
 sf::TcpSocket sock;
 //std::cout << "currently listening on " << NetworkHandler::get().getLocalPort()+portCount << std::endl;
 //sock.receive(packet);
 sListener.accept(sock);
 //std::cout << "i am not getting it" << std::endl;

 while(true){
 std::string type;
 double x{0},y{0};
     //std::cout <<"keeping true all the time " << std::endl;
 sf::Packet packet;
 if(sock.receive(packet) == sf::Socket::Done){
    packet >> type >> x >> y;
    networkEvent(type,x,y);
    //std::cout << type << " " << x << " " << y << std::endl; 
 }
    
 }
}

void Player::networkEvent(std::string type,double x, double y){
    if(type=="movement"){
        setPosition(sf::Vector2f(x,y));
    }else if(type == "projectile"){
        projectile.emplace_back(new Projectile(sf::Vector2f(position.x+size.x/2,position.y+size.y/2),window.mapPixelToCoords(sf::Vector2i((int)x,(int)y)),DefaultResources::bullet, true, 30.f, 10.f,sCount));
        preservedProjectile.emplace_back(new Projectile(sf::Vector2f(position.x+size.x/2,position.y+size.y/2),window.mapPixelToCoords(sf::Vector2i((int)x,(int)y)), DefaultResources::bullet, true, 30.f, 10.f,sCount));
    }
}

void Player::bind(){
    {   

        
        //std::cout << "bind call to player with count " << sCount << std::endl;
        std::string proj{"projectile"};
        
        eventTarget.bind(allowedMovement::left, [&](const sf::Event &) {position.x -= .1f;
        direction=allowedMovement::left;
        std::string movement{"movement"};
        double a =  position.x;
        double b = position.y;
        sf::Packet packet;
        packet << movement << a << b;
        sSocket.send(packet);
         });
         
        eventTarget.bind(allowedMovement::right, [&](const sf::Event &) {position.x += .1f;
        direction=allowedMovement::right;
        std::string movement{"movement"};
        double a =  position.x;
        double b = position.y;
        sf::Packet packet;
        packet << movement << a << b;
        sSocket.send(packet);
         });

        eventTarget.bind(allowedMovement::top, [&](const sf::Event &) {position.y -= .1f;
        direction=allowedMovement::top;
        std::string movement{"movement"};
        double a =  position.x;
        double b = position.y;
        sf::Packet packet;
        packet << movement << a << b;
        sSocket.send(packet);
        
         });

        eventTarget.bind(allowedMovement::down, [&](const sf::Event &) {position.y += .1f;
        direction=allowedMovement::down;
        std::string movement{"movement"};
        double a =  position.x;
        double b = position.y;
        sf::Packet packet;
        packet << movement << a << b;
        sSocket.send(packet); 
        });

        eventTarget.bind(allowedMovement::fire, [&](const sf::Event &)  {
            //std::cout << "fired " << std::endl;
            sf::Vector2i destPos;
            destPos=sf::Mouse::getPosition(window);
            sf::Vector2f newPos{position.x+size.x/2,position.y+size.y/2};
            if (rateCount < 1)
            {
                std::string str{"projectile"};
                double a =  destPos.x;
                double b = destPos.y;
                sf::Packet packet;
                packet << str << a << b;
                sSocket.send(packet);

                //std::cout << "sent a packet of " << a << " and " << b << std::endl;

                if(!eventTarget.isPlayMode()){
                    projectile.emplace_back(new Projectile(newPos, window.mapPixelToCoords(destPos), DefaultResources::bullet, true, 30.f, 10.f,sCount));
                    preservedProjectile.emplace_back(new Projectile(newPos, window.mapPixelToCoords(destPos), DefaultResources::bullet, true, 30.f, 10.f,sCount));
                }else{
                    projectile.emplace_back(preservedProjectile.at(count));
                    count++;
                    if(count == preservedProjectile.size()) count = 0;
                }
                
                //packet << proj << destPos.x << destPos.y;
                //sSock.send(packet);
                rateCount++;
                rateFireCountClock.restart();
            }
        });
    }
}



void Player::processEvent(){
    if(allowRendering)
        eventTarget.processEvents();
}

void Player::setPosition(sf::Vector2f pos){
    position = pos;
}

sf::Vector2f Player::getPosition(){
    return position;
}

void Player::update(){
    if(allowRendering){
    sprite.setPosition(position);
    if(rateFireCountClock.getElapsedTime().asSeconds() > 0.5f){
        rateCount=0;
    }
    }
    //std::cout << "being called " << std::endl;
    
    if(!projectile.empty()){
    for(auto proj{projectile.begin()};proj < projectile.end() ; proj++ ){
        sf::Vector2f pos{(*proj)->getPosition()};
        if(pos.x > max_coords_x or pos.y > max_coords_y or pos.x < 0 or pos.y <0 or (*proj)->toRemove()){
            //std::cout << "proj to remove is " << (*proj)->toRemove() << std::endl;
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

void Player::reverseDirection(sf::Event event){
   //setPosition(sf::Vector2f(601,401));
    //eventTarget.setPlayMode();
    
    if(direction == allowedMovement::right) {
        position.x -= velocity;
    }else if(direction == allowedMovement::left){
        position.x += velocity;
    }else if(direction == allowedMovement::top){
        position.y += velocity;
    }else if(direction == allowedMovement::down){
        position.y -= velocity;
    }

    

    
    
}