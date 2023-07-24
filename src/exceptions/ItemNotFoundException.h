//
// Created by redneath on 17/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_ITEMNOTFOUND7_H
#define ASUMEOHR_SAVE_SYSTEM_POC_ITEMNOTFOUND7_H

#include <stdexcept>

class ItemNotFoundException: public std::runtime_error {
public:
    explicit ItemNotFoundException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_ITEMNOTFOUND7_H
