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
#include "../../../GameEngine/Components/Weapon/Weapon.hpp"
#include "../../../GameEngine/Components/HitBoxSquare/HitBoxSquare.hpp"
#include "../../../GameEngine/Components/Damage/Damage.hpp"
#include "../../../GameEngine/Components/Direction/Direction.hpp"
#include "../../../GameEngine/Components/Team/Team.hpp"
#include "../../../GameEngine/Components/Cooldown/Cooldown.hpp"
#include "../../../GameEngine/Components/Sound/Sound.hpp"
#include "../../../GameEngine/Components/Camera/Camera.hpp"
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
            void loadMob(std::shared_ptr<Camera> camera, nlohmann::json &entity);
            std::string _path;
    };
}