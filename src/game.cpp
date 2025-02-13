#include "game.hpp"

Game::Game(){
    initResources();

    window.create(sf::VideoMode(cn::InitWindowSize), cn::WindowName, sf::Style::Titlebar | sf::Style::Close);
    window.setIcon({icon.getSize().x, icon.getSize().y}, icon.getPixelsPtr());
    window.setFramerateLimit(cn::MaxFPS);

    initData();
}

Game::~Game(){
    
}

void Game::run(){
    while(window.isOpen()){
        handleEvents();
        update();
        render();
    }
}

void Game::initData(){
    windowSize = window.getSize();

    isFullscreen = false;

    // Init view
    view.setSize({to<float>(windowSize.x), to<float>(windowSize.y)});
    view.setCenter({0.f, 0.f});
    window.setView(view);

    // Init shield
    shield = std::make_unique<ArcShield>(100.f, 75.f, 15.f, sf::Vector2f{0.f, 0.f}, 100);

    assets.getText("title").setPosition(sf::Vector2f(0.f, 0.f));//(window.mapCoordsToPixel({0.f, 0.f})));
}

void Game::initResources(){
    // Load game's icon (rlly wantto use ico but sfml didn support it *sad*)
    if(!icon.loadFromFile("assets/Untitled.png")){
        std::cerr << "icon didn't load\n";
    }

    // Load game's used fonts
    resources.loadFont("zerovelo", "assets/font/zerovelo.ttf");
    resources.loadFont("yoster", "assets/font/yoster.ttf");

    // Load game's textures and images
    resources.loadTexture("hand", "assets/img/New Piskel (1).png");

    // Load soundBuffer
    resources.loadSoundBuffer("boom", "assets/sounds/708856__funnyvoices__boomerizer-eu-fx.wav");

    // 
    assets.setText("title", "yoster", cn::WindowName, 50, sf::Color::Cyan);

    //
    assets.setSound("boom", "boom");
}

void Game::handleEvents(){
    while(const std::optional<sf::Event> event = window.pollEvent()){
        // If window closed
        if(event->is<sf::Event::Closed>()){
            window.close();
        }

        // If key pressed
        if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->scancode == sf::Keyboard::Scan::Escape){
                window.close();
            }
            else if(keyPressed->scancode == sf::Keyboard::Scan::F11){
                toggleFullscreen(window);
                windowSize = window.getSize();
            }
            else if(keyPressed->scancode == sf::Keyboard::Scan::R){
                // circles.clear();
                std::random_device rd;
                std::mt19937 rng(rd());

                sf::Vector2f spawnPoint = getRandomSpawnPoint({0.f, 0.f}, windowSize.x*0.8f, windowSize.y*0.85f, rng);
                float angle = std::atan2(-spawnPoint.y, -spawnPoint.x) * 180 / PI;

                sf::Sprite sprite(resources.getTexture("hand"));
                sprite.setPosition(spawnPoint);
                sprite.setOrigin({sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2});
                sprite.setScale({1.f, 1.f});
                sprite.setRotation(sf::degrees(angle + 90.f));

                sprites.push_back(std::move(sprite));
            }
            else if(keyPressed->scancode == sf::Keyboard::Scan::Z && circles.size() > 0){
                circles.pop_back();
            }
            else if(keyPressed->scancode == sf::Keyboard::Scan::Left){
                view.move({-20.f, 0.f});
                window.setView(view);
            }
            else if(keyPressed->scancode == sf::Keyboard::Scan::Right){
                view.move({20.f, 0.f});
                window.setView(view);
            }
            else if(keyPressed->scancode == sf::Keyboard::Scan::Up){
                view.zoom(0.9f);
                view.setSize({view.getSize().x * 0.9f, view.getSize().y * 0.9f});
                window.setView(view);
            }
            else if(keyPressed->scancode == sf::Keyboard::Scan::Down){
                view.zoom(1.1f);
                window.setView(view);
            }
        }

        // If window is resized
        if(event->is<sf::Event::Resized>()){
            windowSize = window.getSize();

            view.setSize({to<float>(windowSize.x), to<float>(windowSize.y)});
            view.setCenter({0.f, 0.f});
            window.setView(view);

            assets.getText("title").setPosition(window.mapPixelToCoords({00, 00}));

            std::cout << "> Resized: " << windowSize.x << "x" << windowSize.y << "\n";
        }

        // If mouse pos moved
        if(const auto* moveEvent = event->getIf<sf::Event::MouseMoved>()){
            lastMousePos = window.mapPixelToCoords(moveEvent->position);

            // std::cout << "Mouse moved to: (" << moveEvent->position.x << ", " << moveEvent->position.y << ")\n";
        }

        // If mouse clicked (begin)
        if(const auto* moveEvent = event->getIf<sf::Event::MouseButtonPressed>()){
            sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::CircleShape circle(50u, 40);
            circle.setPosition({worldPos.x - circle.getRadius(), worldPos.y - circle.getRadius()});
            circle.setFillColor(sf::Color(25, 25, 200));
            circles.push_back(std::move(circle));

            assets.getSound("boom").play();

            std::cout << "click (" << moveEvent->position.x << ", " << moveEvent->position.y << ") " << windowSize.x << "x" << windowSize.y << "\n";
        }
    }
}

void Game::update(){
    shield->update(lastMousePos);
    std::cout << shield->getAngle() << " degrees\n";
}

void Game::render(){
    window.clear(cn::BgColor);

    for(const auto& circle : circles){
        window.draw(circle);
    }
    
    for(const auto& sprite : sprites){
        window.draw(sprite);
    }
    
    window.draw(assets.getText("title"));

    shield->draw(window);
    
    drawCrossLine(window);
    window.display();
}

//////////////////////////////////////

void Game::toggleFullscreen(sf::RenderWindow& window){
    isFullscreen = !isFullscreen;

    sf::VideoMode size = (isFullscreen ? sf::VideoMode(cn::DesktopSize) : sf::VideoMode(cn::InitWindowSize));
    sf::State state = (isFullscreen ? sf::State::Fullscreen : sf::State::Windowed);

    window.create(size, cn::WindowName, sf::Style::Titlebar | sf::Style::Close, state);
    window.setIcon({icon.getSize().x, icon.getSize().y}, icon.getPixelsPtr());
    window.setFramerateLimit(cn::MaxFPS);

    if(isFullscreen){
        view.setSize({to<float>(cn::DesktopSize.size.x), to<float>(cn::DesktopSize.size.y)});
    }
    else{
        view.setSize({to<float>(cn::InitWindowSize.x), to<float>(cn::InitWindowSize.y)});
    }

    view.setCenter({0.f, 0.f});
    window.setView(view);
}
