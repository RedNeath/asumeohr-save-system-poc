//
// Created by redneath on 16/07/23.
//

#include "HeavyResourcesCache.h"

using namespace std;

template <typename TResource>
HeavyResourcesCache<TResource>::HeavyResourcesCache(int capacity) {
    Capacity = capacity;
    Count = 0;
    Dictionary = map<string, HeavyResourceLink<TResource>>();
    LeastRecentlyUsed = nullptr;
    MostRecentlyUsed = nullptr;
}

template<typename TResource>
TResource *HeavyResourcesCache<TResource>::Get(const string &key) {
    TResource *val = nullptr;
    HeavyResourceLink<TResource> *link = Dictionary[key];

    if (link != nullptr) {
        ReorganiseList(link);
        val = link->GetValue();
    }

    return val;
}

template<typename TResource>
void HeavyResourcesCache<TResource>::Put(const std::string &key, TResource *resource) {
    // First, we try to see if there is a value for the given key. This way, we can eliminate many cases where we may
    // have to free some memory.
    HeavyResourceLink<TResource> *link = Dictionary[key];

    if (link != nullptr) {
        ReorganiseList(link);
        link->SetValue(resource);
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
void HeavyResourcesCache<TResource>::ReorganiseList(HeavyResourceLink<TResource> lastUsedLink) {
    if (lastUsedLink == LeastRecentlyUsed && lastUsedLink != MostRecentlyUsed) {
        // The value to retrieve was about to be deleted. If we don't move our pointer, it won't be pointing at the
        // least recently used anymore. So we take the one just next to.
        LeastRecentlyUsed = lastUsedLink->GetMoreUsedResourceLink();
    }
    if (lastUsedLink != MostRecentlyUsed) {
        // Moving the value at the end only if it isn't already (otherwise it will reference itself and be taken out
        // of the linked list)
        lastUsedLink->Move(MostRecentlyUsed, nullptr);
        MostRecentlyUsed = lastUsedLink;
    }
}

template<typename TResource>
void HeavyResourcesCache<TResource>::AddResource(const string &key, TResource *resource) {
    HeavyResourceLink<TResource> *link = HeavyResourceLink<TResource>(MostRecentlyUsed, nullptr, key, resource);
    MostRecentlyUsed = link;

    Count++;
}

template<typename TResource>
void HeavyResourcesCache<TResource>::DeleteLRU() {
    HeavyResourceLink<TResource> *toDelete = LeastRecentlyUsed;
    LeastRecentlyUsed = LeastRecentlyUsed->GetMoreUsedResourceLink();

    Dictionary.erase(toDelete->GetDictionaryKey());
    delete toDelete->GetValue();
    delete toDelete;

    Count--;
}
