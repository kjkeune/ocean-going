//
// Created by kklt on 5/13/25.
//

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>

#include "../UIElement.hpp"

class Button: public virtual UIElement {
public:
    Button(sf::Vector2f size, sf::Color color = sf::Color::White);
    Button(sf::Vector2f size, sf::Texture &bg);
    Button(sf::Texture& bg);
    bool isMouseOnButton();
    bool isClickable();
    void setOnClick(std::function<void()> func);
    void setOnHoverEnter(std::function<void()> func);
    void setOnHoverLeave(std::function<void()> func);
    virtual void setClickable(bool clickable);
    virtual void onClick();
    virtual void onHoverEnter();
    virtual void onHoverLeave();

    void update(float delta) override;
    void render(sf::RenderTarget &target) override;
    sf::Transformable& getTrans() override;
    void setActive(bool state) override;
    void destroy() override;

    void updatePosition(sf::Vector2f offset) override;
    sf::Vector2f getSize() override;

protected:
    bool isHovered = false;
    bool clickable = true;
    sf::RectangleShape rect;

private:
    std::function<void()> on_click;
    std::function<void()> on_hover_enter;
    std::function<void()> on_hover_leave;

};

#endif //BUTTON_HPP
