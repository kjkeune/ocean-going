//
// Created by kklt on 5/28/25.
//

#include "Minimap.hpp"

#include "../../constants/Colors.hpp"
#include "../../handling/ObjectManager.hpp"
#include "../../util/Text.hpp"

const float Minimap::BORDER_PORTION = 32.f / 400.f;

Minimap::Minimap(sf::Vector2f size):
    staticTexture(static_cast<sf::Vector2u>(size * (1 - BORDER_PORTION))),
    dynamicTexture(static_cast<sf::Vector2u>(size * (1 - BORDER_PORTION))),
    mapSprite(staticTexture.getTexture())
{
    border.setSize(size);
    auto& tex = ResourceManager::getInstance().getTexture(textures::MINIMAP);
    border.setTexture(&tex);
    border.setTextureRect({{0,0}, static_cast<sf::Vector2i>(tex.getSize())});
    mapSprite.setPosition(size * BORDER_PORTION / 2.f);
    staticTexture.setSmooth(true);
    dynamicTexture.setSmooth(true);
}

void Minimap::update(float delta) {
    drawDynamic();
}

void Minimap::render(sf::RenderTarget &target) {
    mapSprite.setTexture(staticTexture.getTexture());
    target.draw(mapSprite);
    mapSprite.setTexture(dynamicTexture.getTexture());
    target.draw(mapSprite);
    target.draw(border);
}

void Minimap::drawStatic() {
    auto& resManager = ResourceManager::getInstance();
    auto& world = objManager.getWorld();
    auto mapSize = getMapSize();
    // draw background
    staticTexture.clear(colors::MAP_WHITE_TRANS);
    // draw grid
    float i = World::TILE_SIZE * 2;
    while (i < worldSize.x) {
        sf::RectangleShape lineX;
        lineX.setSize({mapSize.x, 1});
        lineX.setPosition(worldToMinimap({0, i}));
        lineX.setFillColor(colors::MINIMAP_GRID_GREY);
        staticTexture.draw(lineX);
        sf::RectangleShape lineY;
        lineY.setSize({1, mapSize.y});
        lineY.setPosition(worldToMinimap({i, 0}));
        lineY.setFillColor(colors::MINIMAP_GRID_GREY);
        staticTexture.draw(lineY);
        i += World::TILE_SIZE * 2;
    }
    // draw islands and vortex
    sf::CircleShape iconVortex(6);
    iconVortex.setFillColor(colors::MINIMAP_GRID_GREY);
    iconVortex.setOrigin(iconVortex.getLocalBounds().getCenter());
    iconVortex.setPosition(worldToMinimap(world.getVortexPosition()));
    staticTexture.draw(iconVortex);
    for (auto island : world.getIslands()) {
        int type = island->getType();
        auto& tex = resManager.getTexture(replaceTag(textures::ISLAND, "type", std::to_string(type)));
        auto texSize = static_cast<sf::Vector2i>(tex.getSize());
        sf::RectangleShape islandRect;
        islandRect.setTexture(&tex);
        islandRect.setTextureRect({{0,0},texSize});
        islandRect.setFillColor(colors::MINIMAP_ISLAND_GREY);
        islandRect.setSize(worldToMinimap(static_cast<sf::Vector2f>(texSize)));
        islandRect.setOrigin(islandRect.getLocalBounds().getCenter());
        islandRect.setPosition(worldToMinimap(island->getTrans().getPosition()));
        islandRect.setRotation(island->getTrans().getRotation());
        islandRect.setScale(island->getTrans().getScale());
        staticTexture.draw(islandRect);
    }
    staticTexture.display();
}

void Minimap::drawDynamic() {
    dynamicTexture.clear(sf::Color::Transparent);
    // draw player
    auto& player = objManager.getPlayer();
    sf::CircleShape iconPlayer(4);
    iconPlayer.setOutlineThickness(1);
    iconPlayer.setOutlineColor(sf::Color::Black);
    iconPlayer.setFillColor(sf::Color::White);
    iconPlayer.setOrigin(iconPlayer.getLocalBounds().getCenter());
    iconPlayer.setPosition(worldToMinimap(player.getTrans().getPosition()));
    dynamicTexture.draw(iconPlayer);
    // draw enemies
    for (auto enemy : objManager.getEnemies()) {
        if (enemy->currentMode == EnemyMode::IDLE || enemy->currentMode == EnemyMode::RETURN) {
            continue;
        }
        sf::CircleShape iconEnemy(3);
        iconEnemy.setOutlineThickness(1);
        iconEnemy.setOutlineColor(sf::Color::Black);
        iconEnemy.setFillColor(sf::Color::Red);
        iconEnemy.setOrigin(iconEnemy.getLocalBounds().getCenter());
        iconEnemy.setPosition(worldToMinimap(enemy->getTrans().getPosition()));
        dynamicTexture.draw(iconEnemy);
    }
    dynamicTexture.display();
}

void Minimap::setActive(bool state) {
    if (state) {
        worldSize = static_cast<sf::Vector2f>(objManager.getWorld().getSize());
        drawStatic();
    }
    GameObject::setActive(state);
}

sf::Transformable &Minimap::getTrans() {
    return border;
}

sf::Vector2f Minimap::getSize() {
    return border.getSize();
}

void Minimap::updatePosition(sf::Vector2f offset) {
    border.move(offset);
    mapSprite.move(offset);
}

sf::Vector2f Minimap::getMapSize() {
    return static_cast<sf::Vector2f>(staticTexture.getSize());
}

sf::Vector2f Minimap::worldToMinimap(sf::Vector2f pos) {
    auto mapSize = getMapSize();
    return {
        pos.x / worldSize.x * mapSize.x,
        pos.y / worldSize.y * mapSize.y
    };
}
