//
// Created by redneath on 26/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DATABASEUNAVAILABLEEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DATABASEUNAVAILABLEEXCEPTION_H

#include <stdexcept>

class DatabaseUnavailableException: public std::domain_error {
public:
    explicit DatabaseUnavailableException(const std::string &message): domain_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_DATABASEUNAVAILABLEEXCEPTION_H
