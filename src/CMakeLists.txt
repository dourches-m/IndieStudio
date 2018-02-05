cmake_minimum_required(VERSION 3.5)
project(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -std=c++14"
        PARENT_SCOPE)

set (SOURCE_FILES
        ${SOURCE_FILES}
        src/MapManager/MapManager.cpp
        src/srcmap/MapGeneration.cpp
        src/srcmap/MapOgre.cpp
        src/srcmap/Map.cpp
        src/srcmap/TileBase.cpp
        src/srcmap/TileBomb.cpp
        src/srcmap/TileBonusBasket.cpp
        src/srcmap/TileBonusBomb.cpp
        src/srcmap/TileBonusFlame.cpp
        src/srcmap/TileDestroy.cpp
        src/srcmap/TileExplosion.cpp
        src/srcmap/TileInde.cpp
        src/GameLoop/GameLoop.cpp
        src/EntitiesManager/EntitiesManager.cpp
        src/EntitiesManager/AMovableEntity/AMovableEntity.cpp
        src/InputManager/InputManager.cpp
        src/SceneManager/SceneManager.cpp
        src/ScoreManager/ScoreManager.cpp
        src/PlayerManager/PlayerManager.cpp
        src/BombManager/BombManager.cpp
        src/IaManager/IaManager.cpp
        src/InputLinker/InputLinker.cpp
        src/ConfigData/ConfigData.cpp
        src/MenuManager/MenuManager.cpp
        src/SoundManager/SoundManager.cpp
        PARENT_SCOPE)

set(HDRS
        ${HDRS}
        src/MapManager/MapManager.hpp
        src/includemap/MapGeneration.hpp
        src/includemap/ATile.hpp
        src/includemap/ITile.hpp
        src/includemap/Map.hpp
        src/includemap/TileBase.hpp
        src/includemap/TileBomb.hpp
        src/includemap/TileBonusBasket.hpp
        src/includemap/TileBonusBomb.hpp
        src/includemap/TileBonusFlame.hpp
        src/includemap/TileDestroy.hpp
        src/includemap/TileExplosion.hpp
        src/includemap/TileInde.hpp
        src/includes/Pos.hpp
        src/BombManager/BombManager.hpp
        src/PlayerManager/PlayerManager.hpp
        src/GameLoop/GameLoop.hpp
        src/InputManager/InputManager.hpp
        src/GUIManager/GUIManager.hpp
        src/EntitiesManager/EntitiesManager.hpp
        src/EntitiesManager/AMovableEntity/AMovableEntity.hpp
        src/EntitiesManager/IMovableEntity/IMovableEntity.hpp
        src/SceneManager/SceneManager.hpp
        src/SoundManager/SoundManager.hpp
        src/IaManager/IaManager.hpp
        src/InputLinker/InputLinker.hpp
        src/ConfigData/ConfigData.hpp
        src/InputLinker/KeyMap.hpp
        src/MenuManager/MenuManager.hpp
        PARENT_SCOPE)
