/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** SysMap.hpp
*/

#pragma once

#include "../../../GameEngine/Entity/EntityManager/EntityManager.hpp"
#include "../ASystem/ASystem.hpp"
#include "../../../GameEngine/Components/Health/Health.hpp"
#include "../../../GameEngine/Components/Position/Position.hpp"
#include "../../../GameEngine/Components/AI/AI.hpp"
#include "../../../GameEngine/Components/Sprite/Sprite.hpp"
#include "../../../GameEngine/Components/Weapon/Weapon.hpp"
#include "../../../GameEngine/Components/HitBoxSquare/HitBoxSquare.hpp"
#include "../../../GameEngine/Components/Damage/Damage.hpp"
#include "../../../GameEngine/Components/Direction/Direction.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace RType {
    class SysMap: public ISystem {
        public:
            SysMap(const std::string &path);
            ~SysMap();

            void loadMap(std::shared_ptr<EntityManager> manager);

        private:
            void loadMob(std::shared_ptr<EntityManager> manager, nlohmann::json &entity);
            std::string _path;
    };
}