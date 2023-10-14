/*
** EPITECH PROJECT, 2023
** SANJII & ZORO
** File description:
** SysShoot.hpp
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Weapon/Weapon.hpp"
#include "../../Components/Sprite/Sprite.hpp"
#include "../../Utils/Timeout.hpp"
#include <chrono>
#include <random>

namespace GameEngine {

    class SysShoot : public ISystem {
        SysShoot(std::list<std::shared_ptr<Entity>> &entityList) : _entities(entityList), isRunning(true) {}
        ~SysShoot() {};

        virtual void update() override {
                for (std::shared_ptr<Entity> &entityPtr : _entities) {
                std::shared_ptr<Weapon> WeaponComponent = entityPtr->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                if (WeaponComponent != nullptr) {
                    if (WeaponComponent.get()->getWeaponType() == CONFIG::WeaponType::Weapon1 && WeaponComponent.get()->canShoot()) {
                        Weapon1(entityPtr);
                    }

                    if (WeaponComponent.get()->getWeaponType() == CONFIG::WeaponType::Weapon2 && WeaponComponent.get()->canShoot()) {
                        Weapon2(entityPtr);
                    }

                    if (WeaponComponent.get()->getWeaponType() == CONFIG::WeaponType::Weapon3 && WeaponComponent.get()->canShoot()) {
                        Weapon3(entityPtr);
                    }
                }
            }
        };



        private:

            bool isRunning;
            std::list<std::shared_ptr<Entity>> _entities;
    };
}