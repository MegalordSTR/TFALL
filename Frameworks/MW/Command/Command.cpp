//
// Created by Admin on 16.03.2022.
//

#include "Command.hpp"
namespace MW
{
    Command::Command(Action fn, CategoryType category)
    {
        this->action = fn;
        this->category = category;
    }
}

