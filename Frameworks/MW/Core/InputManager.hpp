#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

namespace MW
{
    enum class EventType{
        KeyDown = sf::Event::KeyPressed,
        KeyUp = sf::Event::KeyReleased,
        MButtonDown = sf::Event::MouseButtonPressed,
        MButtonUp = sf::Event::MouseButtonReleased,
        MouseWheel = sf::Event::MouseWheelMoved,
        WindowResized = sf::Event::Resized,
        GainedFocus = sf::Event::GainedFocus,
        LostFocus = sf::Event::LostFocus,
        MouseEntered = sf::Event::MouseEntered,
        MouseLeft = sf::Event::MouseLeft,
        Closed = sf::Event::Closed,
        TextEntered = sf::Event::TextEntered,
        Keyboard = sf::Event::Count + 1, Mouse, Joystick
    };

    struct EventInfo{
        EventInfo(){ code = 0; }
        EventInfo(int event){ code = event; }
        union{
            int code;
        };
    };

    struct EventDetails{
        EventDetails(const std::string& l_bindName)
                : name(l_bindName){
            Clear();
        }
        std::string name;

        sf::Vector2i size;
        sf::Uint32 textEntered;
        sf::Vector2i mouse;
        int mouseWheelDelta;
        int keyCode; // Single key code.

        void Clear(){
            size = sf::Vector2i(0, 0);
            textEntered = 0;
            mouse = sf::Vector2i(0, 0);
            mouseWheelDelta = 0;
            keyCode = -1;
        }
    };

    using Events = std::vector<std::pair<EventType, EventInfo>>;

    struct Binding{
        Binding(const std::string& name): name(name), details(name), c(0){}
        void BindEvent(EventType type, EventInfo info = EventInfo()){
            events.emplace_back(type, info);
        }

        Events events;
        std::string name;
        int c; // Count of events that are "happening".

        EventDetails details;
    };

    using Bindings = std::unordered_map<std::string, Binding*>;
    // Callback container.
    using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
    // State callback container.
    enum class StateType;
    using Callbacks = std::unordered_map<StateType, CallbackContainer>;

    class InputManager{
    public:
        InputManager();
        ~InputManager();

        bool AddBinding(Binding *binding);
        bool RemoveBinding(std::string name);

        void SetCurrentState(StateType l_state);
        void SetFocus(const bool& focus);

        // Needs to be defined in the header!
        template<typename T>
        bool AddCallback(StateType l_state, const std::string& name, std::function<void(T*, EventDetails*)> func, T* instance)
        {
            auto itr = callbacks.emplace(l_state, CallbackContainer()).first;
            auto temp = std::bind(func, instance, std::placeholders::_1);
            return itr->second.emplace(name, temp).second;
        }

        bool RemoveCallback(StateType l_state, const std::string& name){
            auto itr = callbacks.find(l_state);
            if (itr == callbacks.end()){ return false; }
            auto itr2 = itr->second.find(name);
            if (itr2 == itr->second.end()){ return false; }
            itr->second.erase(name);
            return true;
        }

        void HandleEvent(sf::Event& event);
        void Update();

        sf::Vector2i GetMousePos(sf::RenderWindow* window = nullptr){
            return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
        }
    private:
        void LoadBindings();

        StateType m_currentState;
        Bindings bindings;
        Callbacks callbacks;

        bool hasFocus;
    };
}
