//
// Created by Admin on 16.03.2022.
//

#include "State.hpp"
#include "StateStack.hpp"

namespace MW
{
    State::State(StateStack& stack, Context ctx) :
            stack(&stack),
            ctx(ctx)
    {

    }

    State::~State(){}

    void State::requestStackPush(States::ID stateID)
    {
        stack->pushState(stateID);
    }

    void State::requestStackPop()
    {
        stack->popState();
    }

    void State::requestStateClear()
    {
        stack->clearStates();
    }

    State::Context State::getContext() const
    {
        return ctx;
    }

    State::Context::Context(
            sf::RenderWindow& window,
            InputManager& inputManager,
            FontHolder& fonts,
            TextureHolder& textures,
            SoundPlayer& soundPlayer
    ) :
            window(&window),
            inputManager(&inputManager),
            fonts(&fonts),
            textures(&textures),
            soundPlayer(&soundPlayer)
    {
    }
}

