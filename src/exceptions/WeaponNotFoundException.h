//
// Created by redneath on 24/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_WEAPONNOTFOUNDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_WEAPONNOTFOUNDEXCEPTION_H

#include <stdexcept>

class WeaponNotFoundException: public std::runtime_error {
public:
    explicit WeaponNotFoundException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_WEAPONNOTFOUNDEXCEPTION_H
