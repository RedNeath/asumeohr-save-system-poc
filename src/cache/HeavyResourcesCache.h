//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCESCACHE_H
#define ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCESCACHE_H

#include <map>
#include "HeavyResourceLink.h"

template <typename TResource>
class HeavyResourcesCache {
private:
    int Capacity;
    int Count;
    std::map<std::string, HeavyResourceLink<TResource>*> Dictionary;
    HeavyResourceLink<TResource> *LeastRecentlyUsed;
    HeavyResourceLink<TResource> *MostRecentlyUsed;

    void ReorganiseList(HeavyResourceLink<TResource> lastUsedLink);
    void AddResource(const std::string &key, TResource *resource);
    void DeleteLRU();

public:
    explicit HeavyResourcesCache(int capacity);

    TResource *Get(const std::string &key);
    void Put(const std::string &key, TResource *resource);
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCESCACHE_H
