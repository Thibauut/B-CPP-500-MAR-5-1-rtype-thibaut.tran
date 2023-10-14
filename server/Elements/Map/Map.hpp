/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Map.hpp
*/

#pragma once
#include "../../../GameEngine/Entity/EntityManager/EntityManager.hpp"
#include "../../../GameEngine/Components/Health/Health.hpp"
#include "../../../GameEngine/Components/Position/Position.hpp"
#include "../../../GameEngine/Components/AI/AI.hpp"
#include "../../../GameEngine/Components/Sprite/Sprite.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace RType {
    class Map {
        public:
            Map(const std::string &path);
            ~Map();

            void loadMap(std::shared_ptr<EntityManager> manager);

        private:
            void loadMob(std::shared_ptr<EntityManager> manager, nlohmann::json &entity);
            std::string _path;
    };
}