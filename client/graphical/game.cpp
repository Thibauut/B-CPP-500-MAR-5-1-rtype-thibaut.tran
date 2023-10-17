/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** game.cpp
*/

#include "../include/game.hpp"

void Game::InitBackground()
{
    sfmlFunc.LoadSprite(_background, _backgroundTexture, "assets/images/background_1.png", 0, 0, 8, 8);
    sf::IntRect rectBackground(0, 0, 256, 224);
    _rectBackground = rectBackground;
    _background.setTextureRect(_rectBackground);

    sfmlFunc.LoadSprite(_background2, _backgroundTexture2, "assets/images/background_2.png", 0, 0, 8, 8);
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
    _timeMove = Timeout(0.01);
}

void Game::Loop()
{
    _timeMove.Start();
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
                if (_event.key.code == sf::Keyboard::Up) {
                    animStart = true;
                    _moveUp = true;
                }
                if (_event.key.code == sf::Keyboard::Down) {
                    _moveDown = true;
                }
                if (_event.key.code == sf::Keyboard::Left) {
                    _moveLeft = true;
                }
                if (_event.key.code == sf::Keyboard::Right) {
                    _moveRight = true;
                }
                if (_event.key.code == sf::Keyboard::Space) {
                    _shooting = true;
                    my_player->getComponentByType<Weapon>(CONFIG::CompType::WEAPON)->setShooting(false, 0.0);
                    _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
                }
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
            if (_event.key.code == sf::Keyboard::Space) {
                _shooting = false;
                my_player->getComponentByType<Weapon>(CONFIG::CompType::WEAPON)->setShooting(false, 0.0);
                _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
            }
        }
    }
    std::shared_ptr<Position> positionComp = my_player->getComponentByType<Position>(CONFIG::CompType::POSITION);
    std::pair<int, int> pos = positionComp->getPosition();
    if ( _timeMove.can_execute()) {
        if (_moveUp) {
            if (positionComp->getPositionY() > 0) {
                pos.second -= 10;
                positionComp->setPositionY(pos.second);
                my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(pos.first, pos.second));
                _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
            }
        }
        if (_moveDown) {
            if (positionComp->getPositionY() < (1075 - (17.2 * 3))) {
                pos.second += 10;
                positionComp->setPositionY(pos.second);
                my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(pos.first, pos.second));
                _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
            }
        }
        if (_moveLeft) {
            if (positionComp->getPositionX() > 5) {
                pos.first -= 10;
                positionComp->setPositionX(pos.first);
                my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(pos.first, pos.second));
                _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
            }
        }
        if (_moveRight) {
            if (positionComp->getPositionX() < (1915 - (33.2 * 3))) {
                pos.first += 10;
                positionComp->setPositionX(pos.first);
                my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(pos.first, pos.second));
                _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
            }
        }
        _timeMove.Start();
    }
    if (_shooting) {
        _elapsedTime = _timeComp.getElapsedSeconds();
        my_player->getComponentByType<Weapon>(CONFIG::CompType::WEAPON)->setShooting(true, _elapsedTime);
        _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
    }
}

void Game::Draw()
{
        _window->clear(sf::Color::Black);
        _window->draw(_background);
        _window->draw(_background2);

        for (std::shared_ptr<Entity>& entity : entities_->getEntities()) {
            std::shared_ptr<Sprite> spriteComp = entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
            if (spriteComp) {
                std::pair<int, int> positions = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPosition();
                sf::Vector2f pos = {static_cast<float>(positions.first), static_cast<float>(positions.second)};
                spriteComp.get()->setPositionSprite(pos);
                _window->draw(spriteComp->getSprite());
            }
            if (entity->getType() == 2) {
                entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE).get()->AnimateLoop(0.1, 0, 132.8, spriteComp->getSpriteWidth());
            }
        }

        if (animStart) {
            my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->AnimationInput(0.1, 0, 132.8, my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->getSpriteWidth(), animStart);
        }
        _window->draw(my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE).get()->getSprite());


        _window->display();
}
