//
// Created by kklt on 6/11/25.
//

#ifndef ISLANDDECORATION_HPP
#define ISLANDDECORATION_HPP
#include "../GameObject.hpp"

class IslandDecoration: public GameObject {
public:
    static const int NUM_TYPES;

    IslandDecoration(int type);

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;

private:
    sf::Sprite sprite;

};

#endif //ISLANDDECORATION_HPP
