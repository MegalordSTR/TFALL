//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_COMMANDQUEUE_H
#define TEST_COMMANDQUEUE_H


#include "Command.h"
#include <queue>

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


#endif //TEST_COMMANDQUEUE_H
