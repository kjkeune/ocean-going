//
// Created by kklt on 6/11/25.
//

#include "IslandDecoration.hpp"
#include "../../util/Text.hpp"

const int IslandDecoration::NUM_TYPES = 5;

IslandDecoration::IslandDecoration(int type):
    sprite(ResourceManager::getInstance().getTexture(replaceTag(textures::ISLAND_DECO, "type", std::to_string(type))))
{
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    if (type <= 2) {
        zIndex = 970;
    }
    else {
        zIndex = 975;
    }
}

void IslandDecoration::update(float delta) {

}

void IslandDecoration::render(sf::RenderTarget &target) {
    target.draw(sprite);
}

sf::Transformable &IslandDecoration::getTrans() {
    return sprite;
}
