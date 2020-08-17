#pragma once
#include "Action.hpp"
#include "ActionMap.hpp"
#include "EventRecorder.hpp"
#include <functional>
#include <utility>
#include <list>

using FuncType  = std::function<void(const sf::Event&)>;

template<typename T = int>
class ActionTarget{
    public:
        ActionTarget(const ActionTarget<T>&) = delete;
        ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;

        

        ActionTarget(const ActionMap<T>& map);
        
        bool processEvent(const sf::Event& event);
        void processEvents();
        
        void setPlayMode(){
            playMode = true;
            clock.restart();
            recorder.Play();
            
        }

        bool isPlayMode(){
            return playMode;
        }

        void setRecordMode(){
            playMode = false;
        }
        void bind(const T& key, const FuncType& function);
        void unbind(const T& key);
    
    private:
        std::list<std::pair<T,FuncType>> _eventsRealTime;
        ActionMap<T>& _actionMap;
        bool playMode{false};
        sf::Clock clock;
        EventRecorder recorder;
};
#include "ActionTarget.tpl"