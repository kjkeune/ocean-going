//
// Created by kklt on 5/4/25.
//

#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Animation {
public:
    Animation(sf::Sprite& sprite, float duration = 1.f, bool repeated = false, bool startLast = false);
    virtual ~Animation() = default;
    virtual void update(float delta);
    virtual void start();
    virtual void stop();
    bool isRunning();
    void setDuration(float duration);
    void setRepeated(bool repeated);

protected:
    sf::Sprite& sprite;
    bool running = false;
    float currentTime = 0.f;
    bool repeated;
    float duration;
    bool startLast;
};

#endif //ANIMATION_HPP
