//
// Created by kklt on 5/13/25.
//

#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP
#include <functional>
#include <unordered_set>

#include "../object/ui/button/Button.hpp"

class EventHandler {
public:
    static EventHandler& getInstance();

    void handleUserInput(sf::Window& window);
    void add(Button* observer);
    void remove(Button* observer);

private:
    std::unordered_set<Button*> buttonObservers;

    void notifyButtons();

    static EventHandler* instance;
    EventHandler() = default;

};

#endif //EVENTHANDLER_HPP
