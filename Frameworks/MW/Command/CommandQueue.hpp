#pragma once

#include "Command.hpp"
#include <queue>

namespace MW
{
    class CommandQueue
    {
    public:
        CommandQueue();

    public:
        void push(const Command& command);
        Command pop();
        bool isEmpty() const;

    private:
        std::queue<Command> commands;
    };
}
