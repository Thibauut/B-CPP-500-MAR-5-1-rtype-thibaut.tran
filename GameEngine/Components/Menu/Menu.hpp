/*
** EPITECH PROJECT, 2023
** Health
** File description:
** Health
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"
#include "../../../client/include/menu.hpp"

namespace GameEngine {
    class MenuComp : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            MenuComp() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::MENU;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            MenuComp(CONFIG::CompType type, int id, int value, std::string font, std::string background, std::string background2, std::string title, std::shared_ptr<AGame> game) : AComponent(CONFIG::CompType::MENU), _idComponent(id), _type(type),
            _font(font), _background(background), _background2(background2), _title(title), _game(game) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                initMenu();
            }

            ~MenuComp() = default;

            void timerThread(Menu* menu) {
                int counter = 0;
                while (shouldStop == false) {
                    if (menu->_isConnected && !menu->_selectedRoom && !menu->_isCreatingRoom && menu->_inGame == false && menu->ReadyGame == false) {
                        menu->_1Mutex.lock();
                        menu->UpdateRoom();
                        menu->_1Mutex.unlock();
                    }
                    if (menu->_isConnected && menu->_selectedRoom && !menu->_isCreatingRoom && menu->_inGame == false && menu->ReadyGame == false) {
                        menu->_1Mutex.lock();
                        menu->UpdateRoom();
                        menu->UpdatePlayerList();
                        menu->_1Mutex.unlock();
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }

            void initMenu() {
                _menu = new Menu("127.0.0.1", "12345", _font, _background, _background2, _title, _game);
                std::thread timer([this]() { timerThread(_menu); });
                timer.detach();
            }

            sf::RenderWindow *getWindow() {
                return _menu->_window;
            }

            void menuRun() {
                _menu->Loop();
            }

            void setFont(const std::string &font) {_font = font;};
            void getFont(const std::string &font) {_font = font;};
            void setBackground(const std::string &background) {_background = background;};
            void getBackground(const std::string &background) {_background = background;};
            void setTitle(const std::string &title) {_title = title;};
            void getTitle(const std::string &title) {_title = title;};

            // void timerThread()

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
            std::string _font;
            std::string _background;
            std::string _background2;
            std::string _title;
            std::shared_ptr<AGame> _game;
            Menu *_menu;
    };
}
