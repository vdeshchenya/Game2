cmake_minimum_required(VERSION 3.13)
project(Game2)

set(CMAKE_CXX_STANDARD 17)
add_executable(Game2 Game.cpp ChooseLevel_scene.cpp Menu_scene.cpp Scene_manager.cpp main.cpp Scene.cpp Point.cpp Game_scene.cpp Pause_scene.cpp)

# Detect and add SFML
set(SFML_DIR "/media/data/GoogleCloud/MIPT/Inf/Game2/SFML-2.5.1/share/SFML/cmake/Modules")
set(CMAKE_MODULE_PATH "/media/data/GoogleCloud/MIPT/Inf/Game2/SFML-2.5.1/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Game2 ${SFML_LIBRARIES})
endif()
