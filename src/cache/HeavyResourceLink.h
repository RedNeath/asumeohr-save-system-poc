//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCELINK_H
#define ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCELINK_H

#include <string>

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


#endif //ASUMEOHR_SAVE_SYSTEM_POC_HEAVYRESOURCELINK_H
