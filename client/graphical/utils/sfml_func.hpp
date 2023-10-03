/*
** EPITECH PROJECT, 2023
** aa
** File description:
** sfml_func.hpp
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

class SfmlFunc {
    public:
        SfmlFunc();
        void LoadSprite(sf::Sprite& sprite,  sf::Texture &texture, const std::string& imagePath, float posX, float posY, float scaleX, float scaleY);
        void CreateTextField(sf::RectangleShape& textField, sf::Text& text, const sf::Font& font, const std::string& labelText, const sf::Vector2f& size, const sf::Vector2f& position);
        void createText(sf::Text& text, const sf::Font& font, const std::string& content, unsigned int characterSize, const sf::Color& fillColor, const sf::Vector2f& position);
        void CreateButton(sf::RectangleShape& button, sf::Text& buttonText, const sf::Font& font, const std::string& label, const sf::Vector2f& size, const sf::Vector2f& position, int moveText);
        void HandleButtonHover(sf::RectangleShape& button, sf::Text& buttonText, bool& isButtonHovered, const sf::Vector2f& mousePos, const sf::FloatRect& buttonBounds);
        void HandleSpriteHover(sf::Sprite& sprite, bool& isSpriteHovered, const sf::Vector2f& mousePos, const sf::FloatRect& spriteBounds);
};
