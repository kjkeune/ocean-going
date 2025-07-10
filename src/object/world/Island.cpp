//
// Created by kklt on 5/8/25.
//

#include "Island.hpp"

#include "Config.hpp"
#include "../../handling/LevelManager.hpp"
#include "../../util/RandomGenerator.hpp"
#include "../../util/Text.hpp"
#include "../drop/Treasure.hpp"

const float Island::DROP_RADIUS = 100.f;
const float Island::DROP_VALUE_DEVIATION = 0.2f;
const float Island::DECORATION_PORTION = 0.5f;
const float Island::MIN_DECORATION_DIST = 12.f;

std::unordered_map<int, std::vector<sf::Vector2f>> Island::TYPE_BOUNDS = {
    {0,{
        {28.f, 18.f}, {67.f, 8.f}, {138.f, 16.f}, {217.f, 55.f},
        {239.f, 97.f}, {225.f, 173.f}, {156.f, 200.f}, {55.f, 182.f},
        {15.f, 136.f}, {12.f, 44.f}}},
    {1, {
        {140.f, 10.f}, {216.f, 20.f}, {427.f, 75.f}, {432.f, 97.f},
        {406.f, 117.f}, {250.f, 164.f}, {25.f, 117.f}, {9.f, 81.f},
        {40.f, 40.f}, {116.f, 11.f}}},
    {2, {
        {110.f, 10.f}, {224.f, 40.f}, {236.f, 64.f}, {220.f, 100.f},
        {135.f, 163.f}, {50.f, 175.f}, {11.f, 153.f}, {14.f, 100.f},
        {72.f, 17.f}}}
};

std::unordered_map<int, int> Island::TYPE_NUM_DECORATION = {
    {0, 9},
    {1, 11},
    {2, 8}
};

int Island::NUM_TYPES() {
    return TYPE_BOUNDS.size();
}

Island::Island(int type, sf::Vector2f pos, sf::Angle ori, bool mirroX, bool mirroY, int drops, int avgDropValue):
    sprite(ResourceManager::getInstance().getTexture(replaceTag(textures::ISLAND, "type", std::to_string(type)))),
    sound(ResourceManager::getInstance().getSound(sounds::WAVES_SHORE))
{
    zIndex = 980;
    this->type = type;
    this->drops = drops;
    this->enemiesSpawns = drops;
    this->avgDropValue = avgDropValue;
    currentOri = RandomGenerator::getInstance().randomFloat(0, M_PI * 2);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setPosition(pos);
    sprite.setRotation(ori);
    if (mirroX) sprite.scale(sf::Vector2f(-1.f, 1.f));
    if (mirroY) sprite.scale(sf::Vector2f(1.f, -1.f));
    // init bounds
    std::vector<sf::Vector2f> globalBounds;
    for (auto& p : TYPE_BOUNDS[type]) {
        globalBounds.push_back(sprite.getTransform() * p);
    }
    bounds = new ConvexPolygon(globalBounds);
    boundingCircle = new Circle(bounds->getBoundingCircle());
    // init decoration
    initDecoration();
    sound.setPosition({pos.x, 0, pos.y});
    sound.setMinDistance(boundingCircle->radius + DROP_RADIUS);
    sound.setAttenuation(15.f);
    sound.setVolume(40.f);
    sound.setLooping(true);
}

void Island::initDecoration() {
    auto& rg = RandomGenerator::getInstance();
    std::vector<sf::Vector2f> positions;
    int numDecoration = TYPE_NUM_DECORATION[type] + rg.randomInt(-2,2);
    for (int i = 0; i < numDecoration; i++) {
        auto deco = new IslandDecoration(rg.randomInt(0, IslandDecoration::NUM_TYPES - 1));
        auto& decoTrans = deco->getTrans();
        auto pos = determineDecorationPos(positions);
        positions.push_back(pos);
        decoTrans.setPosition(pos);
        decoTrans.setRotation(rg.randomAngle());
        if (rg.randomBool()) decoTrans.scale(sf::Vector2f(-1.f, 1.f));
        if (rg.randomBool()) decoTrans.scale(sf::Vector2f(1.f, -1.f));
        decoration.push_back(deco);
    }
}

sf::Vector2f Island::determineDecorationPos(std::vector<sf::Vector2f> &blocked) {
    auto& rg = RandomGenerator::getInstance();
    sf::Vector2f pos;
    bool overlap = false;
    int iteration = 0;
    int maxIteration = 500;
    do {
        int rnd = rg.randomInt(0, bounds->points.size() - 1);
        auto c = bounds->center;
        auto p0 = bounds->points[rnd];
        auto p1 = bounds->points[(rnd + 1) % bounds->points.size()];
        sf::Vector2f cp0 = (p0 - c) * DECORATION_PORTION;
        sf::Vector2f cp1 = (p1 - c) * DECORATION_PORTION;
        pos = rg.randomPosInTriangle(c, c + cp0, c + cp1);
        for (auto& posB : blocked) {
            if ((pos - posB).length() < MIN_DECORATION_DIST) {
                overlap = true;
            }
        }
        iteration++;
    } while (overlap && iteration < maxIteration);
    return pos;
}

void Island::dropLoot() {
    if (drops == 0) {
        return;
    }
    auto& rg = RandomGenerator::getInstance();
    auto center = bounds->center;
    auto pos = rg.randomPosInRadius(boundingCircle->radius + 25, boundingCircle->radius + DROP_RADIUS, center, currentOri - M_PI_2, currentOri + M_PI_2);
    auto dir = center - pos;
    int value = rg.randomInt(avgDropValue * (1 - DROP_VALUE_DEVIATION) , avgDropValue * (1 + DROP_VALUE_DEVIATION));
    currentOri = std::atan2(dir.y, dir.x);
    currentDrop = new Treasure(pos, value, this);
    currentDrop->setActive(true);
    drops--;
}

void Island::spawnEnemies(bool initial) {
    if (enemiesSpawns <= 0  || PEACEFUL) {
        return;
    }
    auto& rg = RandomGenerator::getInstance();
    // spawn either near island or out of player sight
    float rMin;
    float rMax;
    if (initial) {
        rMin = boundingCircle->radius + EnemyShip::HOME_RADIUS / 2;
        rMax = boundingCircle->radius + EnemyShip::HOME_RADIUS;
    }
    else {
        rMax = boundingCircle->radius + World::ISLAND_MARGIN;
        rMin = rMax - 50;
    }
    float dStart = rg.randomFloat(0.f, 2 * M_PI);
    // determine enemies to spawn with LevelManager
    int spawns = rg.randomInt(1, ceilf(enemiesSpawns / 2.f));
    std::vector<EnemyShip*> enemies;
    for (int i = 0; i < spawns; i++) {
        auto newEns = LevelManager::getInstance().createEnemiesPerIsland(this);
        enemies.insert(enemies.end(),newEns.begin(), newEns.end());
    }
    enemiesSpawns -= spawns;
    int numEnemies = enemies.size();
    // set enemy pos randomly around home island with distance to others
    for (int i = 0; i < numEnemies; i++) {
        float d = dStart + i * 2 * M_PI / static_cast<float>(numEnemies);
        auto pos = rg.randomPosInRadius(rMin, rMax, boundingCircle->center, d - M_PI / 8, d + M_PI / 8);
        enemies[i]->getTrans().setPosition(pos);
        enemies[i]->setActive(true);
    }
}

void Island::update(float delta) {

}

void Island::render(sf::RenderTarget& target) {
    target.draw(sprite);
}

sf::Transformable& Island::getTrans() {
    return sprite;
}

void Island::setActive(bool state) {
    if (state) {
        sound.play();
        dropLoot();
        spawnEnemies(true);
    }
    else {
        sound.stop();
    }
    for (auto decoration : decoration) {
        decoration->setActive(state);
    }
    Collidable::setActive(state);
}

void Island::destroy() {
    for (auto decoration : decoration) {
        decoration->destroy();
    }
    Collidable::destroy();
}

void Island::onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) {

}

ConvexPolygon Island::getCollisionBounds() {
    return *bounds;
}

Circle& Island::getBoundingCircle() {
    return *boundingCircle;
}

int Island::getType() {
    return type;
}