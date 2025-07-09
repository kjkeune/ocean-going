//
// Created by kklt on 5/5/25.
//

#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "../GameObject.hpp"
#include "../../util/InterpolateAnimation.hpp"

enum class EffectType {CANNON_BALL_MISS, CANNON_BALL_HIT};

class Effect: public GameObject{
public:
    EffectType type;

    Effect(EffectType type);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;

private:
    sf::Sprite sprite;
    InterpolateAnimation animation;
    sf::Sound sound;
};

#endif //EFFECT_HPP
