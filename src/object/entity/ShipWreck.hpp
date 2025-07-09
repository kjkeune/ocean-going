//
// Created by kklt on 5/6/25.
//

#ifndef SHIPWRECK_HPP
#define SHIPWRECK_HPP
#include "../GameObject.hpp"
#include "../../util/Animation.hpp"

class ShipWreck: public GameObject {
public:
    static const float DROP_RADIUS_MIN;
    static const float DROP_RADIUS_MAX;
    static const float HEALING_DROP_PROB;
    static const float PARTS_DROP_PROB;

    ShipWreck(sf::Vector2f pos, sf::Angle ori, int hullType);
    void update(float delta) override;
    void render(sf::RenderTarget& renderTarget) override;
    sf::Transformable& getTrans() override;

    void dropLoot();

private:
    sf::Sprite sprite;
    Animation animation;
    sf::Sound sound;
    int hullType;

};

#endif //SHIPWRECK_HPP
