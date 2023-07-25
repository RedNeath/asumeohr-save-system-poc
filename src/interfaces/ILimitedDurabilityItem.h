//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_ILIMITEDDURABILITYITEM_H
#define ASUMEOHR_SAVE_SYSTEM_POC_ILIMITEDDURABILITYITEM_H


#include "IUsableItem.h"

class ILimitedDurabilityItem: public IUsableItem {
protected:
    int DurabilityLeft = 0;

public:
    /**
     * The function to call to use the object! NEVER CALL @c Use() alone for a @c ILimitedDurabilityItem,
     * otherwise the durability won't be decounted!
     *
     * @return @c true if the item is destroyed after the use; @c false otherwise.
     */
    bool makeUse() { // Exceptionally defined in-line, just to make sure the removal of durability is made
        if (Use()) {
            // We reduce the durability only if the use was a success
            DurabilityLeft--;
        }

        return DurabilityLeft == 0;
    }

    virtual int GetDurabilityLeft() const = 0;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_ILIMITEDDURABILITYITEM_H
