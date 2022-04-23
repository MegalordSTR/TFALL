#include "Command.hpp"
namespace MW
{
    Command::Command(Action fn, CategoryType category)
    {
        this->action = fn;
        this->category = category;
    }
}

