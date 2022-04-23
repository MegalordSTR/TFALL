#include "CommandQueue.hpp"

namespace MW
{
    CommandQueue::CommandQueue()
    {
    }

    void CommandQueue::push(const Command& command)
    {
        commands.push(command);
    }

    Command CommandQueue::pop()
    {
        Command command = commands.front();
        commands.pop();
        return command;
    }

    bool CommandQueue::isEmpty() const
    {
        return commands.empty();
    }
}