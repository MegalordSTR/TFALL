#include "InputManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace MW
{
    InputManager::InputManager(): hasFocus(true){ LoadBindings(); }

    InputManager::~InputManager(){
        for (auto &itr : bindings){
            delete itr.second;
        }
    }

    bool InputManager::AddBinding(Binding *binding){
        if (bindings.find(binding->name) != bindings.end())
            return false;

        return bindings.emplace(binding->name, binding).second;
    }

    bool InputManager::RemoveBinding(std::string name){
        auto itr = bindings.find(name);
        if (itr == bindings.end()){ return false; }
        delete itr->second;
        bindings.erase(itr);
        return true;
    }

    void InputManager::SetCurrentState(StateType l_state){
        m_currentState = l_state;
    }

    void InputManager::SetFocus(const bool& focus){ hasFocus = focus; }

    void InputManager::HandleEvent(sf::Event& event){
        // Handling SFML events.
        for (auto &b_itr : bindings){
            Binding* bind = b_itr.second;
            for (auto &e_itr : bind->events){
                EventType sfmlEvent = (EventType)event.type;

                if (e_itr.first != sfmlEvent){ continue; }
                if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){
                    if (e_itr.second.code == event.key.code){
                        // Matching event/keystroke.
                        // Increase count.
                        if (bind->details.keyCode != -1){
                            bind->details.keyCode = e_itr.second.code;
                        }
                        ++(bind->c);
                        break;
                    }
                } else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp){
                    if (e_itr.second.code == event.mouseButton.button){
                        // Matching event/keystroke.
                        // Increase count.
                        bind->details.mouse.x = event.mouseButton.x;
                        bind->details.mouse.y = event.mouseButton.y;
                        if (bind->details.keyCode != -1){
                            bind->details.keyCode = e_itr.second.code;
                        }
                        ++(bind->c);
                    }
                } else {
                    // No need for additional checking.
                    if (sfmlEvent == EventType::MouseWheel){
                        bind->details.mouseWheelDelta = event.mouseWheel.delta;
                    } else if (sfmlEvent == EventType::WindowResized){
                        bind->details.size.x = event.size.width;
                        bind->details.size.y = event.size.height;
                    } else if (sfmlEvent == EventType::TextEntered){
                        bind->details.textEntered = event.text.unicode;
                    }
                    ++(bind->c);
                }
            }
        }
    }

    void InputManager::Update(){
        if (!hasFocus){ return; }
        for (auto &b_itr : bindings){
            Binding* bind = b_itr.second;
            for (auto &e_itr : bind->events){
                switch (e_itr.first){
                    case(EventType::Keyboard) :
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.code))){
                            if (bind->details.keyCode != -1){
                                bind->details.keyCode = e_itr.second.code;
                            }
                            ++(bind->c);
                        }
                        break;
                    case(EventType::Mouse) :
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.code))){
                            if (bind->details.keyCode != -1){
                                bind->details.keyCode = e_itr.second.code;
                            }
                            ++(bind->c);
                        }
                        break;
                    case(EventType::Joystick) :
                        // Up for expansion.
                        break;
                }
            }

            if (bind->events.size() == bind->c){
                auto stateCallbacks = callbacks.find(m_currentState);
                auto otherCallbacks = callbacks.find(StateType(0));

                if (stateCallbacks != callbacks.end()){
                    auto callItr = stateCallbacks->second.find(bind->name);
                    if (callItr != stateCallbacks->second.end()){
                        // Pass in information about events.
                        callItr->second(&bind->details);
                    }
                }

                if (otherCallbacks != callbacks.end()){
                    auto callItr = otherCallbacks->second.find(bind->name);
                    if (callItr != otherCallbacks->second.end()){
                        // Pass in information about events.
                        callItr->second(&bind->details);
                    }
                }
            }
            bind->c = 0;
            bind->details.Clear();
        }
    }

    void InputManager::LoadBindings(){
        std::string delimiter = ":";

        std::ifstream bindingsStream;
        bindingsStream.open("keys.cfg");
        if (!bindingsStream.is_open()){ std::cout << "! Failed loading keys.cfg." << std::endl; return; }
        std::string line;
        while (std::getline(bindingsStream, line)){
            std::stringstream keystream(line);
            std::string callbackName;
            keystream >> callbackName;
            auto bind = new Binding(callbackName);
            while (!keystream.eof()){
                std::string keyval;
                keystream >> keyval;
                if(keystream.fail()) {
                    keystream.clear();
                    break;
                }
                int start = 0;
                int end = keyval.find(delimiter);
                if (end == std::string::npos){ delete bind; bind = nullptr; break; }
                EventType type = EventType(stoi(keyval.substr(start, end - start)));
                int code = stoi(keyval.substr(end + delimiter.length(),
                                              keyval.find(delimiter, end + delimiter.length())));
                EventInfo eventInfo;
                eventInfo.code = code;

                bind->BindEvent(type, eventInfo);
            }

            if (!AddBinding(bind)){ delete bind; }
            bind = nullptr;
        }
        bindingsStream.close();
    }
}