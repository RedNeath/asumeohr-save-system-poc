cmake_minimum_required(VERSION 3.25)
project(asumeohr_save_system_poc)
include(FetchContent)

set(CMAKE_CXX_STANDARD 14 -lMagick++)

add_executable(asumeohr_save_system_poc
        src/Main.cpp src/IGameLoader.h src/entities/Player.h src/entities/Player.cpp src/entities/Item.h src/entities/Item.cpp src/entities/Equipment.h src/entities/Equipment.cpp src/entities/Weapon.h src/entities/Weapon.cpp src/interfaces/ILimitedDurabilityItem.h src/interfaces/IUsableItem.h src/entities/Map.h src/entities/Map.cpp src/entities/Skill.h src/entities/Skill.cpp src/enums/State.h src/enums/Difficulty.h src/cache/HeavyResourcesCache.h src/cache/HeavyResourceLink.h src/exceptions/BadInputException.h src/Game.h src/Game.cpp src/JsonGameLoader.h src/JsonGameLoader.cpp src/SQLiteGameLoader.h src/SQLiteGameLoader.cpp src/settings/GameSettings.h src/settings/GameSettings.cpp src/exceptions/SaveNotFound.h src/exceptions/EquipmentNotFound.h src/exceptions/ItemNotFound.h src/exceptions/SkillNotFound.h)
add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=16)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0)

find_package(ImageMagick COMPONENTS Magick++)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(asumeohr_save_system_poc PUBLIC ${ImageMagick_LIBRARIES})
target_link_libraries(asumeohr_save_system_poc PRIVATE nlohmann_json::nlohmann_json)
