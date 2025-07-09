//
// Created by kklt on 5/4/25.
//

#include "Animation.hpp"

Animation::Animation(sf::Sprite &sprite, float duration, bool repeated, bool startLast):
    sprite(sprite)
{
    this->duration = duration;
    this->repeated = repeated;
    this->startLast = startLast;
    auto texSize = static_cast<sf::Vector2i>(sprite.getTexture().getSize());
    if (startLast) {
        sprite.setTextureRect({{(texSize.x / texSize.y - 1) * texSize.y,0},{texSize.y, texSize.y}});
    }
    else {
        sprite.setTextureRect({{0,0},{texSize.y, texSize.y}});
    }
}

void Animation::update(float delta) {
    if (!running) {
        return;
    }
    currentTime += delta;
    float state = currentTime / duration;
    if (!repeated && state >= 1.f) {
        stop();
        return;
    }
    auto texSize = static_cast<sf::Vector2i>(sprite.getTexture().getSize());
    int frames = texSize.x / texSize.y;
    auto size = sf::Vector2i{texSize.y, texSize.y};
    auto pos = sf::Vector2i{static_cast<int>(state * frames) % frames * size.y, 0};
    sprite.setTextureRect({pos, size});
}

void Animation::start() {
    running = true;
    auto texSize = static_cast<sf::Vector2i>(sprite.getTexture().getSize());
    sprite.setTextureRect({{0,0},{texSize.y, texSize.y}});
}

void Animation::stop() {
    running = false;
    currentTime = 0.f;
}

bool Animation::isRunning() {
    return running;
}

void Animation::setDuration(float duration) {
    this->duration = duration;
}

void Animation::setRepeated(bool repeated) {
    this->repeated = repeated;
}