/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** game.cpp
*/

#include "../include/game.hpp"

GamePong::GamePong(std::shared_ptr<Engine> engine) {
    _font.loadFromFile("assets/fonts/WANTONE.otf");
    InitBackground();
    _timeMove = Timeout(0.01);


    _soundPath = "assets/audio/mario_theme.ogg";


    _sound.openFromFile(_soundPath);
    _sound.setVolume(5);
    _sound.setLoop(true);
}

GamePong::~GamePong() {}

void GamePong::LoadSprite(sf::Sprite& sprite,  sf::Texture &texture, const std::string& imagePath, float posX, float posY, float scaleX, float scaleY) {
    if (texture.loadFromFile(imagePath)) {
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(scaleX, scaleY);
    } else {
        std::cout << "Error: could not load image: " << imagePath << std::endl;
    }
}

void GamePong::InitBackground()
{
    LoadSprite(_background, _backgroundTexture, "assets/images/bgGamePong.png", 0, 0, 1, 1);
    sf::IntRect rectBackground(0, 0, 1920, 1080);
    _rectBackground = rectBackground;
    _background.setTextureRect(_rectBackground);
}

void GamePong::AnimateBackground()  {
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

void GamePong::Loop()
{
    _timeMove.Start();
    gameEngine_._manager->getEntities().push_back(my_player);
    _sound.play();
    std::cout << "GAME STARTED" << std::endl;
    while (_window->isOpen()) {
        HandleEvents();
        Draw();
    }
}

void GamePong::HandleEvents()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window->close();
        }
        if (_event.type == sf::Event::KeyPressed) {
            // std::shared_ptr<Position> positionComp = gameEngine_._manager->getEntityById(3)->getComponentByType<Position>(CONFIG::CompType::POSITION);
            if (_event.key.code == sf::Keyboard::Up) {
                _moveUp = true;
            }
            if (_event.key.code == sf::Keyboard::Down) {
                _moveDown = true;
            }
        }
        if (_event.type == sf::Event::KeyReleased) {
            if (_event.key.code == sf::Keyboard::Up)
                _moveUp = false;
            if (_event.key.code == sf::Keyboard::Down)
                _moveDown = false;
        }
    }
    std::shared_ptr<Position> positionComp = my_player->getComponentByType<Position>(CONFIG::CompType::POSITION);
    std::pair<int, int> pos = positionComp->getPosition();
    if ( _timeMove.can_execute()) {
        if (_moveUp) {
            if (positionComp->getPositionY() > 0) {
                pos.second -= 15;
                positionComp->setPositionY(pos.second);
                my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(pos.first, pos.second));
                _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
            }
        }
        if (_moveDown) {
            if (positionComp->getPositionY() < (1075 - 240)) {
                pos.second += 15;
                positionComp->setPositionY(pos.second);
                my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(pos.first, pos.second));
                _clientOpenUDP->sendMessageSync(_clientOpenUDP->serialize(my_player));
            }
        }
        _timeMove.Start();
    }
}

void GamePong::Draw()
{
        _window->clear(sf::Color::Black);
        _window->draw(_background);

        gameEngine_._manager->lock();
        for (std::shared_ptr<Entity>& entity : gameEngine_._manager->getEntities()) {
            std::vector<std::shared_ptr<Sprite>> SpriteComps = entity->getComponentsByType<Sprite>(CONFIG::CompType::SPRITE);
            for (std::shared_ptr<Sprite> spriteComp : SpriteComps) {
                if (spriteComp->getSpriteType() == CONFIG::SpriteType::BALLSPRITE || spriteComp->getSpriteType() == CONFIG::SpriteType::PLAYERSPRITEAI) {
                    std::pair<int, int> positions = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPosition();
                    sf::Vector2f pos = {static_cast<float>(positions.first), static_cast<float>(positions.second)};
                    spriteComp.get()->setPositionSprite(pos);
                    _window->draw(spriteComp->getSprite());
                }
                if (spriteComp->getSpriteType() == CONFIG::SpriteType::PLAYERSPRITE)
                    _window->draw(spriteComp->getSprite());
            }
            if (entity->getType() == 2 || entity->getType() == 6) {
                std::shared_ptr<Score> scoreComp = entity->getComponentByType<Score>(CONFIG::CompType::SCORE);
                if (scoreComp != nullptr) {
                    sf::Text text;
                    text.setFont(_font);
                    text.setString(std::to_string(scoreComp->getScore()));
                    text.setCharacterSize(100);
                    text.setFillColor(sf::Color::White);
                    if (entity->getType() == 2)
                        text.setPosition(1920 / 2 + 300, 100);
                    else
                        text.setPosition(1920 / 2 - 300, 100);
                    _window->draw(text);
                }
            }
        }
        _window->draw(my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE).get()->getSprite());
        gameEngine_._manager->unlock();

        _window->display();
}
