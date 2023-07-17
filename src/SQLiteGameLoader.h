//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H


#include "IGameLoader.h"

class SQLiteGameLoader: public IGameLoader {
public:
    Game *LoadDataAndAssets(GameSettings settings) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H
