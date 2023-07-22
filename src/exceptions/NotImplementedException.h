//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_NOTIMPLEMENTEDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_NOTIMPLEMENTEDEXCEPTION_H

#include <stdexcept>

class NotImplementedException: public std::runtime_error {
public:
    explicit NotImplementedException(const std::string &message): runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_NOTIMPLEMENTEDEXCEPTION_H
