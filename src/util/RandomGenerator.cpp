//
// Created by kklt on 5/6/25.
//

#include "RandomGenerator.hpp"

#include "Config.hpp"

RandomGenerator* RandomGenerator::instance = nullptr;

RandomGenerator& RandomGenerator::getInstance() {
    if (instance == nullptr) {
        if (RANDOM_SEED) {
            instance = new RandomGenerator();
        }
        else {
            instance = new RandomGenerator(SEED);
        }
    }
    return *instance;
}

RandomGenerator::RandomGenerator(): generator(std::random_device{}()) {}

RandomGenerator::RandomGenerator(unsigned int seed): generator(seed) {}

bool RandomGenerator::randomBool() {
    std::uniform_int_distribution dist(0, 1);
    return dist(generator);
}


int RandomGenerator::randomInt(int a, int b) {
    std::uniform_int_distribution dist(a, b);
    return dist(generator);
}

float RandomGenerator::randomFloat(float a, float b) {
    std::uniform_real_distribution dist(a, b);
    return dist(generator);
}

sf::Vector2f RandomGenerator::randomDirection(float dMin, float dMax) {
    float theta = randomFloat(dMin, dMax);
    return {static_cast<float>(cos(theta)), static_cast<float>(sin(theta))};
}

sf::Angle RandomGenerator::randomAngle(float dMin, float dMax) {
    float theta = randomFloat(dMin, dMax);
    return sf::radians(theta);
}

sf::Vector2f RandomGenerator::randomPosInRect(sf::Vector2f pos, sf::Vector2f size) {
    return {randomFloat(pos.x, pos.x + size.x), randomFloat(pos.y, pos.y + size.y)};
}

sf::Vector2f RandomGenerator::randomPosInTriangle(sf::Vector2f v0, sf::Vector2f v1, sf::Vector2f v2) {
    float u = randomFloat(0.f, 1.f);
    float v = randomFloat(0.f, 1.f);
    if (u + v > 1.f) {
        u = 1.f - u;
        v = 1.f - v;
    }
    return v0 + u * (v1 - v0) + v * (v2 - v0);
}

sf::Vector2f RandomGenerator::randomPosInRadius(float rMin, float rMax, sf::Vector2f center, float dMin, float dMax) {
    float r = randomFloat(rMin, rMax);
    auto dir = randomDirection(dMin, dMax);
    return center + dir * r;
}

bool RandomGenerator::randomChoice(float probability) {
    return randomFloat(0, 1) <= probability;
}
