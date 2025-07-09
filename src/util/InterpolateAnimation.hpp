//
// Created by kklt on 5/19/25.
//

#ifndef INTERPOLATEANIMATION_HPP
#define INTERPOLATEANIMATION_HPP
#include <vector>

#include "Animation.hpp"
#include "SFML/Graphics/Shader.hpp"

class InterpolateAnimation: public Animation {
public:
    InterpolateAnimation(sf::Sprite &sprite, float duration = 1.f, bool repeated = false, bool startLast = false);
    sf::Shader& getShader();

    void update(float delta) override;
    void start() override;
    void stop() override;

private:
    sf::Shader& shader;
    int lastFrame = 0;
    int nextFrame = 1;
    float alpha = 0.f;
    std::vector<sf::Texture> frames;
    const sf::Texture* currentTex;

    void setupTexFrames();
};

#endif //INTERPOLATEANIMATION_HPP
