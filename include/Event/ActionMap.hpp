#pragma once

#include "Action.hpp"
#include <unordered_map>

template<typename T>
class ActionMap
{
    public:
        ActionMap(const ActionMap<T>&) = delete;
        ActionMap<T>& operator=(const ActionMap<T>&)=delete;

        ActionMap() = default;

        void map(const T& key, const Action& action);
        Action& get(const T& key);
    private:
        std::unordered_map<T,Action> _map;

};
#include "ActionMap.tpl"