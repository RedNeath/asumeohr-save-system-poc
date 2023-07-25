//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SAVENOTFOUNDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SAVENOTFOUNDEXCEPTION_H

#include <stdexcept>

class SaveNotFoundException: public std::runtime_error {
public:
    explicit SaveNotFoundException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_SAVENOTFOUNDEXCEPTION_H
