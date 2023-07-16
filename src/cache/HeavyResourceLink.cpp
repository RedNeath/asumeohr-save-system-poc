//
// Created by redneath on 16/07/23.
//

#include "HeavyResourceLink.h"
#include "../exceptions/BadInputException.h"

using namespace std;

template<typename TResource>
HeavyResourceLink<TResource>::HeavyResourceLink(HeavyResourceLink<TResource> *lessUsedResourceLink,
                                                HeavyResourceLink<TResource> *moreUsedResourceLink,
                                                const string &dictionaryKey, TResource *value) {
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
void HeavyResourceLink<TResource>::Move(HeavyResourceLink<TResource> *newLessUsedResourceLink,
                                        HeavyResourceLink<TResource> *newMoreUsedResourceLink) {
    if (newLessUsedResourceLink == nullptr && newMoreUsedResourceLink == nullptr) {
        throw BadInputException("Both links may not be null pointers!");
    }

    LessUsedResourceLink->SetMoreUsedResourceLink(MoreUsedResourceLink);
    MoreUsedResourceLink->SetLessUsedResourceLink(LessUsedResourceLink);

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
const string &HeavyResourceLink<TResource>::GetDictionaryKey() const {
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
