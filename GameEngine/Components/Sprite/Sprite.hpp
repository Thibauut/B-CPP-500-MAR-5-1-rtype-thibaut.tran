/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Render.hpp
*/

#pragma once
#include "../AComponent/AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace GameEngine {

    class Sprite : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Sprite() : AComponent() {};
            Sprite(CONFIG::CompType type, int id)
            : AComponent(), _idComponent(id), _type(type) {}

            ~Sprite() = default;

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Sprite>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                ar & _type;
                ar & _x;
                ar & _y;
                ar & _leftRect;
                ar & _topRect;
                ar & width;
                ar & height;
                ar & _scaleX;
                ar & _scaleY;
                ar & _path;
            }

            void setSprite(int width, int height, const std::string &path, sf::Vector2f scale, sf::IntRect &rect) {
                _x = width;
                _y = height;
                _scaleX = scale.x;
                _scaleY = scale.y;
                _path = path;
                setIntRect(rect);
                // _spriteTexture.loadFromFile(path);
                // _sprite.setTexture(_spriteTexture);
                // _sprite.setTextureRect(rect);
                // _sprite.setScale(sf::Vector2f(_scaleX, _scaleY));
                // _sprite.setPosition(sf::Vector2f(_x, _y));
            }

            void initSprite() {
                _spriteTexture.loadFromFile(_path);
                _sprite.setTexture(_spriteTexture);
                initRect();
                _sprite.setScale(sf::Vector2f(_scaleX, _scaleY));
                _sprite.setPosition(sf::Vector2f(_x, _y));
            }

            void setIntRect(sf::IntRect& rect) {
                _leftRect = rect.left;
                _topRect = rect.top;
                width = rect.width;
                height = rect.height;
            }

            void initRect() {
                sf::IntRect rect = sf::IntRect(_leftRect, _topRect, width, height);
                _rect = rect;
                _sprite.setTextureRect(_rect);
            }

            int getSpriteX() {
                return _x;
            }

            int getSpriteY() {
                return _y;
            }

            sf::Sprite getSprite() {
                return _sprite;
            }

            void setPositionSprite(const sf::Vector2f &pos) {
                _sprite.setPosition(pos);
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) { _idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _x;
            int _y;
            int _leftRect;
            int _topRect;
            int width;
            int height;
            int _scaleX;
            int _scaleY;
            std::string  _path;
            sf::Sprite _sprite;
            sf::Texture _spriteTexture;
            sf::IntRect _rect;
            sf::Clock _clock;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Sprite);
