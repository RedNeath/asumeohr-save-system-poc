//
// Created by redneath on 16/07/23.
//

#include "SQLiteGameLoader.h"
#include "exceptions/DatabaseUnavailableException.h"
#include "exceptions/ItemNotFoundException.h"
#include "exceptions/WeaponNotFoundException.h"
#include "exceptions/EquipmentNotFoundException.h"
#include "exceptions/SkillNotFoundException.h"
#include "exceptions/MapNotFoundException.h"

using namespace sqlite;
using namespace std;

Game *SQLiteGameLoader::LoadDataAndAssets(GameSettings settings) {
    // We open a connexion to the database. We are going to keep it open until the end of this method.
    database db(DB_PATH);

    Player *player = LoadPlayer(settings.SaveName, db);
    HeavyResourcesCache<Map> *mapCache = new HeavyResourcesCache<Map>(settings.MapCacheSize);

    // Putting the current map within the cache
    // If we tried to be smart, we could evaluate what maps are the most likely to appear next in memory and already
    // load them in the cache.
    mapCache->Put(player->GetMap()->GetIdentificationName(), player->GetMap());

    Game *game = new Game(player, mapCache, settings.SaveName);

    // Now that we have the game instance, we can load the global values. Being referenced in the Game object itself
    // will automatically turn them into "singletons".
    LoadAndAffectGlobalVariables(game, db);

    return game;
}

Item *SQLiteGameLoader::GetItem(int itemId) {
    Item *item = nullptr;
    database db(DB_PATH);

    if (itemId >= 2000 && itemId < 3000) { // It is a weapon
        item = GetWeapon(itemId);
    } else if (itemId >= 3000 && itemId < 4000) { // It is an equipment
        item = GetEquipment(itemId);
    } else {
        string query = R"(
        SELECT
            ITM.ItemId,
            ITM.Name,
            ITM.Description,
            ITM.Icon
        FROM Item ITM
        WHERE ITM.ItemId = ?)";

        for (tuple<int, string, string, vector<char>, int> row: db << query << itemId) {
            item = new Item(get<0>(row), get<1>(row), get<2>(row), get<3>(row));
        }

        if (item == nullptr) {
            throw ItemNotFoundException("No item with such Id: " + to_string(itemId) + ".");
        }
    }

    return item;
}

Weapon *SQLiteGameLoader::GetWeapon(int weaponId) {
    Weapon *weapon = nullptr;
    database db(DB_PATH);

    string query = R"(
        SELECT
            WPN.WeaponId,
            WPN.Name,
            WPN.Description,
            WPN.Icon,
            WPN.Damage,
            WPN.Frequency,
            WPN.LoadTime,
            WPN.Range,
            WPN.Durability
        FROM Weapon WPN
        WHERE WPN.WeaponId = ?)";

    for (tuple<int, string, string, vector<char>, float, float, float, int, int> row: db << query << weaponId) {
        weapon = new Weapon(get<0>(row), get<1>(row), get<2>(row), get<3>(row),
                            get<4>(row), get<5>(row), get<6>(row),
                            get<7>(row),get<8>(row), get<8>(row));
    }

    if (weapon == nullptr) {
        throw WeaponNotFoundException("No weapon with such Id: " + to_string(weaponId) + ".");
    }

    return weapon;
}

Equipment *SQLiteGameLoader::GetEquipment(int equipmentId) {
    Equipment *equipment = nullptr;
    database db(DB_PATH);

    string query = R"(
        SELECT
            EQP.EquipmentId,
            EQP.Name,
            EQP.Description,
            EQP.Icon,
            EQP.DamageAbsorption,
            EQP.Durability
        FROM Equipment EQP
        WHERE EQP.EquipmentId = ?)";

    for (tuple<int, string, string, vector<char>, float, int> row: db << query << equipmentId) {
        equipment = new Equipment(get<0>(row), get<1>(row), get<2>(row),
                                  get<3>(row), get<4>(row), get<5>(row),
                                  get<5>(row));
    }

    if (equipment == nullptr) {
        throw EquipmentNotFoundException("No equipment with such Id: " + to_string(equipmentId) + ".");
    }

    return equipment;
}

Skill *SQLiteGameLoader::GetSkill(int skillId) {
    Skill *skill = nullptr;
    database db(DB_PATH);

    string query = R"(
        SELECT
            SKL.SkillId,
            SKL.Name,
            SKL.Description,
            SKL.Icon
        FROM Skill SKL
        WHERE SKL.SkillId = ?)";

    for (tuple<int, string, string, vector<char>> row: db << query << skillId) {
        skill = new Skill(get<0>(row), get<1>(row), get<2>(row), get<3>(row));
    }

    if (skill == nullptr) {
        throw SkillNotFoundException("No skill with such Id: " + to_string(skillId) + ".");
    }

    return skill;
}

Map *SQLiteGameLoader::LoadMap(const string &mapName) {
    Map *map = nullptr;
    database db(DB_PATH);

    string query = R"(
        SELECT
            MapId,
            IdentificationName,
            Name,
            Height,
            Width,
            Sprite
        FROM Map
        WHERE IdentificationName = ?)";

    for (tuple<int, string, string, int, int, vector<char>> row: db << query << mapName) {
        map = new Map(get<0>(row), get<1>(row), get<2>(row), get<3>(row),
                      get<4>(row), get<5>(row));
    }

    if (map == nullptr) {
        throw MapNotFoundException("Could not find any map with the matching map name");
    }

    return map;
}

void SQLiteGameLoader::SaveData(Game *game, const string &saveName) {
    // The first thing to do is to check whether we need to save to another save than the one we loaded from.
    // Then, if it is not, we need to check if there is already a save with the given name, to be able to erase its data
    // once the transaction started.
    // If the name is brand new, we can simply write without having to make any other manipulations.
    // Again, if the name is the same as the one we loaded the data from, we will have to erase the data once the
    // transaction started, to make sure we do not have any remainder left.
    int existingSave;
    int playerId;
    database *db = new database(DB_PATH);

    *db << "SELECT COUNT(PlayerId) FROM Player WHERE SaveName = ?" << saveName >> existingSave;

    // Starting the real saving process
    *db << "begin;";
    if (existingSave) {
        playerId = WashSaveDataAndGetPlayerId(saveName, db);
    } else {
        playerId = LastPlayerId(db) + 1;
    }

    game->GetPlayer()->SetId(playerId);

    // Must be done first, otherwise foreign key constraints will trigger exceptions
    SavePlayerMetadata(game->GetPlayer(), saveName, db);
    SaveEquipments(game->GetPlayer(), db);
    SaveGlobalVariables(game, db);
    SaveInventory(game->GetPlayer(), db);
    SaveSkills(game->GetPlayer(), db);

    *db << "commit;";
}
Player *SQLiteGameLoader::LoadPlayer(const string &saveName, database db) {
    int mapId;
    Player *player;

    db << "SELECT PlayerId, Name, Map, PosX, PosY FROM Player WHERE SaveName = ?" << saveName
       >> [&](int PlayerId, string Name, int Map, int PosX, int PosY) {
        mapId = Map;
        player = new Player(PlayerId, Name, nullptr, PosX, PosY, nullptr, vector<Equipment*>(),
                            vector<stack<Item*>*>(), vector<Skill*>());
    };

    Map *map = LoadMap(mapId, db);
    Weapon *weapon = LoadWeapon(player, db);
    vector<Equipment*> equipments = LoadEquipments(player, db);
    vector<stack<Item*>*> inventory = LoadInventory(player, db);
    vector<Skill*> skills = LoadSkills(player, db);

    player->SetMap(map);
    player->SetWeapon(weapon);
    player->SetEquipments(equipments);
    player->SetInventory(inventory);
    player->SetSkills(skills);

    return player;
}

void SQLiteGameLoader::LoadAndAffectGlobalVariables(Game *game, database db) {
    game->Difficulty = static_cast<Difficulty>(GetGlobalValue("Difficulty", game->GetPlayer(), db));
    game->ChoseClass = static_cast<bool>(GetGlobalValue("ChoseClass", game->GetPlayer(), db));
    *game->ConqueredRedDungeon = static_cast<State>(GetGlobalValue("ConqueredRedDungeon",
                                                                   game->GetPlayer(), db));
    *game->CrossedThousandYearsForest = static_cast<State>(GetGlobalValue("CrossedThousandYearsForest",
                                                                          game->GetPlayer(), db));
    *game->ConqueredAbyssDungeon = static_cast<State>(GetGlobalValue("ConqueredAbyssDungeon",
                                                                     game->GetPlayer(), db));
    *game->StraightenedDawnKingdom = static_cast<State>(GetGlobalValue("StraightenedDawnKingdom",
                                                                       game->GetPlayer(), db));
    *game->ConqueredFinalDungeon = static_cast<State>(GetGlobalValue("ConqueredFinalDungeon",
                                                                     game->GetPlayer(), db));
}

Map *SQLiteGameLoader::LoadMap(int mapId, database db) {
    Map *map;

    db << "SELECT IdentificationName, Name, Height, Width, Sprite FROM Map WHERE MapId = ?" << mapId
       >> [&](string IdentificationName, string Name, int Height, int Width, vector<char> Sprite) {
        map = new Map(mapId, IdentificationName, Name, Height, Width, Sprite);
    };

    return map;
}

Weapon *SQLiteGameLoader::LoadWeapon(Player *player, database db) {
    Weapon *weapon = nullptr;

    string query = R"(
        SELECT
            WPN.WeaponId,
            WPN.Name,
            WPN.Description,
            WPN.Icon,
            WPN.Damage,
            WPN.Frequency,
            WPN.LoadTime,
            WPN.Range,
            WPN.Durability,
            PWP.DurabilityLeft
        FROM PlayerWeapons PWP
        INNER JOIN Weapon WPN ON PWP.Weapon = WPN.WeaponId
        WHERE PWP.Player = ? AND PWP.Equipped = TRUE)";

    for (tuple<int, string, string, vector<char>, float, float, float, int, int, int> row: db << query << player->GetId()) {
        weapon = new Weapon(get<0>(row), get<1>(row), get<2>(row), get<3>(row),
                get<4>(row), get<5>(row), get<6>(row), get<7>(row),
                get<8>(row), get<9>(row));
    }

    return weapon;
}

vector<Equipment*> SQLiteGameLoader::LoadEquipments(Player *player, database db) {
    vector<Equipment*> equipments;

    string query = R"(
        SELECT
            EQP.EquipmentId,
            EQP.Name,
            EQP.Description,
            EQP.Icon,
            EQP.DamageAbsorption,
            EQP.Durability,
            PEQ.DurabilityLeft
        FROM PlayerEquipments PEQ
        INNER JOIN Equipment EQP ON PEQ.Equipment = EQP.EquipmentId
        WHERE PEQ.Player = ? AND PEQ.Equipped = TRUE)";

    for (tuple<int, string, string, vector<char>, float, int, int> row: db << query << player->GetId()) {
        equipments.push_back(new Equipment(get<0>(row), get<1>(row), get<2>(row),
                get<3>(row), get<4>(row),  get<5>(row), get<6>(row)));
    }

    return equipments;
}

vector<std::stack<Item*>*> SQLiteGameLoader::LoadInventory(Player *player, database db) {
    vector<std::stack<Item*>*> inventory;

    // Loading actual items
    string query = R"(
        SELECT
            ITM.ItemId,
            ITM.Name,
            ITM.Description,
            ITM.Icon,
            PIT.Quantity
        FROM PlayerItems PIT
        INNER JOIN Item ITM ON PIT.Item = ITM.ItemId
        WHERE PIT.Player = ?)";

    for (tuple<int, string, string, vector<char>, int> row: db << query << player->GetId()) {
        stack<Item*> *itemsStack = new stack<Item*>();

        for (int i = 0; i < get<4>(row); i++) {
            itemsStack->push(new Item(get<0>(row), get<1>(row), get<2>(row),
                                         get<3>(row)));
        }

        inventory.push_back(itemsStack);
    }

    // Loading weapons
    query = R"(SELECT
                WPN.WeaponId,
                WPN.Name,
                WPN.Description,
                WPN.Icon,
                WPN.Damage,
                WPN.Frequency,
                WPN.LoadTime,
                WPN.Range,
                WPN.Durability,
                PWP.DurabilityLeft
            FROM PlayerWeapons PWP
            INNER JOIN Weapon WPN ON PWP.Weapon = WPN.WeaponId
            WHERE PWP.Player = ? AND PWP.Equipped = FALSE)";

    for (tuple<int, string, string, vector<char>, float, float, float, int, int, int> row: db << query << player->GetId()) {
        stack<Item*> *itemsStack = new stack<Item*>();

        // Quantity is necessarily one.
        itemsStack->push(new Weapon(get<0>(row), get<1>(row), get<2>(row),
                                    get<3>(row), get<4>(row), get<5>(row),
                                    get<6>(row), get<7>(row), get<8>(row),
                                    get<9>(row)));

        inventory.push_back(itemsStack);
    }

    // Loading equipments
    query = R"(
        SELECT
            EQP.EquipmentId,
            EQP.Name,
            EQP.Description,
            EQP.Icon,
            EQP.DamageAbsorption,
            EQP.Durability,
            PEQ.DurabilityLeft
        FROM PlayerEquipments PEQ
        INNER JOIN Equipment EQP ON PEQ.Equipment = EQP.EquipmentId
        WHERE PEQ.Player = ? AND PEQ.Equipped = FALSE)";

    for (tuple<int, string, string, vector<char>, float, int, int> row: db << query << player->GetId()) {
        stack<Item*> *itemsStack = new stack<Item*>();

        // Quantity is necessarily one.
        itemsStack->push(new Equipment(get<0>(row), get<1>(row), get<2>(row),
                                       get<3>(row), get<4>(row), get<5>(row),
                                       get<6>(row)));

        inventory.push_back(itemsStack);
    }

    return inventory;
}

vector<Skill *> SQLiteGameLoader::LoadSkills(Player *player, database db) {
    vector<Skill*> skills;

    string query = R"(
        SELECT
            SKL.SkillId,
            SKL.Name,
            SKL.Description,
            SKL.Icon
        FROM PlayerSkills PSK
        INNER JOIN Skill SKL ON PSK.Skill = SKL.SkillId
        WHERE PSK.Player = ?)";

    for (tuple<int, string, string, vector<char>> row: db << query << player->GetId()) {
        skills.push_back(new Skill(get<0>(row), get<1>(row), get<2>(row), get<3>(row)));
    }

    return skills;
}

int SQLiteGameLoader::GetGlobalValue(const string &variableName, Player *player, database db) {
    int value;

    db << "SELECT Val FROM GlobalVariables WHERE Player = ? AND Name = ?" << player->GetId() << variableName
       >> value;

    return value;
}

int SQLiteGameLoader::WashSaveDataAndGetPlayerId(const string &saveName, database *db) {
    int playerId;

    *db << "SELECT PlayerId FROM Player WHERE SaveName = ?" << saveName >> playerId;

    *db << "DELETE FROM GlobalVariables WHERE Player = ?" << playerId;
    *db << "DELETE FROM PlayerEquipments WHERE Player = ?" << playerId;
    *db << "DELETE FROM PlayerItems WHERE Player = ?" << playerId;
    *db << "DELETE FROM PlayerSkills WHERE Player = ?" << playerId;
    *db << "DELETE FROM PlayerWeapons WHERE Player = ?" << playerId;
    *db << "DELETE FROM Player WHERE PlayerId = ?" << playerId;

    return playerId;
}

int SQLiteGameLoader::LastPlayerId(database *db) {
    int lastPlayerId;
    *db << "SELECT MAX(PlayerId) FROM Player" >> lastPlayerId;
    return lastPlayerId;
}

int SQLiteGameLoader::LastGlobalVariableId(database *db) {
    int lastGlobalVariableId;
    *db << "SELECT MAX(GlobalVariableId) FROM GlobalVariables" >> lastGlobalVariableId;
    return lastGlobalVariableId;
}

void SQLiteGameLoader::SaveEquipments(Player *player, database *db) {
    for (Equipment *equipment: player->GetEquipments()) {
        *db << "INSERT INTO PlayerEquipments(Player, Equipment, DurabilityLeft, Equipped) VALUES (?, ?, ?, TRUE)"
            << player->GetId()
            << equipment->GetId()
            << equipment->GetDurabilityLeft();
    }
}

void SQLiteGameLoader::SaveGlobalVariables(Game *game, database *db) {
    int nextGlobalVariableId = LastGlobalVariableId(db) + 1;

    *db << R"(
        INSERT INTO GlobalVariables(GlobalVariableId, Name, Val, Player)
        VALUES
            (?, 'Difficulty', ?, ?),
            (?, 'ChoseClass', ?, ?),
            (?, 'ConqueredRedDungeon', ?, ?),
            (?, 'CrossedThousandYearsForest', ?, ?),
            (?, 'ConqueredAbyssDungeon', ?, ?),
            (?, 'StraightenedDawnKingdom', ?, ?),
            (?, 'ConqueredFinalDungeon', ?, ?)
        )"

        << nextGlobalVariableId     << (int)  game->Difficulty                  << game->GetPlayer()->GetId()
        << nextGlobalVariableId + 1 << (int)  game->ChoseClass                  << game->GetPlayer()->GetId()
        << nextGlobalVariableId + 2 << (int) *game->ConqueredRedDungeon         << game->GetPlayer()->GetId()
        << nextGlobalVariableId + 3 << (int) *game->CrossedThousandYearsForest  << game->GetPlayer()->GetId()
        << nextGlobalVariableId + 4 << (int) *game->ConqueredAbyssDungeon       << game->GetPlayer()->GetId()
        << nextGlobalVariableId + 5 << (int) *game->StraightenedDawnKingdom     << game->GetPlayer()->GetId()
        << nextGlobalVariableId + 6 << (int) *game->ConqueredFinalDungeon       << game->GetPlayer()->GetId();
}


void SQLiteGameLoader::SaveInventory(Player *player, database *db) {
    for (auto *itemStack: player->GetInventory()) {

        if (itemStack->top()->GetRealType() == ItemType::EQUIPMENT) {
            *db << "INSERT INTO PlayerEquipments(Player, Equipment, DurabilityLeft, Equipped) VALUES (?, ?, ?, FALSE)"
                << player->GetId()
                << itemStack->top()->GetId()
                << ((Equipment*) itemStack->top())->GetDurabilityLeft();

        } else if (itemStack->top()->GetRealType() == ItemType::WEAPON) {
            *db << "INSERT INTO PlayerWeapons(Player, Weapon, DurabilityLeft, Equipped) VALUES (?, ?, ?, FALSE)"
                << player->GetId()
                << itemStack->top()->GetId()
                << ((Weapon*) itemStack->top())->GetDurabilityLeft();

        } else {
            *db << "INSERT INTO PlayerItems(Player, Item, Quantity) VALUES (?, ?, ?)"
                << player->GetId()
                << itemStack->top()->GetId()
                << itemStack->size();
        }
    }
}

void SQLiteGameLoader::SavePlayerMetadata(Player *player, const string &saveName, database *db) {
    // We have to reinsert the player and their weapon (if they have one)
    *db << "INSERT INTO Player(PlayerId, SaveName, Name, Map, PosX, PosY) VALUES (?, ?, ?, ?, ?, ?)"
        << player->GetId()
        << saveName
        << player->GetName()
        << player->GetMap()->GetId()
        << player->GetPosX()
        << player->GetPosY();

    Weapon *weapon = player->GetWeapon();
    if (weapon != nullptr) {
        *db << "INSERT INTO PlayerWeapons(Player, Weapon, DurabilityLeft, Equipped) VALUES (?, ?, ?, TRUE)"
            << player->GetId()
            << weapon->GetId()
            << weapon->GetDurabilityLeft();
    }
}

void SQLiteGameLoader::SaveSkills(Player *player, database *db) {
    for (Skill *skill: player->GetSkills()) {
        *db << "INSERT INTO PlayerSkills(Player, Skill) VALUES (?, ?)"
            << player->GetId()
            << skill->GetId();
    }
}
