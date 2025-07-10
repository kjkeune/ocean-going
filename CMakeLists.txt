cmake_minimum_required(VERSION 3.28)
project(ocean-going LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# include dll's for windows
if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Detect if in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG true)
else()
    set(DEBUG false)
endif()

# Configure config file
configure_file(
    ${CMAKE_SOURCE_DIR}/src/Config.hpp.in
    ${CMAKE_BINARY_DIR}/gen/Config.hpp
    @ONLY
)

include_directories(${CMAKE_BINARY_DIR}/gen)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

# add icon on windows
if(WIN32)
    enable_language(RC)
    set(APP_ICON_RESOURCE "${CMAKE_SOURCE_DIR}/assets/icon.rc")
endif()

add_executable(ocean-going src/Game.cpp
        src/Game.hpp
        src/handling/ResourceManager.cpp
        src/handling/ResourceManager.hpp
        src/handling/ObjectManager.cpp
        src/handling/ObjectManager.hpp
        src/handling/CollisionHandler.cpp
        src/handling/CollisionHandler.hpp
        src/handling/EventHandler.cpp
        src/handling/EventHandler.hpp
        src/handling/SceneLoader.cpp
        src/handling/SceneLoader.hpp
        src/object/GameObject.cpp
        src/object/GameObject.hpp
        src/object/Collidable.cpp
        src/object/Collidable.hpp
        src/object/ship/Ship.cpp
        src/object/ship/Ship.hpp
        src/object/ship/PlayerShip.cpp
        src/object/ship/PlayerShip.hpp
        src/object/ship/EnemyShip.cpp
        src/object/ship/EnemyShip.hpp
        src/object/ship/Cannon.cpp
        src/object/ship/Cannon.hpp
        src/object/ship/Sail.cpp
        src/object/ship/Sail.hpp
        src/object/world/World.cpp
        src/object/world/World.hpp
        src/object/world/Border.cpp
        src/object/world/Border.hpp
        src/object/world/Vortex.cpp
        src/object/world/Vortex.hpp
        src/object/entity/CannonBall.cpp
        src/object/entity/CannonBall.hpp
        src/object/entity/Effect.cpp
        src/object/entity/Effect.hpp
        src/object/entity/ShipWreck.cpp
        src/object/entity/ShipWreck.hpp
        src/object/drop/Drop.cpp
        src/object/drop/Drop.hpp
        src/object/drop/Treasure.cpp
        src/object/drop/Treasure.hpp
        src/object/drop/HealingBarrel.cpp
        src/object/drop/HealingBarrel.hpp
        src/object/drop/ShipParts.cpp
        src/object/drop/ShipParts.hpp
        src/object/world/Island.cpp
        src/object/world/Island.hpp
        src/object/ui/UIElement.cpp
        src/object/ui/UIElement.hpp
        src/object/ui/container/Container.cpp
        src/object/ui/container/Container.hpp
        src/object/ui/button/Button.cpp
        src/object/ui/button/Button.hpp
        src/object/ui/HealthBar.cpp
        src/object/ui/HealthBar.hpp
        src/util/Shapes.cpp
        src/util/Shapes.hpp
        src/util/Animation.cpp
        src/util/Animation.hpp
        src/util/RandomGenerator.cpp
        src/util/RandomGenerator.hpp
        src/constants/Colors.hpp
        src/object/ui/CannonDisplay.cpp
        src/object/ui/CannonDisplay.hpp
        src/util/InterpolateAnimation.cpp
        src/util/InterpolateAnimation.hpp
        src/constants/Paths.hpp
        src/object/ui/FPSDisplay.cpp
        src/object/ui/FPSDisplay.hpp
        src/factory/Upgrade.cpp
        src/factory/Upgrade.hpp
        src/factory/ShipConfiguration.cpp
        src/factory/ShipConfiguration.hpp
        src/handling/LevelManager.cpp
        src/handling/LevelManager.hpp
        src/object/ui/Label.cpp
        src/object/ui/Label.hpp
        src/object/ui/container/InGameUI.cpp
        src/object/ui/container/InGameUI.hpp
        src/object/ui/container/ShipMenuUI.cpp
        src/object/ui/container/ShipMenuUI.hpp
        src/object/ui/container/MainMenuUI.cpp
        src/object/ui/container/MainMenuUI.hpp
        src/object/ship/Ruder.cpp
        src/object/ship/Ruder.hpp
        src/object/ui/button/UpgradeButton.cpp
        src/object/ui/button/UpgradeButton.hpp
        src/object/ui/container/ShipPreview.cpp
        src/object/ui/container/ShipPreview.hpp
        src/util/Text.cpp
        src/util/Text.hpp
        src/object/ui/button/PlankButton.cpp
        src/object/ui/button/PlankButton.hpp
        src/object/ui/container/ShipPreview.cpp
        src/object/ui/container/ShipPreview.hpp
        src/object/ui/Minimap.cpp
        src/object/ui/Minimap.hpp
        src/util/MultiLayerTexture.cpp
        src/util/MultiLayerTexture.hpp
        src/object/ui/AttributeBar.cpp
        src/object/ui/AttributeBar.hpp
        src/handling/GameSaver.cpp
        src/handling/GameSaver.hpp
        src/object/ui/container/DeathScreen.cpp
        src/object/ui/container/DeathScreen.hpp
        src/object/ui/container/CompletedScreen.cpp
        src/object/ui/container/CompletedScreen.hpp
        src/object/world/IslandDecoration.cpp
        src/object/world/IslandDecoration.hpp
        src/object/ui/container/TutorialUI.cpp
        src/object/ui/container/TutorialUI.hpp
        ${APP_ICON_RESOURCE}
)

target_compile_features(ocean-going PRIVATE cxx_std_17)
target_link_libraries(ocean-going
        PRIVATE SFML::Graphics
        PRIVATE SFML::Audio
        PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(
        TARGET ocean-going POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copying assets to output directory"
)

add_custom_command(
        TARGET ocean-going POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/saves
        ${CMAKE_BINARY_DIR}/saves
        COMMENT "Copying assets to output directory"
)

# create symbolic link
#add_custom_command(TARGET ocean-going POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ocean-going.exe ${CMAKE_BINARY_DIR}/ocean-going
#        COMMENT "Creating symbolic link to ocean-going.exe"
#)

# include pthread dll for windows
if (MINGW)
    add_custom_command(TARGET ocean-going POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/libwinpthread-1.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif()