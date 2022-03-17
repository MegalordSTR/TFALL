//
// Created by Admin on 16.03.2022.
//

#include "StateStack.h"

#include <cassert>

namespace Engine
{
    StateStack::StateStack(State::Context ctx) :
            states(),
            pendingList(),
            ctx(ctx),
            factories()
    {

    }

    StateStack::~StateStack(){}

    void StateStack::update(sf::Time dt)
    {
        for (auto stateItr = states.rbegin(); stateItr != states.rend(); ++stateItr)
        {
            if (!(*stateItr)->update(dt))
                break;
        }

        applyPendingChanges();
    }

    void StateStack::draw()
    {
        for (auto& state : states)
        {
            state->draw();
        }
    }

    void StateStack::handleEvent(const sf::Event& event)
    {
        for (auto stateItr = states.rbegin(); stateItr != states.rend(); ++stateItr)
        {
            if (!(*stateItr)->handleEvent(event))
                break;
        }

        applyPendingChanges();
    }

    void StateStack::pushState(States::ID stateID)
    {
        pendingList.push_back(PendingChange(Action::Push, stateID));
    }

    void StateStack::popState()
    {
        pendingList.push_back(PendingChange(Action::Pop));
    }

    void StateStack::clearStates()
    {
        pendingList.push_back(PendingChange(Action::Clear));
    }

    bool StateStack::isEmpty() const
    {
        return states.empty();
    }

    State::Ptr StateStack::createState(States::ID stateID)
    {
        auto found = factories.find(stateID);
        assert(found != factories.end());

        return found->second();
    }

    void StateStack::applyPendingChanges()
    {
        for (PendingChange change : pendingList)
        {
            switch (change.action)
            {
                case Action::Push:
                    states.push_back(createState(change.stateID));
                    break;
                case Action::Pop:
                    states.pop_back();
                    break;
                case Action::Clear:
                    states.clear();
                    break;
                default:
                    break;
            }
        }

        pendingList.clear();
    }

    StateStack::PendingChange::PendingChange(Action action, States::ID stateID) :
            action(action),
            stateID(stateID)
    {
    }
}

