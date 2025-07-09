//
// Created by kklt on 4/26/25.
//

#ifndef CANNON_HPP
#define CANNON_HPP
#include "../GameObject.hpp"
#include "../../util/InterpolateAnimation.hpp"
#include "../../util/MultiLayerTexture.hpp"
#include "SFML/Graphics.hpp"

class Ship;

class Cannon: public GameObject {
public:
    float velShot = 275.f;

    Cannon(Ship* ship, sf::Vector2f pos_offset, bool left);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;

    void fire();
    bool isLoaded();
    void setupTexture(int lvlStrength, int lvlRange, int lvlReload);

private:
    Ship* ship;
    sf::Sprite sprite;
    InterpolateAnimation animation;
    sf::Vector2f offset;
    MultiLayerTexture texture;
    sf::Sound sound;
    bool left;
    float loadingState = 0.f;
};

#endif //CANNON_HPP
