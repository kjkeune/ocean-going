//
// Created by kklt on 5/19/25.
//

#include "InterpolateAnimation.hpp"

#include <iostream>

#include "../constants/Paths.hpp"
#include "../handling/ResourceManager.hpp"

InterpolateAnimation::InterpolateAnimation(sf::Sprite &sprite, float duration, bool repeated, bool startLast):
    Animation(sprite, duration, repeated, startLast),
    shader(ResourceManager::getInstance().getShader(shaders::BLEND))
{
    setupTexFrames();
}

void InterpolateAnimation::setupTexFrames() {
    frames.clear();
    // Get texture and attributes
    auto& texFull = sprite.getTexture();
    currentTex = &texFull;
    auto texSize = static_cast<sf::Vector2i>(texFull.getSize());
    // crop out frames
    sf::Image imgFull = texFull.copyToImage();
    auto size = sf::Vector2i{texSize.y, texSize.y};
    int numFrames = texSize.x / texSize.y;
    for (int i = 0; i < numFrames; i++) {
        auto pos = sf::Vector2i{i * size.y, 0};
        sf::Image frame(static_cast<sf::Vector2u>(size));
        if (!frame.copy(imgFull, {0,0}, sf::IntRect{pos, size})) {
            throw std::runtime_error("Copying image of animation failed!");
        }
        sf::Texture texFrame(frame);
        texFrame.setRepeated(true);
        frames.emplace_back(std::move(texFrame));
    }
}


void InterpolateAnimation::update(float delta) {
    if (!running) {
        return;
    }
    currentTime += delta;
    float state = currentTime / duration;
    if (!repeated && state >= 1.f) {
        stop();
        return;
    }
    int numFrames = frames.size();
    float currentFrame = state * numFrames;
    lastFrame = static_cast<int>(currentFrame);
    alpha = currentFrame - lastFrame;
    lastFrame %= numFrames;
    nextFrame = (lastFrame + 1) % numFrames;
}

void InterpolateAnimation::start() {
    running = true;
    if (currentTex != &sprite.getTexture()) {
        setupTexFrames();
    }
    if (startLast) {
        sprite.setTexture(frames[frames.size() - 1]);
    }
    else {
        sprite.setTexture(frames[0]);
    }
}

void InterpolateAnimation::stop() {
    running = false;
    currentTime = 0.f;
    sprite.setTexture(*currentTex);
    auto texSize = static_cast<sf::Vector2i>(sprite.getTexture().getSize());
    if (startLast) {
        sprite.setTextureRect({{(texSize.x / texSize.y - 1) * texSize.y,0},{texSize.y, texSize.y}});
    }
    else {
        sprite.setTextureRect({{0,0},{texSize.y, texSize.y}});
    }
}

sf::Shader &InterpolateAnimation::getShader() {
    int i = lastFrame;
    int j = nextFrame;
    if (startLast) {
        i = (i - 1) % frames.size();
        j = (j - 1) % frames.size();
    }
    shader.setUniform("tex1", frames[i]);
    shader.setUniform("tex2", frames[j]);
    shader.setUniform("alpha", alpha);
    return shader;
}
