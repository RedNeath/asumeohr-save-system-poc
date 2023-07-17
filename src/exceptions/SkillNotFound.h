//
// Created by redneath on 17/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SKILLNOTFOUND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SKILLNOTFOUND_H

#include <stdexcept>

class SkillNotFound: public std::runtime_error {
public:
    explicit SkillNotFound(const std::string &message) : runtime_error(message) {}
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_SKILLNOTFOUND_H
