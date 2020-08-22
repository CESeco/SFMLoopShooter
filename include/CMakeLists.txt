

function(add_lib_and_include_directories LibName)
add_library(${LibName} ${ARGN})
target_include_directories(${LibName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
get_property(temp GLOBAL PROPERTY game_libs_list)
set_property(GLOBAL PROPERTY game_libs_list "${temp}" "${LibName}")
endfunction()

add_lib_and_include_directories(Entities 
                   Entity/Entity.hpp
                   Entity/StaticEntities.hpp
                   Entity/Projectile.hpp
                   Entity/Player.hpp
                   Entity/Player.cpp
                   Entity/Configuration.hpp
                   )



add_lib_and_include_directories(Event Event/Action.hpp
                   Event/Action.cpp
                   Event/ActionMap.hpp
                   Event/ActionMap.tpl
                   Event/ActionTarget.hpp
                   Event/ActionTarget.tpl
                   Event/EventRecorder.hpp)



add_lib_and_include_directories(Resource Resources/ResourceManager.hpp
                     Resources/ResourceManager.tpl
                     Resources/ResourceHolder.hpp
                     Resources/ResourceHolder.cpp
                     )
                     

add_lib_and_include_directories(Views Views/Configuration.hpp Views/TileMapView.hpp Views/TileMapView.cpp Views/TileContainerView.hpp Views/TileContainerView.cpp Views/SplashScreen.hpp)

add_lib_and_include_directories(GameLogic GameLogic/GameLogic.hpp GameLogic/GameLogic.cpp GameLogic/NetworkInterface.hpp GameLogic/GameHost.hpp GameLogic/GameClient.hpp GameLogic/NetworkHandler.hpp)

add_lib_and_include_directories(GUI GUI/Widget.hpp GUI/Button.hpp GUI/Button.cpp GUI/Widget.hpp GUI/Widget.cpp GUI/TextBox.hpp GUI/TextBox.cpp)



