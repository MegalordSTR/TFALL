//
// Created by Admin on 29.03.2022.
//

#ifndef TFALL_INPUTMANAGER_HPP
#define TFALL_INPUTMANAGER_HPP

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
    using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

    class InputManager{
    public:
        InputManager();
        ~InputManager();

        bool AddBinding(Binding *binding);
        bool RemoveBinding(std::string name);

        void SetFocus(const bool& focus);

        // Needs to be defined in the header!
        template<typename T>
        bool AddCallback(const std::string& name, std::function<void(T*, EventDetails*)> func, T* instance)
        {
            auto temp = std::bind(func, instance, std::placeholders::_1);
            return callbacks.emplace(name, temp).second;
        }

        void RemoveCallback(const std::string& name){
            callbacks.erase(name);
        }

        void HandleEvent(sf::Event& event);
        void Update();

        sf::Vector2i GetMousePos(sf::RenderWindow* window = nullptr){
            return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
        }
    private:
        void LoadBindings();

        Bindings bindings;
        Callbacks callbacks;
        bool hasFocus;
    };
}


#endif //TFALL_INPUTMANAGER_HPP
