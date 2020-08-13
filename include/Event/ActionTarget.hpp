#pragma once
#include "Action.hpp"
#include "ActionMap.hpp"
#include <functional>
#include <utility>
#include <list>

template<typename T = int>
class ActionTarget{
    public:
        ActionTarget(const ActionTarget<T>&) = delete;
        ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;

        using FuncType  = std::function<void(const sf::Event&)>;

        ActionTarget(const ActionMap<T>& map);
        
        bool processEvent(const sf::Event& event) const;
        void processEvents() const;
        
        void bind(const T& key, const FuncType& function);
        void unbind(const T& key);
    
    private:
        std::list<std::pair<T,FuncType>> _eventsRealTime;
        ActionMap<T>& _actionMap;
};
#include "ActionTarget.tpl"