/*
** EPITECH PROJECT, 2023
** Health
** File description:
** Health
*/

#pragma once

#include "../AComponent/AComponent.hpp"
#include "../Position/Position.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Window/Window.hpp"
#include "SFML/Graphics.hpp"

namespace GameEngine {
    class RectangleShape : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            RectangleShape() : AComponent() {
                _idComponent = 752;
                _type = CONFIG::CompType::RECTANGLESHAPE;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }

            RectangleShape(sf::RectangleShape rect) : AComponent() {
                _idComponent = 752;
                _type = CONFIG::CompType::RECTANGLESHAPE;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
                rectangle = rect;
            }

            ~RectangleShape() = default;

            void setRectangleShape(std::shared_ptr<Entity> &entity, int x) {
                std::shared_ptr<Sprite> sprite = entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
                std::shared_ptr<Position> position = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                sf::FloatRect rect = sprite->getSprite().getGlobalBounds();
                sf::RectangleShape rectangle2(sf::Vector2f(rect.width, rect.height));
                rectangle2.setFillColor(sf::Color::Transparent);
                rectangle2.setOutlineThickness(5);
                rectangle2.setOutlineColor(sf::Color::White);
                rectangle2.setPosition(x, position->getPositionY());
                rectangle = rectangle2;
            }

            sf::RectangleShape &getRectangleShape() {
                return rectangle;
            }

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<RectangleShape>();
                ar & boost::serialization::base_object<AComponent>(*this);
                // ar & _uuid;
                ar & _idComponent;
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
            sf::RectangleShape rectangle;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::RectangleShape);
