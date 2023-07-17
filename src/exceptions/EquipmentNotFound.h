//
// Created by redneath on 17/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENTNOTFOUND7_H
#define ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENTNOTFOUND7_H

#include <stdexcept>

class EquipmentNotFound: public std::runtime_error {
public:
    explicit EquipmentNotFound(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENTNOTFOUND7_H
