//
// Created by kklt on 5/23/25.
//

#ifndef RUDER_HPP
#define RUDER_HPP
#include "../GameObject.hpp"
#include "../../util/MultiLayerTexture.hpp"

class Ship;

class Ruder: public GameObject {
public:
    Ruder(Ship* ship, sf::Vector2f pos_offset);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;
    void setupTexture(int level);

private:
    Ship* ship;
    sf::Vector2f offset;
    sf::Sprite sprite;
    MultiLayerTexture texture;
};

#endif //RUDER_HPP
