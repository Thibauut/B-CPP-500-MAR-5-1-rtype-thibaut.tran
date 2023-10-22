/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** game.hpp
*/

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
#include "../graphical/utils/sfml_func.cpp"
#include "global.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../network/OpenUDP/OpenUDP.hpp"


#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080
#define GAME_TITLE  "R-Type"

#pragma once

class Game {
    public:
        Game(sf::RenderWindow *window);
        ~Game() = default;

        void Init();
        void InitBackground();

        void AnimateBackground();

        void Loop();
        void HandleEvents();
        void Draw();


    std::shared_ptr<Entity> my_player;
    GameEngine::Engine gameEngine_;


    SfmlFunc sfmlFunc;
    sf::RenderWindow *_window;
    sf::VideoMode _videoMode;
    sf::Event _event;
    sf::Font _font;
    sf::Clock _clock;
    std::shared_ptr<ClientOpenUDP> _clientOpenUDP;

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

    std::string my_id_;
    std::string portUDP_;


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