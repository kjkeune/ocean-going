//
// Created by kklt on 6/2/25.
//

#ifndef MULTILAYERTEXTURE_HPP
#define MULTILAYERTEXTURE_HPP
#include <vector>

#include "SFML/Graphics/RenderTexture.hpp"

class MultiLayerTexture : public sf::RenderTexture {
public:
    void setup(const std::string& base, const std::vector<std::string>& layers);
};

#endif //MULTILAYERTEXTURE_HPP
