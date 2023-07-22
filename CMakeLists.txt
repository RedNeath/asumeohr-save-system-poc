cmake_minimum_required(VERSION 3.25)
project(asumeohr_save_system_poc)
include(FetchContent)

set(CMAKE_CXX_STANDARD 14 -lMagick++)

add_executable(asumeohr_save_system_poc
        src/Main.cpp src/IGameLoader.h src/entities/Player.h src/entities/Player.cpp src/entities/Item.h src/entities/Item.cpp src/entities/Equipment.h src/entities/Equipment.cpp src/entities/Weapon.h src/entities/Weapon.cpp src/interfaces/ILimitedDurabilityItem.h src/interfaces/IUsableItem.h src/entities/Map.h src/entities/Map.cpp src/entities/Skill.h src/entities/Skill.cpp src/enums/State.h src/enums/Difficulty.h src/cache/HeavyResourcesCache.h src/cache/HeavyResourceLink.h src/exceptions/BadInputException.h src/Game.h src/Game.cpp src/JsonGameLoader.h src/JsonGameLoader.cpp src/SQLiteGameLoader.h src/SQLiteGameLoader.cpp src/settings/GameSettings.h src/settings/GameSettings.cpp src/exceptions/SaveNotFound.h src/exceptions/EquipmentNotFound.h src/exceptions/ItemNotFound.h src/exceptions/SkillNotFound.h src/interfaces/ICommand.h src/enums/Commands.h src/exceptions/CommandNotFoundException.h src/commands/end/SaveCommand.h src/commands/end/SaveCommand.cpp src/commands/end/SaveAndExitCommand.h src/commands/end/SaveAndExitCommand.cpp src/commands/end/ExitCommand.h src/commands/end/ExitCommand.cpp src/commands/actions/GiveCommand.h src/commands/actions/GiveCommand.cpp src/commands/actions/DropCommand.h src/commands/actions/DropCommand.cpp src/commands/actions/EquipCommand.h src/commands/actions/EquipCommand.cpp src/commands/actions/UnequipCommand.h src/commands/actions/UnequipCommand.cpp src/commands/actions/LearnCommand.h src/commands/actions/LearnCommand.cpp src/commands/actions/ForgetCommand.h src/commands/actions/ForgetCommand.cpp src/commands/actions/MoveCommand.h src/commands/actions/MoveCommand.cpp src/commands/actions/TeleportCommand.h src/commands/actions/TeleportCommand.cpp src/commands/settings/SetDifficultyCommand.h src/commands/settings/SetDifficultyCommand.cpp src/commands/settings/ToggleChoseClassCommand.h src/commands/settings/ToggleChoseClassCommand.cpp src/commands/settings/ProgressCommand.h src/commands/settings/ProgressCommand.cpp src/commands/display/DisplayAllCommand.h src/commands/display/DisplayAllCommand.cpp src/commands/display/DisplayPlayerCommand.h src/commands/display/DisplayPlayerCommand.cpp src/commands/display/DisplayMapCacheCommand.h src/commands/display/DisplayMapCacheCommand.cpp src/commands/display/DisplayWeaponCommand.h src/commands/display/DisplayWeaponCommand.cpp src/commands/display/DisplayEquipmentsCommand.h src/commands/display/DisplayEquipmentsCommand.cpp src/commands/display/DisplayInventoryCommand.h src/commands/display/DisplayInventoryCommand.cpp src/commands/display/DisplaySkillsCommand.h src/commands/display/DisplaySkillsCommand.cpp src/commands/display/DisplayMapCommand.h src/commands/display/DisplayMapCommand.cpp src/exceptions/NotImplementedException.h src/exceptions/NoMatchingSignature.h)
add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=16)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0)

find_package(ImageMagick COMPONENTS Magick++)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(asumeohr_save_system_poc PUBLIC ${ImageMagick_LIBRARIES})
target_link_libraries(asumeohr_save_system_poc PRIVATE nlohmann_json::nlohmann_json)
