//
// Created by kklt on 4/23/25.
//

#include "ResourceManager.hpp"

#include <iostream>

#include "Config.hpp"
#include "../constants/Paths.hpp"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager& ResourceManager::getInstance() {
    if (instance == nullptr) {
        instance = new ResourceManager();
    }
    return *instance;
}

ResourceManager::ResourceManager() {
    if (!sf::Shader::isAvailable())
    {
        throw std::runtime_error("Shaders are not supported!");
    }
}

void ResourceManager::preLoad() {
    int count = 0;
    for (auto path : textures::PRELOAD) {
        getTexture(*path);
        count++;
    }
    for (auto path : sounds::PRELOAD) {
        getSound(*path);
        count++;
    }
    if (DEBUG) std::cout << count << " resources preloaded." << std::endl;
}

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    // Check if texture is already loaded
    auto it = textures.find(filename);
    if (it != textures.end()) {
        return it->second;
    }
    // Load and store texture
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    texture.setSmooth(true);
    if (filename == textures::WATER || filename == textures::WATER_DARK) {
        texture.setRepeated(true);
    }
    textures[filename] = std::move(texture);
    return textures[filename];
}

sf::SoundBuffer &ResourceManager::getSound(const std::string &filename) {
    // Check if sound is already loaded
    auto it = sounds.find(filename);
    if (it != sounds.end()) {
        return it->second;
    }
    // Load and store sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load sound: " + filename);
    }
    sounds[filename] = std::move(buffer);
    return sounds[filename];
}

sf::Music &ResourceManager::getMusic(const std::string &filename) {
    auto it = music.find(filename);
    if (it != music.end()) {
        return it->second;
    }
    // Load and store music
    sf::Music file;
    if (!file.openFromFile(filename)) {
        throw std::runtime_error("Failed to load music: " + filename);
    }
    file.setLooping(true);
    file.setVolume(50);
    file.setRelativeToListener(true);
    music[filename] = std::move(file);
    return music[filename];
}

sf::Shader &ResourceManager::getShader(const std::string &filename) {
    // Check if shader is already loaded
    auto it = shaders.find(filename);
    if (it != shaders.end()) {
        return it->second;
    }
    // Load and store shader
    sf::Shader shader;
    sf::Shader::Type shaderType;
    std::filesystem::path path = filename;
    if (path.extension() == ".frag") {
        shaderType = sf::Shader::Type::Fragment;
    }
    else {
        shaderType = sf::Shader::Type::Vertex;
    }
    if (!shader.loadFromFile(path, shaderType)) {
        throw std::runtime_error("Failed to load shader: " + filename);
    }
    shaders[filename] = std::move(shader);
    return shaders[filename];
}


sf::Font& ResourceManager::getFont(const std::string &filename) {
    // Check if font is already loaded
    auto it = fonts.find(filename);
    if (it != fonts.end()) {
        return it->second;
    }
    // Load and store font
    sf::Font font;
    if (!font.openFromFile(filename)) {
        throw std::runtime_error("Failed to load font: " + filename);
    }
    fonts[filename] = std::move(font);
    return fonts[filename];
}
