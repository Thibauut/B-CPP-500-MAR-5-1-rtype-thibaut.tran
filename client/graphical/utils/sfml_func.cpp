/*
** EPITECH PROJECT, 2023
** aa
** File description:
** sfml_func.cpp
*/

#include "sfml_func.hpp"

SfmlFunc::SfmlFunc() = default;

sf::Sprite SfmlFunc::CreateSprite(std::string path, float posX, float posY, float scaleX, float scaleY)
{
    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile(path);
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);
    return sprite;
}
