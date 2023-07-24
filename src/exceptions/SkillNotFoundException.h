//
// Created by redneath on 17/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SKILLNOTFOUNDEXCEPTION_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SKILLNOTFOUNDEXCEPTION_H

#include <stdexcept>

class SkillNotFoundException: public std::runtime_error {
public:
    explicit SkillNotFoundException(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_SKILLNOTFOUNDEXCEPTION_H
