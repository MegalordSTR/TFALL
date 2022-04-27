#pragma once

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <SFML/System.hpp>

#include <stack>
#include <vector>
#include <memory>
#include <functional>

namespace MW
{
    class [[deprecated]] StateStack : sf::NonCopyable
    {
    public:

        enum class Action
        {
            Push,
            Pop,
            Clear,
        };

        explicit StateStack(State::Context context);
        ~StateStack();

        template <typename T>
        void registerState(States::ID stateID);

        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);

        void pushState(States::ID stateID);
        void popState();
        void clearStates();

        bool isEmpty() const;

    private:

        State::Ptr createState(States::ID stateID);
        void applyPendingChanges();

    private:

        struct PendingChange
        {
            explicit PendingChange(Action action, States::ID stateID = States::ID::None);

            Action action;
            States::ID stateID;
        };

    private:

        std::vector<State::Ptr> states;
        std::vector<PendingChange> pendingList;

        State::Context ctx;
        std::map<States::ID, std::function<State::Ptr()>> factories;
    };

    template<typename T>
    inline void StateStack::registerState(States::ID stateID)
    {
        factories[stateID] = [this]()
        {
            return State::Ptr(new T(*this, ctx));
        };
    }
}