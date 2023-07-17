//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SAVENOTFOUND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SAVENOTFOUND_H

#include <stdexcept>

class SaveNotFound: public std::runtime_error {
public:
    explicit SaveNotFound(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_SAVENOTFOUND_H
