/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Editor.hpp
*/

#pragma once
#include "../../GameEngine/GameEngine.hpp"
#include "../../GameEngine/Systems/SysRender/SysRenderGlobal.hpp"
// #include "../../GameEngine/Systems/SysDrag/SysDrag.hpp"
#include "../../GameEngine/Systems/SysPollEvent/SysPollEvent.hpp"
#include "../../GameEngine/Systems/SysCamera/SysCameraEditor.hpp"
#include "../../GameEngine/Components/String/String.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

class Editor {
    public:
        Editor(sf::RenderWindow *window);
        ~Editor();

        void loadPalette();
        void loadSprites();
        void loadSystems();
        void loadGUI();
        void loadButtonGUI();

    private:
        Engine _core;
};