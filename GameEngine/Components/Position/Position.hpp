
/*
** EPITECH PROJECT, 2023
** Position
** File description:
** Position
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {
    class Position : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Position() : AComponent(CONFIG::CompType::POSITION) {}
            Position(CONFIG::CompType type, int id, int x, int y) : AComponent(CONFIG::CompType::POSITION), _idComponent(id), _type(type), _xPos(x), _yPos(y) {}
            virtual ~Position() = default;

            void setPosition(int xPos, int yPos) {
                _xPos = xPos;
                _yPos = yPos;
            }

            void setPositionX(int xPos) {
                _xPos = xPos;
            }

            void setPositionY(int yPos) {
                _yPos = yPos;
            }

            std::pair<int, int> getPosition() const {
                return std::make_pair(_xPos, _yPos);
            }

            int getPositionX() {
                return _xPos;
            }

            int getPositionY() {
                return _yPos;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Position>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                ar & _type;
                ar & _xPos;
                ar & _yPos;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _xPos;
            int _yPos;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Position);