//
// Created by kklt on 4/28/25.
//

#ifndef ENEMYSHIP_HPP
#define ENEMYSHIP_HPP
#include "Ship.hpp"
#include "../ui/HealthBar.hpp"
#include "../world/Island.hpp"

enum class EnemyMode {
    IDLE,
    HUNT,
    FIGHT,
    RETURN
};

class EnemyShip : public Ship {
public:
    static const float HOME_RADIUS;
    static const float FRONTAL_ATTACK_ANGLE;
    static const float ALIGN_EPSILON;
    static const float MIN_DISTANCE;

    float sightRadius = 600;
    float fireCooldown = 1.5f;
    EnemyMode currentMode = EnemyMode::IDLE;

    EnemyShip(ShipConfiguration& config, Island* home);
    void update(float delta) override;
    void setActive(bool active) override;
    void destroy() override;
    void onCollision(Collidable *other, std::vector<sf::Vector2f> &contacts) override;

    void sink() override;

private:
    HealthBar* healthBar;
    Island* homeIsland;
    float timeToFire = 0.f;

    float fightRadius;
    sf::Vector2f targetDir;
    Island* inRange = nullptr;

    void updateCurrentMode();
    void idleMode();
    void huntMode();
    void fightMode();
    void returnMode();

    void avoidCollisionIslands();
    bool isIslandInRange(Island* island);
    void avoidCollisionShips();
    bool isShipInRange(Ship* ship);

    void adjustSailToTurn();
    void alignWithTarget();
    bool cannonsAlignedWithPlayer();
    float attackAngle();
};

#endif //ENEMYSHIP_HPP
