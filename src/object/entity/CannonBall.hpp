//
// Created by kklt on 4/27/25.
//

#ifndef CANNONBALL_HPP
#define CANNONBALL_HPP
#include "../Collidable.hpp"
#include "../GameObject.hpp"
#include "../../util/Animation.hpp"

class CannonBall: public Collidable {
    public:
        float damage = 25.f;
        float range = 300.f;

        CannonBall(float damage, float range, sf::Vector2f velocity);
        void update(float delta) override;
        void render(sf::RenderTarget &target) override;
        sf::Transformable& getTrans() override;
        void onCollision(Collidable* other, std::vector<sf::Vector2f>& contacts) override;
        ConvexPolygon getCollisionBounds() override;

        void hit();
        void miss();

    private:
        static const float DAMAGE_DEVIATION;
        static const float CRITICAL_DAMAGE;
        static const float CRITICAL_RANGE_POR;
        sf::Sprite sprite;
        sf::Vector2f velCurrent;
        sf::Sound sound;
        float rangeLeft;
        bool isCritical = false;
};

#endif //CANNONBALL_HPP
