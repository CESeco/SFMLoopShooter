#include "Widget.hpp"
#include <functional>
#include <string>
#include <Event/ActionMap.hpp>
#include <Event/ActionTarget.hpp>
#include <Event/Action.hpp>

//call setMappings before instantiating this class
class Button: public Widget{
    public:
    enum ButtonEvent{
        press
    };
        Button(sf::Vector2f position,sf::Vector2f size,int fontResourceID, const sf::RenderWindow& window);
        void setText(const std::string& str,int size,sf::Color color);
        void setBackgroundColor(const sf::Color color);
        sf::Vector2f getSize() const override;
        void setPosition(const sf::Vector2f& position) override;
        void processEvent(const sf::RenderWindow& window) override;


        

        static void setMappings();
        void addTargets();

    private:
        
        const sf::RenderWindow& window;
        static ActionMap<ButtonEvent> map;
        ActionTarget<ButtonEvent> actionTarget;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states);

        

      
        
};