cmake_minimum_required(VERSION 3.10)
project(MazeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл
add_executable(MazeApp
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
    src/StepByStepFinder.cpp
)

target_include_directories(MazeApp PRIVATE src)

if(UNIX AND NOT APPLE)
    target_link_libraries(MazeApp pthread)
endif()

# Подключение GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Подключаем тесты
add_subdirectory(tests)
