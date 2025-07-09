//
// Created by kklt on 4/29/25.
//

#include "Shapes.hpp"

#include <cmath>

Circle::Circle(float radius, sf::Vector2f center) {
    this->radius = radius;
    this->center = center;
}

bool Circle::intersects(const Circle &other) {
    return (center - other.center).length() <= radius + other.radius;
}


ConvexPolygon::ConvexPolygon(std::vector<sf::Vector2f>& points) {
    this->points = points;
    center = centerPoint(points);
}

Circle ConvexPolygon::getBoundingCircle() {
    float dmax = 0.f;
    for (auto& p : this->points) {
        float d = (center - p).length();
        if (d > dmax) {
            dmax = d;
        }
    }
    return {dmax, center};
}

bool ConvexPolygon::intersects(ConvexPolygon &other) {
    auto& pointsA = points;
    auto& pointsB = other.points;
    // All edges of A
    for (size_t i = 0; i < pointsA.size(); ++i) {
        sf::Vector2f p1 = pointsA[i];
        sf::Vector2f p2 = pointsA[(i + 1) % pointsA.size()];
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f axis(-edge.y, edge.x); // Perpendicular
        axis /= axis.length(); // Normalize
        if (!overlapOnAxis(other, axis))
            return false;
    }
    // All edges of B
    for (size_t i = 0; i < pointsB.size(); ++i) {
        sf::Vector2f p1 = pointsB[i];
        sf::Vector2f p2 = pointsB[(i + 1) % pointsB.size()];
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f axis(-edge.y, edge.x); // Perpendicular
        axis /= axis.length(); // Normalize
        if (!overlapOnAxis(other, axis))
            return false;
    }
    return true; // No separating axis found => collision
}

bool ConvexPolygon::overlapOnAxis(ConvexPolygon& other, sf::Vector2f& axis) {
    auto project = [](const std::vector<sf::Vector2f>& points, const sf::Vector2f& axis) {
        float min = points[0].dot(axis);
        float max = min;
        for (const auto& p : points) {
            float projection = p.dot(axis);
            if (projection < min) min = projection;
            if (projection > max) max = projection;
        }
        return std::pair<float, float>{min, max};
    };
    auto [minA, maxA] = project(points, axis);
    auto [minB, maxB] = project(other.points, axis);
    return !(maxA < minB || maxB < minA);
}

std::vector<sf::Vector2f> ConvexPolygon::contactPoints(ConvexPolygon& other) {
    std::vector<sf::Vector2f> contacts;
    for (size_t i = 0; i < points.size(); ++i) {
        sf::Vector2f pa1 = points[i];
        sf::Vector2f pa2 = points[(i + 1) % points.size()];
        for (size_t j = 0; j < other.points.size(); ++j) {
            sf::Vector2f pb1 = other.points[j];
            sf::Vector2f pb2 = other.points[(j + 1) % other.points.size()];
            auto intersection = segmentsIntersect(pa1, pa2, pb1, pb2);
            if (intersection) {
                contacts.push_back(intersection.value());
            }
        }
    }
    return contacts;
}

std::vector<sf::Vector2f> rectToPoints(const sf::FloatRect& rect) {
    return {
        {rect.position.x, rect.position.y},                                     // Top-left
        {rect.position.x + rect.size.x, rect.position.y},                        // Top-right
        {rect.position.x + rect.size.x, rect.position.y + rect.size.y},          // Bottom-right
        {rect.position.x, rect.position.y + rect.size.y}                        // Bottom-left
    };
}

sf::Vector2f centerPoint(std::vector<sf::Vector2f>& points) {
    sf::Vector2f c({0.f,0.f});
    int size = points.size();
    if (size == 0) {
        return c;
    }
    for (auto& p : points) {
        c += p;
    }
    return c / static_cast<float>(size);
}

sf::FloatRect boundingRect(std::vector<sf::Vector2f>& points) {
    float xmin = INFINITY;
    float ymin = INFINITY;
    float xmax = -INFINITY;
    float ymax = -INFINITY;
    for (auto& p : points) {
        xmin = std::min(xmin, p.x);
        ymin = std::min(ymin, p.y);
        xmax = std::max(xmax, p.x);
        ymax = std::max(ymax, p.y);
    }
    return {{xmin, ymin},{xmax - xmin, ymax - ymin}};
}

std::optional<sf::Vector2f> segmentsIntersect(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& q1, sf::Vector2f& q2) {
    sf::Vector2f r = p2 - p1;
    sf::Vector2f s = q2 - q1;
    float rxs = r.cross(s);
    float qpxr = (q1 - p1).cross(r);
    if (rxs == 0) {
        // Lines are parallel...
        if (qpxr == 0) {
            // ...and intersecting
            float t0 = (q1-p1).dot(r) / r.dot(r);
            float t1 = (q1 + s - p1).dot(r) / r.dot(r);
            return p1 + (t0 + t1) / 2 * r;
        }
        //  ...and not intersecting
        return std::nullopt;
    }
    float t = (q1 - p1).cross(s) / rxs;
    float u = (q1 - p1).cross(r) / rxs;
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        // Intersection point
        return p1 + t * r;
    }
    // No intersection
    return std::nullopt;
}

