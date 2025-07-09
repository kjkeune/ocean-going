//
// Created by kklt on 5/25/25.
//

#ifndef UPGRADEBUTTON_HPP
#define UPGRADEBUTTON_HPP
#include "Button.hpp"
#include "../Label.hpp"
#include "../container/Container.hpp"
#include "../../../factory/Upgrade.hpp"

class ShipPreview;

class UpgradeButton : public Button, public Container {
public:
    UpgradeButton(sf::Vector2f size, UpgradeType type, ShipPreview* preview);
    void setNextUpgrade(Upgrade* upgrade);
    void checkBuyable();

    void addElement(UIElement* element) override;
    void removeAllElements() override;

    void setClickable(bool clickable) override;
    void onClick() override;
    void onHoverEnter() override;
    void onHoverLeave() override;

    void update(float delta) override;
    void render(sf::RenderTarget& target) override;
    sf::Transformable& getTrans() override;
    void setActive(bool state) override;
    void destroy() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

private:
    static std::vector<UpgradeButton*> buttons;
    static sf::Sound soundUpgrade;

    sf::Sound soundHover;
    UpgradeType type;
    ShipPreview* preview;
    Label* title;
    Label* description;
    Label* level;
    Label* gold;
    Label* shipParts;

    void initLabels();

};

#endif //UPGRADEBUTTON_HPP
