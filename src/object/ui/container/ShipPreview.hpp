//
// Created by kklt on 5/25/25.
//

#ifndef SHIPPREVIEW_HPP
#define SHIPPREVIEW_HPP
#include "Container.hpp"
#include "../AttributeBar.hpp"
#include "../UIElement.hpp"
#include "../../../factory/ShipConfiguration.hpp"
#include "../../ship/Ship.hpp"

class PreviewShip: public Ship {
public:
    PreviewShip(ShipConfiguration& config);

    void update(float delta) override;
    void sink() override;

    void onCollision(Collidable *other, std::vector<sf::Vector2f> &contacts) override;
};

class ShipPreview: public Container {
public:
    ShipPreview(sf::Vector2f size);
    void startPreview(ShipConfiguration& config);
    void endPreview();
    void updateCurrent();

    void update(float delta) override;
    void render(sf::RenderTarget& target) override;
    void setActive(bool state) override;
    void destroy() override;

    void updatePosition(sf::Vector2f offset) override;

private:
    sf::RectangleShape shipBackground;
    PreviewShip* preview = nullptr;
    PreviewShip* current = nullptr;
    PreviewShip* maxed = new PreviewShip(ShipConfiguration::newMaxedOut());
    bool inPreview = false;

    std::vector<AttributeBar*> attributeBars;

    void initStats(const std::vector<std::string> &names,const std::vector<float>& maxVals, const std::vector<std::function<float(PreviewShip*)>>& getters);
    PreviewShip* setupShip(ShipConfiguration& config);
    void boughtAnimation(PreviewShip* ship);
};



#endif //SHIPPREVIEW_HPP
