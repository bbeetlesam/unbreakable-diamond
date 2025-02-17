#ifndef RES
#define RES

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

// Class for resource manager (ive had enough with that fucking Game class)
class ResourceManager{
    public:
        // Load font, texture, sound buffer, dll.
        bool loadFont(const std::string& id, const std::string& filePath);
        bool loadTexture(const std::string& id, const std::string& filePath);
        bool loadSoundBuffer(const std::string& id, const std::string& filePath);

        // Getters dengan pengecekan aman
        sf::Font& getFont(const std::string& id);
        sf::Texture& getTexture(const std::string& id);
        sf::SoundBuffer& getSoundBuffer(const std::string& id);

    private:
        std::unordered_map<std::string, sf::Font> fonts;
        std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
        std::unordered_map<std::string, sf::Texture> textures;
};

// Class for 
class ObjectManager{
    public:
        ObjectManager(ResourceManager& resourceManager) : resources(resourceManager) {}

        // 
        void setText(const std::string& id, const std::string& fontID, const std::string& content, unsigned size = 30, sf::Color color = sf::Color::White);
        //
        void setSound(const std::string& id, const std::string& soundBufferID);
        //
        void setSprite(const std::string& id, const std::string& textureID);
        
        sf::Text& getText(const std::string& id);
        sf::Sound& getSound(const std::string& id);
        sf::Sprite& getSprite(const std::string& id);

    private:
        ResourceManager& resources;
        std::unordered_map<std::string, sf::Text> texts;
        std::unordered_map<std::string, sf::Sound> sounds;
        std::unordered_map<std::string, sf::Sprite> sprites;
};

#endif // RES