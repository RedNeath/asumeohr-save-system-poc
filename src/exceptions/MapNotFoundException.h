//
// Created by redneath on 25/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_MAPNOTFOUNDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_MAPNOTFOUNDEXCEPTION_H

#include <stdexcept>

class MapNotFoundException: public std::runtime_error {
public:
    explicit MapNotFoundException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_MAPNOTFOUNDEXCEPTION_H
