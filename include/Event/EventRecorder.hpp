#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <utility>
#include <vector>
#include <functional>


using FuncType  = std::function<void(const sf::Event&)>; 
using Recorder = std::vector<std::pair<sf::Time,FuncType>>;



//for each player instance that uses ActionTarget. It is recorded automatically
//and played when not in control mode 

//call play before requesting for events 
class EventRecorder{
    public:
        EventRecorder(bool record){
            
            //std::cout << "recording has been started" << std::endl;
            this->record = record;
            clock.restart();
            
        }

        void setRecord(bool rec){
            record = rec;
        }
        
        void Play(){
            iterator = recordList.begin();
        }

        void addEventRecord(FuncType event){
            //std::cout << "recorded at " << clock.getElapsedTime().asSeconds() << std::endl;
            recordList.emplace_back(std::make_pair(clock.getElapsedTime(),event));
        }

        std::pair<sf::Time,FuncType> getCurrentRecord(){
                return *iterator;
        }
        bool increaseIterator(){
        bool res{false};
        if(iterator < recordList.end()){
            res=true;
            iterator++;
        }
        return res;
        }
    private:
        bool record;
        sf::Clock clock;
        Recorder recordList;
        Recorder::iterator iterator{recordList.begin()};
        
};

