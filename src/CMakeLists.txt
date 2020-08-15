add_executable(SFMLoopShooter main.cpp)
get_property(libslist GLOBAL PROPERTY game_libs_list)
foreach(a IN LISTS libslist)
    message(STATUS ${a})
endforeach()

message(STATUS ${libslist})
message("test")
target_link_libraries(SFMLoopShooter ${SFML_libs} ${libslist})

add_custom_command(TARGET SFMLoopShooter POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:SFMLoopShooter>)