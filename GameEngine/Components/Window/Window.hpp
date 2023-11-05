/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Window.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {

    class Window : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Window() : AComponent(CONFIG::CompType::WINDOW) {
                _idComponent = 0;
                _type = CONFIG::CompType::WINDOW;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }

            Window(sf::RenderWindow *window) : AComponent(CONFIG::CompType::WINDOW) {
                _idComponent = 0;
                _type = CONFIG::CompType::WINDOW;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                _window = window;
            }

            Window(CONFIG::CompType type, int id, int sizeX, int sizeY, std::string title) : AComponent(CONFIG::CompType::WINDOW), _idComponent(id), _type(type), _sizeX(sizeX), _sizeY(sizeY), _title(title) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                _window->create(sf::VideoMode(_sizeX, _sizeY), _title);
            }

            virtual ~Window() = default;

            void initWindow(int sizeX, int sizeY, std::string title) {
                _sizeX = sizeX;
                _sizeY = sizeY;
                _title = title;
                _window->create(sf::VideoMode(_sizeX, _sizeY), _title);
            }

            void clear() {
                _window->clear();
            }

            void display() {
                _window->display();
            }

            void setWindowSize(int sizeX, int sizeY) {
                _sizeX = sizeX;
                _sizeY = sizeY;
            }

            void setWindowTitle(std::string title) {
                _title = title;
            }

            std::pair<int, int> getWindowSize() {
                return std::make_pair(_sizeX, _sizeY);
            }

            std::string getWindowTitle() {
                return _title;
            }

            sf::RenderWindow *getWindow() {
                return _window;
            }

            void draw(sf::Drawable &sprite) {
                _window->draw(sprite);

            }

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Position>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                // ar & _uuid;
                ar & _type;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};
            virtual std::string getUuid() {return _uuid;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;
            std::string _uuid;

        private:
            sf::RenderWindow *_window;
            std::string _title;
            int _sizeX;
            int _sizeY;


    };
}