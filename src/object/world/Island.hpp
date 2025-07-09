//
// Created by kklt on 5/8/25.
//

#ifndef ISLAND_HPP
#define ISLAND_HPP

#include "IslandDecoration.hpp"
#include "../Collidable.hpp"
#include "../GameObject.hpp"
#include "../drop/Drop.hpp"

class Island: public Collidable {
public:
    static std::unordered_map<int, std::vector<sf::Vector2f>> TYPE_BOUNDS;
    static std::unordered_map<int, int> TYPE_NUM_DECORATION;
    static const float DROP_RADIUS;
    static const float DROP_VALUE_DEVIATION;
    static const float DECORATION_PORTION;
    static const float MIN_DECORATION_DIST;

    static int NUM_TYPES();

    Island(int type, sf::Vector2f pos, sf::Angle ori = sf::degrees(0), bool mirroX = false, bool mirroY = false, int drops = 5, int avgDropValue = 100);
    void dropLoot();
    void spawnEnemies(bool initial = false);
    Circle& getBoundingCircle();
    int getType();

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;
    void setActive(bool state) override;
    void destroy() override;

    void onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) override;
    ConvexPolygon getCollisionBounds() override;

private:
    sf::Sprite sprite;
    ConvexPolygon* bounds;
    Circle* boundingCircle;
    std::vector<IslandDecoration*> decoration;
    sf::Sound sound;

    int type;
    int drops;
    int enemiesSpawns;
    int avgDropValue;

    Drop* currentDrop = nullptr;
    float currentOri;

    void initDecoration();
    sf::Vector2f determineDecorationPos(std::vector<sf::Vector2f>& blocked);

};

#endif //ISLAND_HPP
