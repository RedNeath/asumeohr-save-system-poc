//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_NOMATCHINGSIGNATURE_H
#define ASUMEOHR_SAVE_SYSTEM_POC_NOMATCHINGSIGNATURE_H

#include <stdexcept>

class NoMatchingSignature: public std::runtime_error {
public:
    explicit NoMatchingSignature(const std::string &message): runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_NOMATCHINGSIGNATURE_H
