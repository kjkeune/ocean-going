//
// Created by kklt on 4/29/25.
//

#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"

class Circle {
public:
    float radius;
    sf::Vector2f center;

    Circle(float radius, sf::Vector2f center);
    bool intersects(const Circle &other);
};

class ConvexPolygon {
public:
    std::vector<sf::Vector2f> points;
    sf::Vector2f center;

    ConvexPolygon(std::vector<sf::Vector2f>& points);
    bool intersects(ConvexPolygon &other);
    std::vector<sf::Vector2f> contactPoints(ConvexPolygon &other);
    Circle getBoundingCircle();

private:
    bool overlapOnAxis(ConvexPolygon& other, sf::Vector2f& axis);

};

std::vector<sf::Vector2f> rectToPoints(const sf::FloatRect& rect);

sf::Vector2f centerPoint(std::vector<sf::Vector2f>& points);

sf::FloatRect boundingRect(std::vector<sf::Vector2f>& points);

std::optional<sf::Vector2f> segmentsIntersect(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& q1, sf::Vector2f& q2);

#endif //SHAPES_HPP
