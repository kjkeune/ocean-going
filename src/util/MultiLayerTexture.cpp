//
// Created by kklt on 6/2/25.
//

#include "MultiLayerTexture.hpp"

#include "../handling/ResourceManager.hpp"

void MultiLayerTexture::setup(const std::string& base, const std::vector<std::string>& layers) {
    auto& texBase = ResourceManager::getInstance().getTexture(base);
    auto baseSize = texBase.getSize();
    if (!resize(baseSize)) {
        throw std::runtime_error("Failed to resize");
    }
    clear(sf::Color::Transparent);
    draw(sf::Sprite(texBase));
    for (auto& layer : layers) {
        auto& texLayer = ResourceManager::getInstance().getTexture(layer);
        draw(sf::Sprite(texLayer));
    }
    display();
}
