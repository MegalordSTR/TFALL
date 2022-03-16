//
// Created by Admin on 16.03.2022.
//

#include "Command.h"

Command::Command(Action fn, Game::CategoryType category)
{
    this->action = fn;
    this->category = category;
}
