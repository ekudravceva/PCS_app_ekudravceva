set(PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Labyrinth.cpp
    ${CMAKE_SOURCE_DIR}/src/DFSGenerator.cpp
    ${CMAKE_SOURCE_DIR}/src/KruskalGenerator.cpp
    ${CMAKE_SOURCE_DIR}/src/BFSFinder.cpp
    ${CMAKE_SOURCE_DIR}/src/AStarFinder.cpp
    ${CMAKE_SOURCE_DIR}/src/Visualizer.cpp
    ${CMAKE_SOURCE_DIR}/src/StatisticsDecorator.cpp
    ${CMAKE_SOURCE_DIR}/src/StepByStepFinder.cpp
)

# исполняемый файл для тестов
add_executable(runTests
    test_main.cpp
    test_cell.cpp
    test_labyrinth.cpp
    test_dfs_generator.cpp
    test_kruskal_generator.cpp
    test_bfs_finder.cpp
    test_astar_finder.cpp
    test_scenarios.cpp
    ${PROJECT_SOURCES}  # ← ДОБАВИТЬ ЭТУ СТРОКУ (линкуем реализации)
)

target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(runTests GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)
