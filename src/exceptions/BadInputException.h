//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_BADINPUTEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_BADINPUTEXCEPTION_H


#include <stdexcept>

class BadInputException: public std::runtime_error {
public:
    explicit BadInputException(const std::string &message) : runtime_error(message) {}
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_BADINPUTEXCEPTION_H
