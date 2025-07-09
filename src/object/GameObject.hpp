#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../handling/ResourceManager.hpp"
#include "../constants/Paths.hpp"

class GameObject {
public:
    int zIndex = 0;

    GameObject() = default;
    bool isActive();

    virtual ~GameObject() = default;
    virtual void render(sf::RenderTarget& target) = 0;
    virtual void update(float delta) = 0;
    virtual sf::Transformable& getTrans() = 0;
    virtual void setActive(bool state);
    virtual void destroy();

private:
    bool active = false;
};

#endif //GAMEOBJECT_H
