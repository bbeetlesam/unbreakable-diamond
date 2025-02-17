#include "game.hpp"
#include "hand.hpp"

/////////////////////////////////////////////////////////////////////////////////////////

Hand::Hand(sf::Vector2f startPos, const sf::Texture& armTex, const sf::Texture& handTex)
    : scale(1.0f), armTexture(armTex), handTexture(handTex), handSprite(handTex)
{
    position = startPos;
    direction = normalize(targetPos - startPos);

    handSprite.setOrigin(sf::Vector2f(handTex.getSize().x / 2, handTex.getSize().y / 2));
    handSprite.setScale({scale, scale});
}

void Hand::draw(sf::RenderWindow& window){
    rotation = std::atan2(direction.y, direction.x) * 180 / PI;

    handSprite.setPosition(position);
    handSprite.setRotation(sf::degrees(rotation + 90.f));

    for (auto& segment : arms) {
        window.draw(segment);
    }

    window.draw(handSprite);
}

/////////////////////////////////////////////////////////////////////////////////////////

NormalHand::NormalHand(sf::Vector2f startPos, const sf::Texture& armTex, const sf::Texture& handTex)
    : Hand(startPos, armTex, handTex)
{
    speed = handSpeed;
}

void NormalHand::update(float deltaTime){
    // 1. Hitung arah dari posisi sekarang ke target
    sf::Vector2f direction = getTargetPos() - getPosition();
    
    // 2. Normalisasi arah
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) direction /= length;  

    // 3. Update posisi hand maju menuju target
    sf::Vector2f newPos = getPosition() + direction * getSpeed() * deltaTime;
    setPosition(newPos);

    // 4. Tambahkan posisi baru hanya jika cukup jauh dari posisi terakhir
    float distSquared = (newPos.x - previousPositions.front().x) * (newPos.x - previousPositions.front().x) +
                        (newPos.y - previousPositions.front().y) * (newPos.y - previousPositions.front().y);
    if (previousPositions.empty() || distSquared >= segmentSpacing * segmentSpacing) {
        previousPositions.push_front(newPos);
    }

    // 5. Hapus posisi lama jika melebihi maxSegments
    if (to<int>(previousPositions.size()) > maxSegments) {
        previousPositions.pop_back();
    }

    // 6. Reset arm sebelum update
    arms.clear();

    // 7. Buat segmen dengan jarak segmentSpacing
    for (size_t i = 1; i < previousPositions.size(); i++) {
        sf::Sprite segment{armTexture};
    
        // Set origin ke tengah sprite agar rotasi lebih akurat
        segment.setOrigin(sf::Vector2f(segment.getGlobalBounds().size.x / 2, segment.getGlobalBounds().size.y / 2));
    
        // Set posisi segment sesuai previousPositions
        segment.setPosition(previousPositions[i]);
    
        // Hitung arah rotasi segment mengikuti jalur sebelumnya
        float angle;
        if (i == 1) {
            // Arm pertama harus selalu mengikuti rotasi hand
            angle = rotation + 90.f;
        } else {
            // Arm lainnya mengikuti rotasi dari segmen sebelumnya
            sf::Vector2f dir = previousPositions[i - 1] - previousPositions[i];
            angle = std::atan2(dir.y, dir.x) * 180 / PI + 90.f;
        }
        
        segment.setRotation(sf::degrees(angle));
        arms.push_back(segment);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

