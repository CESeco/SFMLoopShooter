add_library(Event  Event/Action.hpp
                   Event/Action.cpp
                   Event/ActionMap.hpp
                   Event/ActionMap.tpl
                   Event/ActionTarget.hpp
                   Event/ActionTarget.tpl)

set(EventCpp "${CMAKE_CURRENT_SOURCE_DIR}/Event/Action.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/Event/ActionMap.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/Event/ActionTarget.cpp")

add_library(Resource Resources/ResourceManager.hpp
                     Resources/ResourceManager.cpp
                     Resources/ResourceManager.tpl)

target_include_directories(Event PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Resource PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

