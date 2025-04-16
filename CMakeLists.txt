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
   
add_executable(TacticSFML
    "src/main.cpp"
    src/Map/mapBuilder.cpp
    src/Map/mapLogic.cpp
    src/Utilities/button.cpp src/Headers/state.h "src/Map/tile.cpp" "src/headers/tile.h" "src/headers/unit.h" 
    "src/models/unit.cpp" "src/headers/animatedSprite.h" "src/Headers/mapLogic.h" "src/Utilities/animatedSprite.cpp" 
    "src/Utilities/animState.cpp" "src/models/weapon.cpp" "src/headers/weapon.h"  
    "src/TurnLogic/AllayTurn.cpp" "src/TurnLogic/enemyTurn.cpp" "src/headers/actionState.hpp" 
    "src/TurnLogic/Actions/0_chooseTile.cpp" "src/TurnLogic/Actions/1_tileSelected.cpp"
    "src/TurnLogic/Actions/2_chooseAttack.cpp" "src/TurnLogic/Actions/3_attack.cpp" 
    "src/headers/1_tileSelected.h" "src/headers/2_chooseAttack.h" "src/TurnLogic/turnState.cpp" "src/headers/pathAlgorithm.h" "src/Utilities/pathAlgorithm.cpp")
target_link_libraries(TacticSFML PRIVATE SFML::Graphics)