/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Editor.hpp
*/

#pragma once
#include "../../GameEngine/GameEngine.hpp"
#include "../../GameEngine/Systems/SysRender/SysRenderGlobal.hpp"

class Editor {
    public:
        Editor(sf::RenderWindow *window);
        ~Editor();

        void loadSprites();
        void loadSystems();

    private:
        Engine _core;
};