cmake_minimum_required(VERSION 3.7)
project(RacoonDay)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp menu.h demo_level.h levels.h)
add_executable(RacoonDay ${SOURCE_FILES})

set(SFML_DIR "C:/Users/littl/ClionProjects/RacoonDay/SFML-2.4.2/cmake/Modules")
set(CMAKE_MODULE_PATH "C:/Users/littl/ClionProjects/RacoonDay/SFML-2.4.2/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})

    target_link_libraries(RacoonDay ${SFML_LIBRARIES})
endif()
