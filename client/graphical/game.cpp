/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** game.cpp
*/

#include "../include/game.hpp"

void Game::InitBackground()
{
    sfmlFunc.LoadSprite(_background, _backgroundTexture, "assets/images/background_1.png", 0, 0, 7, 7);
    sf::IntRect rectBackground(0, 0, 256, 224);
    _rectBackground = rectBackground;
    _background.setTextureRect(_rectBackground);

    sfmlFunc.LoadSprite(_background2, _backgroundTexture2, "assets/images/background_2.png", 0, 0, 7, 7);
    sf::IntRect rectBackground2(0, 0, 256, 224);
    _rectBackground2 = rectBackground2;
    _background2.setTextureRect(_rectBackground2);

    sf::Color spriteColor = _background.getColor();
    spriteColor.a = 128;
    _background.setColor(spriteColor);

    sf::Color spriteColor2 = _background2.getColor();
    spriteColor2.a = 128;
    _background2.setColor(spriteColor2);
}

void Game::AnimateBackground() {
    sf::Time elapsed = _clock.getElapsedTime();
    if (elapsed.asSeconds() > 0.03) {
        _rectBackground.left += 1;
        _rectBackground2.left += 2;
        if (_rectBackground.left >= 256) {
            _rectBackground.left = 0;
        }
        if (_rectBackground2.left >= 256) {
            _rectBackground2.left = 0;
        }
        _background.setTextureRect(_rectBackground);
        _background2.setTextureRect(_rectBackground2);
        _clock.restart();
    }
}

Game::Game(sf::RenderWindow *window): _window(window)
{
    _font.loadFromFile("assets/fonts/WANTONE.otf");
    InitBackground();
}

void Game::Loop()
{
    if (my_id_ == "1")
        _players.push_back(std::make_shared<PlayerUDP>(stoi(my_id_), 300, 300));
    else if (my_id_ == "2")
        _players.push_back(std::make_shared<PlayerUDP>(stoi(my_id_), 300, 400));
    else if (my_id_ == "3")
        _players.push_back(std::make_shared<PlayerUDP>(stoi(my_id_), 300, 500));
    else if (my_id_ == "4")
        _players.push_back(std::make_shared<PlayerUDP>(stoi(my_id_), 300, 600));
    if (_clientOpenUDP->sendMessageSyncFirst(my_id_ + " 300 300 false") == true) {
        if (_players.empty()) {
            std::cout << "empty" << std::endl;
        }
        for(std::shared_ptr<PlayerUDP> &player : _players) {
            if (player.get()->_id == 1) {
                player.get()->_spriteTexture.loadFromFile("assets/sprites/r-typesheet42.gif");
                player.get()->_sprite.setTexture(player.get()->_spriteTexture);
                sf::IntRect testRect(0, 0, std::round(33.2), std::round(17.2));
                player.get()->_sprite.setScale(sf::Vector2f(3, 3));
                player.get()->_sprite.setTextureRect(testRect);
                player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x, player.get()->_y));

            }
            if (player.get()->_id == 2) {
                player.get()->_spriteTexture.loadFromFile("assets/sprites/r-typesheet42.gif");
                player.get()->_sprite.setTexture(player.get()->_spriteTexture);
                sf::IntRect testRect(0, std::round(17.2), std::round(33.2), std::round(17.2));
                player.get()->_sprite.setScale(sf::Vector2f(3, 3));
                player.get()->_sprite.setTextureRect(testRect);
                // player.get()->_x = 300;
                // player.get()->_y = 400;
                // player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x, player.get()->_y));
            }
            if (player.get()->_id == 3) {
                player.get()->_spriteTexture.loadFromFile("assets/sprites/r-typesheet42.gif");
                player.get()->_sprite.setTexture(player.get()->_spriteTexture);
                sf::IntRect testRect(0, std::round(34.4), std::round(33.2), std::round(17.2));
                player.get()->_sprite.setScale(sf::Vector2f(3, 3));
                player.get()->_sprite.setTextureRect(testRect);
                // player.get()->_x = 300;
                // player.get()->_y = 500;
                // player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x, player.get()->_y));
            }
            if (player.get()->_id == 4) {
                player.get()->_spriteTexture.loadFromFile("assets/sprites/r-typesheet42.gif");
                player.get()->_sprite.setTexture(player.get()->_spriteTexture);
                sf::IntRect testRect(0, std::round(51.6), std::round(33.2), std::round(17.2));
                player.get()->_sprite.setScale(sf::Vector2f(3, 3));
                player.get()->_sprite.setTextureRect(testRect);
                // player.get()->_x = 300;
                // player.get()->_y = 600;
                // player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x, player.get()->_y));
            }
        }
    }

    while (_window->isOpen()) {
        HandleEvents();
        AnimateBackground();
        Draw();
    }
}

void Game::HandleEvents()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window->close();
        }
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::Up)
                _moveUp = true;
            if (_event.key.code == sf::Keyboard::Down)
                _moveDown = true;
            if (_event.key.code == sf::Keyboard::Left)
                _moveLeft = true;
            if (_event.key.code == sf::Keyboard::Right)
                _moveRight = true;
            if (_event.key.code == sf::Keyboard::Space)
                _shooting = true;
        }
        if (_event.type == sf::Event::KeyReleased) {
            if (_event.key.code == sf::Keyboard::Up)
                _moveUp = false;
            if (_event.key.code == sf::Keyboard::Down)
                _moveDown = false;
            if (_event.key.code == sf::Keyboard::Left)
                _moveLeft = false;
            if (_event.key.code == sf::Keyboard::Right)
                _moveRight = false;
            if (_event.key.code == sf::Keyboard::Space)
                _shooting = false;
        }
    }
    if (_moveUp) {
        action = new Action(UP);
        for(std::shared_ptr<PlayerUDP> &player : _players) {
            if (player.get()->_id == std::stoi(my_id_))
                player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x, player.get()->_y -= 1));
        }
    }
    if (_moveDown) {
        action = new Action(DOWN);
        for(std::shared_ptr<PlayerUDP> &player : _players) {
            if (player.get()->_id == std::stoi(my_id_))
                player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x, player.get()->_y += 1));
        }
    }
    if (_moveLeft) {
        action = new Action(LEFT);
        for(std::shared_ptr<PlayerUDP> &player : _players) {
            if (player.get()->_id == std::stoi(my_id_))
                player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x -= 1, player.get()->_y));
        }
    }
    if (_moveRight) {
        action = new Action(RIGHT);
        for(std::shared_ptr<PlayerUDP> &player : _players) {
            if (player.get()->_id == std::stoi(my_id_))
                player.get()->_sprite.setPosition(sf::Vector2f(player.get()->_x += 1, player.get()->_y));
        }
    }
    if (_shooting) {
        action = new Action(SHOOT);
    }
}

void Game::Draw()
{
        _window->clear(sf::Color::Black);
        _window->draw(_background);
        _window->draw(_background2);

        for (auto& pl : _players) {
            _window->draw(pl->_sprite);
        }
        _window->display();
}