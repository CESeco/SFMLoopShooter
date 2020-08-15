cmake_minimum_required(VERSION 3.10)


project(SFMLoopShooter)
set_property(GLOBAL PROPERTY game_libs_list)
set(SFML_libs sfml-window sfml-system sfml-graphics sfml-network sfml-audio)

add_subdirectory("include")
add_subdirectory("src")

