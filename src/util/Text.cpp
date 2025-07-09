//
// Created by kklt on 5/25/25.
//

#include "Text.hpp"

#include <sstream>

std::string wrapTextToWidth(std::string& text, float width, sf::Text& textObj) {
    std::string result;
    std::string word;
    std::istringstream stream(text);
    while (stream >> word) {
        sf::Text temp(textObj.getFont(), result + word + " ", textObj.getCharacterSize());
        if (temp.getLocalBounds().size.x > width) {
            result += "\n" + word + " ";
        } else {
            result += word + " ";
        }
    }
    return result;
}

std::string replaceTag(const std::string& text, std::string tag, std::string replacement) {
    std::string result = text;
    size_t pos = 0;
    while ((pos = result.find(tag, pos)) != std::string::npos) {
        result.replace(pos, tag.size(), replacement);
        pos += replacement.length(); // move past the inserted number
    }
    return result;
}