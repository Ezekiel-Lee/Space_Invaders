cmake_minimum_required(VERSION 3.16)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:\\Users\\nsa05\\OneDrive\\Desktop\\game\\SFML-3.1.0\\lib\\cmake\\SFML")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(SpaceInvaders
    src/cpp/main.cpp
    src/cpp/Game.cpp
    src/cpp/Player.cpp
    src/cpp/Enemy.cpp
    src/cpp/Bullet.cpp
)

target_include_directories(SpaceInvaders PRIVATE src/header)

target_link_libraries(SpaceInvaders SFML::Graphics SFML::Window SFML::System)