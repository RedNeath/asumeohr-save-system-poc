cmake_minimum_required(VERSION 3.25)
project(asumeohr_save_system_poc)
include(FetchContent)

set(CMAKE_CXX_STANDARD 14)

add_executable(asumeohr_save_system_poc
        src/Main.cpp src/IGameLoader.h src/IGameLoader.cpp src/entities/Player.h src/entities/Player.cpp src/entities/Item.h src/entities/Item.cpp src/entities/Equipment.h src/entities/Equipment.cpp src/entities/Weapon.h src/entities/Weapon.cpp src/interfaces/ILimitedDurabilityItem.h src/interfaces/IUsableItem.h src/entities/Map.h src/entities/Map.cpp src/entities/Skill.h src/entities/Skill.cpp src/enums/State.h src/enums/Difficulty.h src/cache/HeavyResourcesCache.h src/cache/HeavyResourcesCache.cpp src/cache/HeavyResourceLink.h src/cache/HeavyResourceLink.cpp src/exceptions/BadInputException.h)

FETCHCONTENT_DECLARE(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FETCHCONTENT_MAKEAVAILABLE(json)

target_link_libraries(asumeohr_save_system_poc PRIVATE nlohmann_json::nlohmann_json)
