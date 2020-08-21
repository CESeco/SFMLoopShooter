//make a copy of pair instead of event
template<typename T>
ActionTarget<T>::ActionTarget(const ActionMap<T>& map) :_actionMap(const_cast<ActionMap<T>&>(map)),recorder(true){  //start recording at first
    clock.restart();
    //std::cout << "action target inititated" << std::endl;
}

template<typename T>
bool ActionTarget<T>::processEvent(const sf::Event& event)
{
    bool res = false;
    for(auto& pair:_eventsRealTime){
        if(_actionMap.get(pair.first) == event)
        {
            pair.second(event);
            res = true;
            break;
        }
       }
    return res;
}

template <typename T>
void ActionTarget<T>::processEvents() 
{
    for(auto& pair: _eventsRealTime)
    {
        Action& action = _actionMap.get(pair.first);
        if(!playMode){
        if(_actionMap.get(pair.first).test()){
            
            pair.second(action._event);
            recorder.addEventRecord(pair.second);
        }
        }
        else{
           std::pair<sf::Time,FuncType> recordedEvent = recorder.getCurrentRecord();
           
           if(clock.getElapsedTime() >= recordedEvent.first){
               //std::cout << "caught a record at " << recordedEvent.first.asSeconds() << " when time is " << clock.getElapsedTime().asSeconds() << std::endl;
               if(recorder.increaseIterator())
                recordedEvent.second(action._event);
               break;
             }
           }
        }
        
    }


template<typename T>
void ActionTarget<T>::bind(const T& key, const FuncType& callback)
{
     _eventsRealTime.emplace_back(key,callback);
}

template<typename T>
void ActionTarget<T>::unbind(const T& key)
{
    auto remove_func = [&key](const std::pair<T,FuncType>& pair) -> bool
    {
        return pair.first == key;
    };

    const Action& action = _actionMap.get(key);
    _eventsRealTime.remove_if(remove_func);

}