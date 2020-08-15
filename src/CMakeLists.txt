add_executable(SFMLoopShooter main.cpp)
target_link_libraries(SFMLoopShooter sfml-window sfml-graphics sfml-system sfml-network Entities Event Resource)

add_custom_command(TARGET SFMLoopShooter POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:SFMLoopShooter>)