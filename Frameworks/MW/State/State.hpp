#pragma once

#include "StateIdentifiers.hpp"
#include <MW/Resources/ResourceIdentifiers.hpp>
#include <MW/Resources/SoundPlayer.hpp>

#include <SFML/Graphics.hpp>

#include <memory>



namespace MW
{
    class StateStack;
    class InputManager;


    class [[deprecated]] State
    {
    public:
        typedef std::unique_ptr<State> Ptr;

        struct [[deprecated]] Context
        {
            Context(
                    sf::RenderWindow& window,
                    InputManager& inputManager,
                    FontHolder& fonts,
                    TextureHolder& textures,
                    SoundPlayer& soundPlayer
            );

            InputManager* inputManager;
            sf::RenderWindow* window;
            FontHolder* fonts;
            TextureHolder* textures;
            SoundPlayer* soundPlayer;
        };

    public:

        State(StateStack& stack, Context ctx);
        virtual ~State();

        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;

    protected:
        void requestStackPush(States::ID stateID);
        void requestStackPop();
        void requestStateClear();

        Context getContext() const;

    private:
        StateStack* stack;
        Context ctx;
    };
}
