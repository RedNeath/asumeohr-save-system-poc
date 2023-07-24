//
// Created by redneath on 24/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENTNOTFOUNDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENTNOTFOUNDEXCEPTION_H

#include <stdexcept>

class EquipmentNotFoundException: public std::runtime_error {
public:
    explicit EquipmentNotFoundException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENTNOTFOUNDEXCEPTION_H
