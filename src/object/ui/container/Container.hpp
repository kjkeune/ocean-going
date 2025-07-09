//
// Created by kklt on 5/12/25.
//

#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include "../UIElement.hpp"

class Container: public virtual UIElement {
public:
    Container(sf::Vector2f size, sf::Color color = sf::Color::White);
    Container(sf::Vector2f size, sf::Texture& bg);
    Container(sf::Texture& bg);
    void setBorder(float thickness, sf::Color color = sf::Color::Black);
    virtual void addElement(UIElement* element);
    virtual void removeAllElements();

    void update(float delta) override;
    void render(sf::RenderTarget& target) override;
    sf::Transformable& getTrans() override;
    void setActive(bool state) override;
    void destroy() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

protected:
    std::vector<UIElement*> elements;
    sf::RectangleShape rect;

};

#endif //CONTAINER_HPP
