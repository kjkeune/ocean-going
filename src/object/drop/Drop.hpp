//
// Created by kklt on 5/4/25.
//

#ifndef DROP_HPP
#define DROP_HPP
#include "../Collidable.hpp"
#include "../GameObject.hpp"
#include "../ship/PlayerShip.hpp"
#include "../ui/Label.hpp"

class Island;
class Ship;

class Drop: public Collidable {
public:
    Drop(Island* island = nullptr);
    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;
    void onCollision(Collidable *other, std::vector<sf::Vector2f>& contacts) override;
    ConvexPolygon getCollisionBounds() override;

protected:
    static const float LABEL_FADEOUT_PER_SEC;

    sf::Sprite sprite;
    sf::Sound sound;
    Island* island;
    Label* collectLabel = nullptr;
    bool collected = false;

    virtual void collect(PlayerShip& ship);
};

#endif //DROP_HPP
