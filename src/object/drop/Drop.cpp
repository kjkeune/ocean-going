//
// Created by kklt on 5/4/25.
//

#include "Drop.hpp"

#include "../../Game.hpp"
#include "../../handling/ObjectManager.hpp"

const float Drop::LABEL_FADEOUT_PER_SEC = 0.5f;

Drop::Drop(Island* island):
    sprite(ResourceManager::getInstance().getTexture(textures::DEFAULT)),
    sound(ResourceManager::getInstance().getSound(sounds::TREASURE_COLLECT))
{
    zIndex = 700;
    this->island = island;
    sound.setRelativeToListener(true);
    sound.setVolume(75.f);
}

void Drop::update(float delta) {
    if (collectLabel != nullptr) {
        float newOpacity = collectLabel->getOpacity() - delta * LABEL_FADEOUT_PER_SEC;
        if (newOpacity < 0) {
            collectLabel->destroy();
            collectLabel = nullptr;
        }
        else {
            collectLabel->setOpacity(newOpacity);
        }
    }
    else if (collected && sound.getStatus() != sf::Sound::Status::Playing) {
        destroy();
    }
}

void Drop::render(sf::RenderTarget &target) {
    if (!collected) {
        target.draw(sprite);
    }
}

sf::Transformable& Drop::getTrans() {
    return sprite;
}

ConvexPolygon Drop::getCollisionBounds() {
    auto bounds = rectToPoints(sprite.getGlobalBounds());
    return {bounds};
}

void Drop::onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) {
    if (collected) {
        return;
    }
    if (auto s = dynamic_cast<PlayerShip*>(other)) {
        collect(*s);
    }
}

void Drop::collect(PlayerShip& ship) {
    if (island != nullptr) {
        island->dropLoot();
        island->spawnEnemies();
    }
    if (collectLabel != nullptr) {
        collectLabel->zIndex = 100;
        collectLabel->getText().setFillColor(sf::Color::White);
        collectLabel->setRelativePosition(sprite.getPosition() - collectLabel->getSize() / 2.f);
        collectLabel->setActive(true);
    }
    sound.play();
    collected = true;
}