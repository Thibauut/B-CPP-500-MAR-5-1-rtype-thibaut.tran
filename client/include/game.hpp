/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** game.hpp
*/

#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include "../../GameEngine/GameEngine.hpp"
#include "AGame.hpp"


#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080
#define GAME_TITLE  "R-Type"

class GameRtype: public AGame {
    public:
        GameRtype(std::shared_ptr<Engine> engine);
        virtual ~GameRtype();

        // game
        virtual void InitBackground() override;
        virtual void AnimateBackground() override;
        virtual void Loop() override;
        virtual void HandleEvents() override;
        virtual void Draw() override;

        void LoadSprite(sf::Sprite& sprite,  sf::Texture &texture, const std::string& imagePath, float posX, float posY, float scaleX, float scaleY);

    sf::VideoMode _videoMode;
    sf::Event _event;
    sf::Font _font;
    sf::Clock _clock;

    sf::Sprite _background;
    sf::Texture _backgroundTexture;
    sf::IntRect _rectBackground;
    sf::Sprite _background2;
    sf::Texture _backgroundTexture2;
    sf::IntRect _rectBackground2;

    bool _moveUp = false;
    bool _moveDown = false;
    bool _moveLeft = false;
    bool _moveRight = false;
    bool _shooting = false;

    //ANIMATION
    bool animStartUp = false;
    bool animEndUp = false;
    bool animStartDown = false;
    bool animEndDown = false;

    std::mutex _1Mutex;

    sf::Sprite _spriteDeath;
    sf::Texture _textureDeath;
    sf::IntRect _rectDeath;
    bool startDeath = false;
    sf::Clock _clockDeath;

    //TIMER MOVEMENT & SHOOT

    double _elapsedTime = 0.0;
    Timeout _timeComp;
    Timeout _timeMove;

    std::string _soundPath;
    sf::Music _sound;
};