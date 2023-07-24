//
// Created by redneath on 24/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DIRECTIONNOTFOUNDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DIRECTIONNOTFOUNDEXCEPTION_H

#include <stdexcept>

class DirectionNotFoundException: public std::runtime_error {
public:
    explicit DirectionNotFoundException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_DIRECTIONNOTFOUNDEXCEPTION_H
