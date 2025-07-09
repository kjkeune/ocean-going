//
// Created by kklt on 4/26/25.
//

#ifndef SAIL_HPP
#define SAIL_HPP
#include "../GameObject.hpp"
#include "../../util/MultiLayerTexture.hpp"
#include "SFML/Graphics.hpp"

class Ship;

class Sail: public GameObject {
public:

    Sail(Ship* ship, sf::Vector2f pos_offset);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;
    void setSailState(int state);
    void setupTexture(bool enemy, int level);

private:
    Ship* ship;
    sf::Sprite sprite;
    sf::Vector2f offset;
    MultiLayerTexture texture;
};


#endif //SAIL_HPP
