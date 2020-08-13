

template<typename T>
void ActionMap<T>::map(const T& key, const Action& action){
    _map.emplace(key,action);
}

template<typename T>
Action& ActionMap<T>::get(const T& key) 
{
    return _map.at(key);
}