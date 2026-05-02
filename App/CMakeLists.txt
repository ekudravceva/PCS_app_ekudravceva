cmake_minimum_required(VERSION 3.10)
project(MazeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Labyrinth.cpp
    src/DFSGenerator.cpp
    src/KruskalGenerator.cpp
    src/BFSFinder.cpp
    src/AStarFinder.cpp
    src/Visualizer.cpp
    src/StatisticsDecorator.cpp
    src/GenerateMazeCommand.cpp
    src/FindPathCommand.cpp
    src/ToggleModeCommand.cpp
    src/ShowStatisticsCommand.cpp
    src/NewMazeCommand.cpp
)

add_executable(MazeApp ${SOURCES})

target_include_directories(MazeApp PRIVATE src)

if(UNIX AND NOT APPLE)
    target_link_libraries(MazeApp pthread)
endif()
