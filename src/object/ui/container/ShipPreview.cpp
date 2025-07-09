//
// Created by kklt on 5/25/25.
//

#include "ShipPreview.hpp"

#include "../Label.hpp"
#include "../../../handling/LevelManager.hpp"

//TODO Hovering to fast makes incorrect preview
ShipPreview::ShipPreview(sf::Vector2f size): Container(size, sf::Color::Transparent) {
    float porYPrev = 0.4f;
    shipBackground.setSize({size.x, size.y * porYPrev});
    auto &tex = ResourceManager::getInstance().getTexture(textures::SHIP_PREVIEW);
    shipBackground.setTexture(&tex);
    shipBackground.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(tex.getSize())));
    current = setupShip(LevelManager::getInstance().getPlayerConfig());
    preview = setupShip(LevelManager::getInstance().getPlayerConfig());
    initStats({
        "Health",
        "Damage",
        "Range",
        "Reloading Time",
        "Velocity",
        "Manoeuvrability"},
    {
        maxed->maxHealth,
        maxed->canDamage,
        maxed->canRange,
        1.f / maxed->canReloadTime / 4.f,
        maxed->determineVelocity(Ship::MAX_SAIL_STATE) * 1.4f,
        maxed->turnPerSec * 1.33f
    },
    {
        [](PreviewShip* ship) {
            return ship->maxHealth;
        },
        [](PreviewShip* ship) {
            return ship->canDamage;
        },
        [](PreviewShip* ship) {
            return ship->canRange;
        },
        [](PreviewShip* ship) {
            return 1.f / ship->canReloadTime / 4.f;
        },
        [](PreviewShip* ship) {
            return ship->determineVelocity(Ship::MAX_SAIL_STATE);
        },
        [](PreviewShip* ship) {
            return ship->turnPerSec;
        },
    });
}

void ShipPreview::initStats(const std::vector<std::string> &names,const std::vector<float>& maxVals, const std::vector<std::function<float(PreviewShip*)>>& getters) {
    float mar = 12.f;
    float marFont = 10.f;
    float fontSize = 28.f;
    float barHeight = 20.f;
    float offsetX = 2 * mar;
    float offsetY = shipBackground.getSize().y + mar;
    float blockHeight = fontSize + barHeight + mar + marFont;
    for (int i = 0; i < names.size(); i++) {
        auto label = new Label(names[i], fonts::TREAMD, fontSize);
        label->setRelativePosition({ offsetX, offsetY + i * blockHeight});
        label->getText().setStyle(sf::Text::Bold);
        addElement(label);
        auto attBar = new AttributeBar({getSize().x - 3 * offsetX, barHeight}, maxVals[i], getters[i]);
        attBar->setRelativePosition({ offsetX, offsetY + fontSize + marFont + i * blockHeight});
        attributeBars.push_back(attBar);
        addElement(attBar);
    }
}

void ShipPreview::startPreview(ShipConfiguration& config) {
    if (inPreview) {
        return;
    }
    preview->destroy();
    preview = setupShip(config);
    preview->setActive(true);
    current->disabled = true;
    inPreview = true;
    for (auto attBar : attributeBars) {
        attBar->startPreview(preview);
    }
}

void ShipPreview::endPreview() {
    if (!inPreview) {
        return;
    }
    preview->disabled = true;
    current->disabled = false;
    inPreview = false;
    for (auto attBar : attributeBars) {
        attBar->endPreview();
    }
}

void ShipPreview::updateCurrent() {
    current->destroy();
    current = setupShip(LevelManager::getInstance().getPlayerConfig());
    current->setActive(true);
    if (inPreview) {
        current->disabled = true;
    }
    for (auto attBar : attributeBars) {
        attBar->updateCurrent(current);
    }
}

void ShipPreview::update(float delta) {

}

void ShipPreview::render(sf::RenderTarget& target) {
    Container::render(target);
    target.draw(shipBackground);
}

void ShipPreview::setActive(bool state) {
    Container::setActive(state);
    current->setActive(state);
    preview->setActive(state);
    if (state) {
        inPreview = false;
        updateCurrent();
        preview->disabled = true;
    }
}

void ShipPreview::destroy() {
    Container::destroy();
    preview->destroy();
    current->destroy();
    maxed->destroy();
}

void ShipPreview::updatePosition(sf::Vector2f offset) {
    shipBackground.move(offset);
    preview->getTrans().move(offset);
    current->getTrans().move(offset);
    Container::updatePosition(offset);
}

PreviewShip* ShipPreview::setupShip(ShipConfiguration& config) {
    auto ship = new PreviewShip(config);
    auto& shipTrans = ship->getTrans();
    shipTrans.setPosition(shipBackground.getPosition() + shipBackground.getSize() / 2.f);
    shipTrans.setScale(sf::Vector2f(1.85f, 1.85f));
    return ship;
}

void ShipPreview::boughtAnimation(PreviewShip *ship) {
    for (int i = 0; i < ship->numCannons; i++) {
        ship->fireCannons();
    }
}

// ------------------------- Preview Ship -----------------------------

PreviewShip::PreviewShip(ShipConfiguration& config): Ship(config) {
    zIndex = -100;
    for (auto cannon : cannons) {
        cannon->zIndex = zIndex - 10;
    }
    for (auto sail : sails) {
        sail->zIndex = zIndex - 20;
        sail->setSailState(1);
    }
    ruder->zIndex = zIndex + 10;
}

void PreviewShip::update(float delta) {

}

void PreviewShip::sink() {

}

void PreviewShip::onCollision(Collidable *other, std::vector<sf::Vector2f> &contacts) {

}
