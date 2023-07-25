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

    void ReorganiseList(HeavyResourceLink<TResource> *lastUsedLink);
    void AddResource(const std::string &key, TResource *resource);
    void DeleteLRU();

public:
    explicit HeavyResourcesCache(int capacity);
    ~HeavyResourcesCache();

    TResource *Get(const std::string &key);
    void Put(const std::string &key, TResource *resource);
};

template<typename TResource>
HeavyResourcesCache<TResource>::HeavyResourcesCache(int capacity) {
    Capacity = capacity;
    Count = 0;
    Dictionary = std::map<std::string, HeavyResourceLink<TResource>*>();
    LeastRecentlyUsed = nullptr;
    MostRecentlyUsed = nullptr;
}

template<typename TResource>
HeavyResourcesCache<TResource>::~HeavyResourcesCache() {
    // We are going to delete every link from the dictionary. Doing it this way will dispense us from freeing the two
    // pointers (LRU & MRU).
    if (!Dictionary.empty()) {
        for(auto&& value: Dictionary) {
            delete value.second;
        }
    }
}

template<typename TResource>
TResource *HeavyResourcesCache<TResource>::Get(const std::string &key) {
    TResource *val = nullptr;
    auto link = Dictionary.find(key);

    if (link != Dictionary.end()) {
        ReorganiseList(link->second);
        val = link->second->GetValue();
    }

    return val;
}

template<typename TResource>
void HeavyResourcesCache<TResource>::Put(const std::string &key, TResource *resource) {
    // First, we try to see if there is a value for the given key. This way, we can eliminate many cases where we may
    // have to free some memory.
    auto link = Dictionary.find(key);

    if (link != Dictionary.end()) {
        ReorganiseList(link->second);
        link->second->SetValue(resource);
    } else if (Count < Capacity) {
        AddResource(key, resource);
    } else {
        // We will have to free some space for the new value to add.
        // Just in case the max capacity is set to 1, we add the new value before to remove the LRU.
        AddResource(key, resource);
        DeleteLRU();
    }
}

template<typename TResource>
void HeavyResourcesCache<TResource>::ReorganiseList(HeavyResourceLink<TResource> *lastUsedLink) {
    // Four possible cases:
    // -> The link is the most recently used
    // -> THe link is the least recently used
    // -> The link is in the middle of the cache
    // -> The link is the most recently used AND the least recently used (cache with 1 element)
    if (LeastRecentlyUsed != MostRecentlyUsed && lastUsedLink != MostRecentlyUsed) {
        if (lastUsedLink == LeastRecentlyUsed) {
            LeastRecentlyUsed = lastUsedLink->GetMoreUsedResourceLink();
        }

        lastUsedLink->Move(MostRecentlyUsed, nullptr);
        MostRecentlyUsed = lastUsedLink;
    }
}

template<typename TResource>
void HeavyResourcesCache<TResource>::AddResource(const std::string &key, TResource *resource) {
    HeavyResourceLink<TResource> *link = new HeavyResourceLink<TResource>(MostRecentlyUsed, nullptr, key, resource);
    MostRecentlyUsed = link;
    Dictionary.insert({key, link});

    if (Count == 0) {
        LeastRecentlyUsed = link;
    }

    Count++;
}

template<typename TResource>
void HeavyResourcesCache<TResource>::DeleteLRU() {
    HeavyResourceLink<TResource> *toDelete = LeastRecentlyUsed;
    LeastRecentlyUsed = LeastRecentlyUsed->GetMoreUsedResourceLink();
    LeastRecentlyUsed->SetLessUsedResourceLink(nullptr);

    Dictionary.erase(toDelete->GetDictionaryKey());
    //delete toDelete->GetValue();
    delete toDelete;

    Count--;
}

#endif //ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCESCACHE_H
