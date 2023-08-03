//
// Created by redneath on 26/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SQLEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SQLEXCEPTION_H

#include <stdexcept>

class SQLException: public std::runtime_error {
public:
    explicit SQLException(const std::string &message): runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_SQLEXCEPTION_H
