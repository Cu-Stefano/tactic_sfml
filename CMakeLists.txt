cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Aggiungi il file PNG alla directory di outputs
file(COPY ${CMAKE_SOURCE_DIR}/resources
    DESTINATION ${CMAKE_BINARY_DIR}/bin/)
   

add_executable(TacticSFML
    "src/main.cpp"
    src/Map/mapBuilder.cpp
    src/Utilities/button.cpp src/Headers/state.h "src/Utilities/tile.cpp" "src/headers/tile.h" "src/headers/unit.h" "src/Utilities/unit.cpp")
target_link_libraries(TacticSFML PRIVATE SFML::Graphics)