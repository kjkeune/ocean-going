//
// Created by kklt on 5/25/25.
//

#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>

#include "SFML/Graphics/Text.hpp"

std::string wrapTextToWidth(std::string& text, float width, sf::Text& textObj);

std::string replaceTag(const std::string& text, std::string symbol, std::string replacement);

#endif //TEXT_HPP
