//
// Created by Admin on 16.03.2022.
//

#include "CommandQueue.h"

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
