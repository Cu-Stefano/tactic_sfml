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

file(COPY ${CMAKE_SOURCE_DIR}/resources
    DESTINATION ${CMAKE_BINARY_DIR}/bin/)

# Cerca automaticamente tutti i file .cpp e .h nella directory src e sottodirectory
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h)

# Aggiungi l'eseguibile principale con tutti i file trovati
add_executable(TacticSFML ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(TacticSFML PRIVATE SFML::Graphics)
