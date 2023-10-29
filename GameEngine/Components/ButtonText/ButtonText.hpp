/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ButtonText.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {

    class ButtonText : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            ButtonText() : AComponent(CONFIG::CompType::BUTTON) {
                _idComponent = 0;
                _type = CONFIG::CompType::BUTTON;

                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());

            }
            ButtonText(CONFIG::CompType type, int id, int sizeX, int sizeY, std::string label, bool isActivate, bool isPressed) : AComponent(CONFIG::CompType::BUTTON), _idComponent(id), _type(type), _sizeX(sizeX), _sizeY(sizeY), _label(label), _isActivate(isActivate), _isPressed(isPressed) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            virtual ~ButtonText() = default;


            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Position>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                // ar & _uuid;
                ar & _type;
                ar & _sizeX;
                ar & _sizeY;
                ar & _label;
                ar & _isActivate;
                ar & _isPressed;
            }

            void setSize(int x, int y) {
                _sizeX = x;
                _sizeY = y;
            }

            int getSizeX() {
                return _sizeX;
            }

            int getSizeY() {
                return _sizeY;
            }

            void startPress() {
                _isPressed = true;
            }

            void stopPress() {
                _isPressed = false;
            }

            bool isPressed() const {
                return _isPressed;
            }

            void activateButton() {
                _isActivate = true;
            }

            void desactivateButton() {
                _isActivate = false;
            }

            bool isActivate() const {
                return _isActivate;
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
            int _sizeX;
            int _sizeY;
            std::string _label;
            bool _isPressed;
            bool _isActivate;
         

    };
}