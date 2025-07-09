

#ifndef SHIP_H
#define SHIP_H
#include "../GameObject.hpp"
#include "SFML/Graphics.hpp"
#include "Cannon.hpp"
#include "Ruder.hpp"
#include "Sail.hpp"
#include "../Collidable.hpp"
#include "../../factory/ShipConfiguration.hpp"
#include "../../factory/Upgrade.hpp"
#include "../../util/MultiLayerTexture.hpp"

class Ship: public Collidable {
public:
    const static int MAX_SAIL_STATE; // max velocity

    int hullType = 1;
    float maxHealth = 100;

    int numCannons = 2;
    float canDamage = 25.f;
    float canRange = 420.f;
    float canReloadTime = 2.f;

    int numSails = 1;
    float velPerSailState = 45.f; // how fast per sailState

    float turnPerSec = 45.f; // velocity of turning

    bool invincible = false;
    bool disabled = false;

    Ship(ShipConfiguration& config);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;
    void setActive(bool active) override;
    void destroy() override;

    void onCollision(Collidable* other, std::vector<sf::Vector2f>& contacts) override;
    ConvexPolygon getCollisionBounds() override;

    void increaseSails();
    void decreaseSails();
    void setSailState(int state);
    int getSailState();
    float determineVelocity(int sailState);
    sf::Vector2f getVelocity();
    sf::Vector2f getDirection();

    void turnAngle(float angle);
    float getTurnAngle();

    void fireCannons();
    std::vector<bool> cannonsLoaded();

    void heal(float amount);
    void damage(float amount);
    float getHealth();

protected:
    sf::Sprite hull;
    MultiLayerTexture textureHull;
    std::vector<Sail*> sails;
    std::vector<Cannon*> cannons;
    Ruder* ruder;
    std::vector<sf::Vector2f> bounds;
    sf::Sound soundDamage;
    sf::Sound soundSail;
    sf::Sound soundHull;

    float velIncPerSec = 30.f; // acceleration
    float maxTurn = 70.f; // max turning angle
    float borderDamagePerSec;
    float collisionDamagePerSec = 150.f;
    int collisionDamageFactor = 0;
    float pushVelPerSec = 175.f;

    virtual void sink() = 0;

private:
    static std::unordered_map<int, std::vector<sf::Vector2f>> TYPE_BOUNDS;

    float health;
    int sailState = 0;
    float vel = 0.f;
    sf::Vector2f velCurrent = {0.f, 0.f};
    float turn = 0.f;
    bool isOutsideBorder = false;
    bool isInCollision = false;
    sf::Vector2f pushVelCurrent = {0.f, 0.f};

    void initHull(ShipConfiguration& config);
    void initCannons(ShipConfiguration& config);
    void initSails(ShipConfiguration& config);
    void initRuder(ShipConfiguration& config);

};

#endif //SHIP_H
