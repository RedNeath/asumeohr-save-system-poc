//
// Created by redneath on 21/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_COMMANDNOTFOUNDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_COMMANDNOTFOUNDEXCEPTION_H

#include <stdexcept>

class CommandNotFoundException: public std::runtime_error {
public:
    explicit CommandNotFoundException(const std::string &message): runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_COMMANDNOTFOUNDEXCEPTION_H
