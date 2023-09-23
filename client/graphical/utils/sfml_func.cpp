/*
** EPITECH PROJECT, 2023
** aa
** File description:
** sfml_func.cpp
*/

#include "sfml_func.hpp"

SfmlFunc::SfmlFunc() = default;

void SfmlFunc::LoadSprite(sf::Sprite& sprite,  sf::Texture &texture, const std::string& imagePath, float posX, float posY, float scaleX, float scaleY) {
    if (texture.loadFromFile(imagePath)) {
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(scaleX, scaleY);
    } else {
        std::cout << "Error: could not load image: " << imagePath << std::endl;
    }
}

void SfmlFunc::CreateTextField(sf::RectangleShape& textField, sf::Text& text, const sf::Font& font, const std::string& labelText, const sf::Vector2f& size, const sf::Vector2f& position) {
    textField.setSize(size);
    textField.setFillColor(sf::Color::Black);
    textField.setOutlineColor(sf::Color::White);
    textField.setOutlineThickness(5.0f);
    textField.setPosition(position);

    text.setFont(font);
    text.setString(labelText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(position - sf::Vector2f(0, 40));
}

void SfmlFunc::createText(sf::Text& text, const sf::Font& font, const std::string& content, unsigned int characterSize, const sf::Color& fillColor, const sf::Vector2f& position) {
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColor);
    text.setPosition(position);
}

void SfmlFunc::CreateButton(sf::RectangleShape& button, sf::Text& buttonText, const sf::Font& font, const std::string& label, const sf::Vector2f& size, const sf::Vector2f& position, int moveText) {
    button.setSize(size);
    button.setFillColor(sf::Color::Black);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(5.0f);
    button.setPosition(position);

    buttonText.setFont(font);
    buttonText.setString(label);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(position + sf::Vector2f(moveText, 10));
}

void SfmlFunc::HandleButtonHover(sf::RectangleShape& button, sf::Text& buttonText, bool& isButtonHovered, const sf::Vector2f& mousePos, const sf::FloatRect& buttonBounds) {
    if (buttonBounds.contains(mousePos)) {
        isButtonHovered = true;
        button.setScale(1.01f, 1.01f);
        buttonText.setScale(1.01f, 1.01f);
    } else {
        isButtonHovered = false;
        button.setScale(1.0f, 1.0f);
        buttonText.setScale(1.0f, 1.0f);
    }
}

void SfmlFunc::HandleSpriteHover(sf::Sprite& sprite, bool& isSpriteHovered, const sf::Vector2f& mousePos, const sf::FloatRect& spriteBounds) {
    if (spriteBounds.contains(mousePos)) {
        isSpriteHovered = true;
        sprite.setScale(0.51f, 0.51f);
    } else {
        isSpriteHovered = false;
        sprite.setScale(0.5f, 0.5f);
    }
}
