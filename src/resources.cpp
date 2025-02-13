#include "resources.hpp"
#include <stdexcept>

#include <iostream>

// Load Font
bool ResourceManager::loadFont(const std::string& id, const std::string& filePath) {
    sf::Font font(filePath);
    // if (!font.loadFromFile(filePath)) {
    //     std::cerr << "Failed to load font: " << filePath << std::endl;
    //     return false;
    // }
    fonts.emplace(id, std::move(font));
    return true;
}

// Load Texture
bool ResourceManager::loadTexture(const std::string& id, const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return false;
    }
    textures.emplace(id, std::move(texture));
    return true;
}

// Load SoundBuffer
bool ResourceManager::loadSoundBuffer(const std::string& id, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Failed to load sound: " << filePath << std::endl;
        return false;
    }
    soundBuffers.emplace(id, std::move(buffer));
    return true;
}

// Get Font
sf::Font& ResourceManager::getFont(const std::string& id) {
    auto it = fonts.find(id);
    if (it == fonts.end()) throw std::runtime_error("Font not found: " + id);
    return it->second;
}

// Get Texture
sf::Texture& ResourceManager::getTexture(const std::string& id) {
    auto it = textures.find(id);
    if (it == textures.end()) throw std::runtime_error("Texture not found: " + id);
    return it->second;
}

// Get SoundBuffer
sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& id) {
    auto it = soundBuffers.find(id);
    if (it == soundBuffers.end()) throw std::runtime_error("SoundBuffer not found: " + id);
    return it->second;
}

//////////////////////////////////////////////////////////////////////////////////////////

/// Create a drawable text from a font @param string unique map key @param string font key @param string message/content @param u_int text size -> 30 @param sf::Color text color -> sf::Color::White
void ObjectManager::setText(const std::string& id, const std::string& fontID, const std::string& content, unsigned size, sf::Color color) {
    sf::Text text(resources.getFont(fontID), content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    texts.emplace(id, std::move(text));
}

/// Create a playable sound from a soundBuffer @param string unique map key @param string soundBuffer key
void ObjectManager::setSound(const std::string& id, const std::string& soundBufferID) {
    sf::Sound sound(resources.getSoundBuffer(soundBufferID));
    sounds.emplace(id, std::move(sound));
}

/// Create a drawable texture/image from a texture @param string unique map key @param string soundBuffer key
void ObjectManager::setSprite(const std::string& id, const std::string& textureID){
    sf::Sprite sprite(resources.getTexture(textureID));
    sprites.emplace(id, std::move(sprite));
}

// 
sf::Text& ObjectManager::getText(const std::string& id) {
    auto it = texts.find(id);
    if (it == texts.end()) throw std::runtime_error("Text not found: " + id);
    return it->second;
}

// 
sf::Sound& ObjectManager::getSound(const std::string& id) {
    auto it = sounds.find(id);
    if (it == sounds.end()) throw std::runtime_error("Sound not found: " + id);
    return it->second;
}

// 
sf::Sprite& ObjectManager::getSprite(const std::string& id){
    auto it = sprites.find(id);
    if (it == sprites.end()) throw std::runtime_error("Sprite not found: " + id);
    return it->second;
}

