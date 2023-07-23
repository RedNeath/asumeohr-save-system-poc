//
// Created by redneath on 23/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_IMPOSSIBLEACTIONEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_IMPOSSIBLEACTIONEXCEPTION_H

#include <stdexcept>

class ImpossibleActionException: public std::runtime_error {
public:
    explicit ImpossibleActionException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_IMPOSSIBLEACTIONEXCEPTION_H
