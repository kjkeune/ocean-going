//
// Created by kklt on 4/24/25.
//

#include "World.hpp"

#include <iostream>

#include "Config.hpp"
#include "../../Game.hpp"
#include "../../util/RandomGenerator.hpp"

const int World::BORDER_THICKNESS = 10;
const int World::TILE_SIZE = 128;
const float World::ISLAND_MARGIN = 400.f;

World::World(sf::Vector2i tiles, sf::Vector2f spawnPos, sf::Vector2f vortexPos):
    size(tiles * TILE_SIZE),
    water(ResourceManager::getInstance().getTexture(textures::WATER)),
    animation(water, 5.f, true),
    sound(ResourceManager::getInstance().getSound(sounds::SEAGULL))
{
    zIndex = 1000;
    int bt = BORDER_THICKNESS * TILE_SIZE;
    auto btf = static_cast<float>(bt);
    water.setPosition({-btf,-btf});
    water.setTextureRect(sf::IntRect({0, 0}, {size.x + 2 * bt, size. y + 2 * bt}));
    animation.start();
    // init borders
    borders.push_back(new Border({-btf, -btf}, {bt, size.y + bt}));
    borders.push_back(new Border({0.f, -btf}, sf::Vector2i{size.x + bt, bt}));
    borders.push_back(new Border({static_cast<float>(size.x), 0.f}, {bt, size.y + bt}));
    borders.push_back(new Border({-btf, static_cast<float>(size.y)}, {size.x + bt, bt}));
    // init spawn point
    auto& rg = RandomGenerator::getInstance();
    if (spawnPos == sf::Vector2f{}) {
        spawnPos = rg.randomPosInRect({ISLAND_MARGIN,ISLAND_MARGIN}, {size.x - ISLAND_MARGIN * 2, size.y - ISLAND_MARGIN * 2});
    }
    spawnPoint = spawnPos;
    // init vortex
    if (vortexPos == sf::Vector2f{}) {
        do {
            vortexPos = rg.randomPosInRect({ISLAND_MARGIN,ISLAND_MARGIN}, {size.x - ISLAND_MARGIN * 2, size.y - ISLAND_MARGIN * 2});
        } while ((vortexPos - spawnPos).length() < ISLAND_MARGIN);
    }
    vortex = new Vortex(vortexPos);
    sound.setRelativeToListener(true);
    sound.setMinDistance(Game::SOUND_MIN_DIST / 2.f);
    sound.setVolume(80.f);
}

void World::update(float delta) {
    animation.update(delta);
    nextSoundTime -= delta;
    if (nextSoundTime <= 0) {
        auto& rg = RandomGenerator::getInstance();
        auto pos = rg.randomPosInRadius(25, Game::SOUND_MIN_DIST, {});
        sound.setPosition({pos.x, 0, pos.y});
        sound.play();
        nextSoundTime = rg.randomFloat(10.f, 30.f);
    }
}

void World::render(sf::RenderTarget& target) {
    target.draw(water, &animation.getShader());
}

sf::Transformable& World::getTrans() {
    return water;
}

std::vector<Island *>& World::getIslands() {
    return islands;
}

void World::addIsland(Island* island) {
    islands.push_back(island);
}

bool World::addRandomIsland(int drops, int avgDropValue) {
    auto& rg = RandomGenerator::getInstance();
    int type = rg.randomInt(0, Island::NUM_TYPES() - 1);
    bool mirroX = rg.randomBool();
    bool mirroY = rg.randomBool();
    sf::Angle ori = rg.randomAngle();
    Island* newIsland;
    bool overlap;
    int iteration = 0;
    int maxIteration = 500;
    do {
        overlap = false;
        sf::Vector2f pos = rg.randomPosInRect({ISLAND_MARGIN,ISLAND_MARGIN}, {size.x - ISLAND_MARGIN * 2, size.y - ISLAND_MARGIN * 2});
        newIsland = new Island(type, pos, ori, mirroX, mirroY, drops, avgDropValue);
        if (checkOverlap(newIsland)) {
            newIsland->destroy();
            overlap = true;
        }
        iteration++;
    } while (overlap && iteration < maxIteration);
    if (iteration == maxIteration) {
        if (DEBUG) std::cout << "Could not create island within " << iteration << " iterations."<< std::endl;
        return false;
    }
    if (DEBUG) std::cout << "Island created within " << iteration << " iterations."<< std::endl;
    islands.push_back(newIsland);
    return true;
}

bool World::checkOverlap(Island* newIsland) {
    auto newIslandCirc = Circle(newIsland->getBoundingCircle().radius + ISLAND_MARGIN / 2, newIsland->getBoundingCircle().center);
    // check spawn point overlap
    if (newIslandCirc.intersects(Circle(ISLAND_MARGIN / 2, spawnPoint))) {
        return true;
    }
    // check vortex overlap
    if (newIslandCirc.intersects(Circle(ISLAND_MARGIN / 2, vortex->getTrans().getPosition()))) {
        return true;
    }
    // check other islands overlap
    for (auto island : islands) {
        auto islandCirc = island->getBoundingCircle();
        if (Circle(islandCirc.radius + ISLAND_MARGIN / 2, islandCirc.center).intersects(newIslandCirc)) {
            return true;
        }
    }
    return false;
}

sf::Vector2f World::getSpawnPoint() {
    return spawnPoint;
}

sf::Vector2f World::getVortexPosition() {
    return vortex->getTrans().getPosition();
}


sf::Vector2i World::getSize() {
    return size;
}


void World::setActive(bool active) {
    for (auto& border : borders) {
        border->setActive(active);
    }
    for (auto& island : islands) {
        island->setActive(active);
    }
    vortex->setActive(active);
    GameObject::setActive(active);
}

void World::destroy() {
    for (auto& border : borders) {
        border->destroy();
    }
    for (auto& island : islands) {
        island->destroy();
    }
    vortex->destroy();
    GameObject::destroy();
}
