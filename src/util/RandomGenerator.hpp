//
// Created by kklt on 5/6/25.
//

#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP
#include <random>

#include "SFML/System/Vector2.hpp"

class RandomGenerator {
public:
    static RandomGenerator& getInstance();

    bool randomBool();
    int randomInt(int a, int b);
    float randomFloat(float a, float b);
    sf::Vector2f randomPosInRect(sf::Vector2f pos, sf::Vector2f size);
    sf::Vector2f randomPosInTriangle(sf::Vector2f v0, sf::Vector2f v1, sf::Vector2f v2);
    sf::Vector2f randomPosInRadius(float rMin, float rMax, sf::Vector2f center, float dMin = 0, float dMax = 2 * M_PI);
    sf::Vector2f randomDirection(float dMin = 0, float dMax = 2 * M_PI);
    sf::Angle randomAngle(float dMin = 0, float dMax = 2 * M_PI);
    bool randomChoice(float probability);

private:
    static RandomGenerator* instance;

    RandomGenerator();
    RandomGenerator(unsigned int seed);

    std::mt19937 generator;
};

#endif //RANDOMGENERATOR_HPP
