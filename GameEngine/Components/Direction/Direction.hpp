/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Direction.hpp
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {
    class Direction : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Direction() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::DIRECTION;
                _directionX = 1;
                _directionY = 1;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Direction(CONFIG::CompType type, int id) : AComponent(CONFIG::CompType::DIRECTION), _idComponent(id), _type(type), _directionX(1), _directionY(1),_orientation(90) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Direction(CONFIG::CompType type, int id, int directionX, int directionY, double orientation) : AComponent(CONFIG::CompType::DIRECTION), _idComponent(id), _type(type), _directionX(directionX), _directionY(directionY), _orientation(orientation) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            ~Direction() = default;

            void setOrientation(double orientation) {
                _orientation = orientation;
            }

            double getOriantation() const {
                return _orientation;
            }
            void setDirectionX(int direction) {
                _directionX = direction;
            }

            int getDirectionX() const {
                return _directionX;
            }

            void setDirectionY(int direction) {
                _directionY = direction;
            }

            int getDirectionY() const {
                return _directionY;
            }

            void reverse_orientation() {
                for (int i = 0; i != 180; i++, _orientation ++) {
                    if (_orientation > 360)
                        _orientation = 1;
                }
            }
            void reverse_directionX() {
                if (_directionX == 1)
                    _directionX = -1;
                else
                    _directionX = 1;
            }

            void reverse_directionY() {
                if (_directionY == 1)
                    _directionY = -1;
                else
                    _directionY = 1;
            }

            double calculateAngle(double x, double y, double xCible, double yCible) {
                double deltaX = xCible - x;
                double deltaY = yCible - y;
                double angle_radians = std::atan2(deltaY, deltaX);
                double angle_degrees = angle_radians * (180.0 / M_PI);
                if (angle_degrees < 0.0) {
                    angle_degrees += 360.0;
                }
                return angle_degrees;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Direction>();
                ar & boost::serialization::base_object<AComponent>(*this);
                // ar & _uuid;
                ar & _idComponent;
                ar & _type;
                ar & _directionX;
                ar & _directionY;
                ar &_orientation;
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
            int _directionX;
            int _directionY;
            double _orientation;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Direction);
