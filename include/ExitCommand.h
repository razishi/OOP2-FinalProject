#pragma once

#include "Command.h"
#include <cstdlib>

class ExitCommand : public Command {
public:
    void execute() override {
        std::exit(0);
    }
};


