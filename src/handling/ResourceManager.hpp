//
// Created by kklt on 4/23/25.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../constants/Paths.hpp"

class ResourceManager {
public:
    static ResourceManager& getInstance();

    void preLoad();
    sf::Texture& getTexture(const std::string& filename);
    sf::SoundBuffer& getSound(const std::string& filename);
    sf::Music& getMusic(const std::string& filename);
    sf::Shader& getShader(const std::string& filename);
    sf::Font& getFont(const std::string &filename = fonts::TREAMD);

private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
    std::unordered_map<std::string, sf::Music> music;
    std::unordered_map<std::string, sf::Shader> shaders;
    std::unordered_map<std::string, sf::Font> fonts;

    static ResourceManager* instance;
    ResourceManager();
};

#endif //RESOURCEMANAGER_H
