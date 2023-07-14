//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H


class IGameLoader {
public:
    virtual ~IGameLoader() = default;
    virtual Game LoadDataAndAssets() = 0;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H
