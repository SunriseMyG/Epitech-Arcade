cmake_minimum_required(VERSION 3.8)

project("Arcade" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lncurses -lSDL2 -lSDL2_ttf -lSDL2_image")

# Test Unit
option(BUILD_TESTS "Build the unit tests" OFF)

# Find SFML package
find_package(SFML REQUIRED system window graphics)

# Find ncurses package
find_package(Curses REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES "src/cores/*.cpp")
file(GLOB_RECURSE HEADERS "src/cores/*.hpp")

# Main executable
add_executable("arcade" ${SOURCES} ${HEADERS})

add_custom_command(TARGET arcade POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arcade> ../$<TARGET_FILE_NAME:arcade>)

# Include directories
target_include_directories(arcade PRIVATE ${SFML_INCLUDE_DIRS} ${CURSES_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)

# Configure games
message(STATUS "Starting to configure games...")
file(GLOB GAMES_LIST "src/games/*")
foreach(GAME_PATH ${GAMES_LIST})
    if(IS_DIRECTORY ${GAME_PATH})
        get_filename_component(GAME_NAME ${GAME_PATH} NAME)
        string(TOLOWER ${GAME_NAME} GAME_NAME)
        message(STATUS "Processing game: ${GAME_NAME}")

        file(GLOB GAME_SOURCES "${GAME_PATH}/*.cpp")
        message(STATUS "Game sources: ${GAME_SOURCES}")

        add_library("arcade_${GAME_NAME}" SHARED ${GAME_SOURCES})
        target_include_directories("arcade_${GAME_NAME}" PRIVATE ${GAME_PATH}/)
        target_sources("arcade_${GAME_NAME}" PRIVATE ${CMAKE_SOURCE_DIR}/src/games/IGames.hpp)

        set_target_properties("arcade_${GAME_NAME}" PROPERTIES
                              PREFIX ""
                              OUTPUT_NAME "arcade_${GAME_NAME}"
                              SUFFIX ".so"
                              LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    endif()
endforeach()
message(STATUS "Finished configuring games.")

# Configure graphical libraries
message(STATUS "Starting to configure Graphical libraries...")
file(GLOB GRAPHICAL_LIBS_LIST "src/lib/*")
foreach(GRAPHICAL_LIBS_PATH ${GRAPHICAL_LIBS_LIST})
    if(IS_DIRECTORY ${GRAPHICAL_LIBS_PATH})
        get_filename_component(GRAPHICAL_LIBS_NAME ${GRAPHICAL_LIBS_PATH} NAME)
        string(TOLOWER ${GRAPHICAL_LIBS_NAME} GRAPHICAL_LIBS_NAME)
        message(STATUS "Processing graphical library: ${GRAPHICAL_LIBS_NAME}")

        file(GLOB GRAPHICAL_LIBS_SOURCES "${GRAPHICAL_LIBS_PATH}/*.cpp")
        message(STATUS "Graphical library sources: ${GRAPHICAL_LIBS_SOURCES}")

        add_library("arcade_${GRAPHICAL_LIBS_NAME}" SHARED ${GRAPHICAL_LIBS_SOURCES})
        target_include_directories("arcade_${GRAPHICAL_LIBS_NAME}" PRIVATE ${GRAPHICAL_LIBS_PATH}/)

        set_target_properties("arcade_${GRAPHICAL_LIBS_NAME}" PROPERTIES
                              PREFIX ""
                              OUTPUT_NAME "arcade_${GRAPHICAL_LIBS_NAME}"
                              SUFFIX ".so"
                              LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    endif()
endforeach()
message(STATUS "Finished configuring Graphical libraries.")

if(BUILD_TESTS)
    enable_testing()

    add_executable(testReturns84WhenArgcNot2 tests/testReturns84WhenArgcNot2.cpp)
    add_test(NAME testReturns84WhenArgcNot2 COMMAND tests/testReturns84WhenArgcNot2)

    add_executable(testReturns84WhenFileNotFound tests/testReturns84WhenFileNotFound.cpp)
    add_test(NAME testReturns84WhenFileNotFound COMMAND testReturns84WhenFileNotFound)

    add_executable(testReturns84WhenInvalidFile tests/testReturns84WhenInvalidFile.cpp)
    add_test(NAME testReturns84WhenInvalidFile COMMAND testReturns84WhenInvalidFile)

    add_executable(testReturns0WhenValidFile tests/testReturns0WhenValidFile.cpp)
    add_test(NAME testReturns0WhenValidFile COMMAND testReturns0WhenValidFile)
endif()