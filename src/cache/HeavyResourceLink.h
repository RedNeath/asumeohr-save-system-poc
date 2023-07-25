//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCELINK_H
#define ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCELINK_H

#include <string>
#include "../exceptions/BadInputException.h"

/**
 * This is the link object for the double linked list that belongs to the cache.
 */
template <typename TResource>
class HeavyResourceLink {
private:
    HeavyResourceLink<TResource> *LessUsedResourceLink;
    HeavyResourceLink<TResource> *MoreUsedResourceLink;
    std::string DictionaryKey;
    TResource *Value;

public:
    /**
     * Creates a new link and adds it to the list.
     *
     * @param lessUsedResourceLink The link that contains the pointer to the resource that has been less recently used
     * than this one. May be null.
     * @param moreUsedResourceLink The link that contains the pointer to the resource that has been more recently used
     * than this one. May be null.
     * @param dictionaryKey The key of the cache dictionary this link's resource pointer corresponds. This allows the
     * deletion from the dictionary in case this link gets destroyed.
     * @param value The pointer to the value this link stores.
     */
    HeavyResourceLink(HeavyResourceLink<TResource> *lessUsedResourceLink,
                      HeavyResourceLink<TResource> *moreUsedResourceLink,
                      const std::string &dictionaryKey,
                      TResource *value);
    ~HeavyResourceLink();

    /**
     * Changes the links linked to this one to the ones given as parameters. Both could be null, but not at the same
     * time, or this link would be lost in the memory.
     *
     * @param newLessUsedResourceLink The new link that contains the pointer to the resource that has been less recently
     * used than this one. May be null.
     * @param newMoreUsedResourceLink The new link that contains the pointer to the resource that has been more recently
     * used than this one.
     */
    void Move(HeavyResourceLink<TResource> *newLessUsedResourceLink,
              HeavyResourceLink<TResource> *newMoreUsedResourceLink);

    // Getters
    HeavyResourceLink<TResource> *GetLessUsedResourceLink() const;
    HeavyResourceLink<TResource> *GetMoreUsedResourceLink() const;
    const std::string &GetDictionaryKey() const;
    TResource *GetValue() const;

    // Setters
    void SetLessUsedResourceLink(HeavyResourceLink<TResource> *lessUsedResourceLink);
    void SetMoreUsedResourceLink(HeavyResourceLink<TResource> *moreUsedResourceLink);
    void SetDictionaryKey(const std::string &dictionaryKey);
    void SetValue(TResource *value);
};

template<typename TResource>
HeavyResourceLink<TResource>::HeavyResourceLink(HeavyResourceLink<TResource> *lessUsedResourceLink,
                                                HeavyResourceLink<TResource> *moreUsedResourceLink,
                                                const std::string &dictionaryKey, TResource *value) {
    LessUsedResourceLink = lessUsedResourceLink;
    MoreUsedResourceLink = moreUsedResourceLink;
    DictionaryKey = dictionaryKey;
    Value = value;

    if (LessUsedResourceLink != nullptr) {
        LessUsedResourceLink->SetMoreUsedResourceLink(this);
    }
    if (MoreUsedResourceLink != nullptr) {
        MoreUsedResourceLink->SetLessUsedResourceLink(this);
    }
}

template<typename TResource>
HeavyResourceLink<TResource>::~HeavyResourceLink() {
    // ⚠️ Do not delete the object pointed at by the link properties!
    delete Value;
}

template<typename TResource>
void HeavyResourceLink<TResource>::Move(HeavyResourceLink<TResource> *newLessUsedResourceLink,
                                        HeavyResourceLink<TResource> *newMoreUsedResourceLink) {
    if (newLessUsedResourceLink == nullptr && newMoreUsedResourceLink == nullptr) {
        throw BadInputException("Both links may not be null pointers!");
    }

    if (LessUsedResourceLink != nullptr) {
        LessUsedResourceLink->SetMoreUsedResourceLink(MoreUsedResourceLink);
    }
    if (MoreUsedResourceLink != nullptr) {
        MoreUsedResourceLink->SetLessUsedResourceLink(LessUsedResourceLink);
    }

    LessUsedResourceLink = newLessUsedResourceLink;
    MoreUsedResourceLink = newMoreUsedResourceLink;

    if (LessUsedResourceLink != nullptr) {
        LessUsedResourceLink->SetMoreUsedResourceLink(this);
    }
    if (MoreUsedResourceLink != nullptr) {
        MoreUsedResourceLink->SetLessUsedResourceLink(this);
    }
}

// Getters
template<typename TResource>
HeavyResourceLink<TResource> *HeavyResourceLink<TResource>::GetLessUsedResourceLink() const {
    return LessUsedResourceLink;
}

template<typename TResource>
HeavyResourceLink<TResource> *HeavyResourceLink<TResource>::GetMoreUsedResourceLink() const {
    return MoreUsedResourceLink;
}

template<typename TResource>
const std::string &HeavyResourceLink<TResource>::GetDictionaryKey() const {
    return DictionaryKey;
}

template<typename TResource>
TResource *HeavyResourceLink<TResource>::GetValue() const {
    return Value;
}

// Setters
template<typename TResource>
void HeavyResourceLink<TResource>::SetLessUsedResourceLink(HeavyResourceLink<TResource> *lessUsedResourceLink) {
    LessUsedResourceLink = lessUsedResourceLink;
}

template<typename TResource>
void HeavyResourceLink<TResource>::SetMoreUsedResourceLink(HeavyResourceLink<TResource> *moreUsedResourceLink) {
    MoreUsedResourceLink = moreUsedResourceLink;
}

template<typename TResource>
void HeavyResourceLink<TResource>::SetDictionaryKey(const std::string &dictionaryKey) {
    DictionaryKey = dictionaryKey;
}

template<typename TResource>
void HeavyResourceLink<TResource>::SetValue(TResource *value) {
    Value = value;
}


#endif //ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCELINK_H
