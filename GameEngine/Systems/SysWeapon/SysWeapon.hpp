/*
** EPITECH PROJECT, 2023
** SANJII & ZORO
** File description:
** SysWeapon.hpp
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Weapon/Weapon.hpp"
#include "../../Components/Sprite/Sprite.hpp"
#include "../../Components/TimeComp/TimeComp.hpp"
#include "../../Entity/EntityManager/EntityManager.hpp"
#include "../../Utils/Timeout.hpp"
#include <chrono>
#include <random>

namespace GameEngine {

    class SysWeapon : public ISystem {
        public:
            SysWeapon(std::shared_ptr<EntityManager> entityList) : _manager(entityList), isRunning(true) {}
            ~SysWeapon() {};

            virtual void update() override {
                for (std::shared_ptr<Entity> &entityPtr : _manager->getEntities()) {
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
            Entity createNewBullet(int posX, int posY, double couldown_value)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(3000, 10000);
                Entity newBullet(dis(gen), 4);
                int id_comp = 4452;
                Position position = Position(CONFIG::CompType::POSITION, id_comp, posX, posY);
                Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp + 1);
                TimeComp couldown = TimeComp(CONFIG::CompType::TIMECOMP, 1, couldown_value);

                sf::IntRect spriteRect(0, 0, 16, 12);
                sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/simpleBullet.png", sf::Vector2f(3, 3), spriteRect);
                std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
                std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
                std::shared_ptr<TimeComp> coulDownShared = std::make_shared<TimeComp>(couldown);
                newBullet.addComponent(positionShared);
                newBullet.addComponent(spriteShared);
                newBullet.addComponent(coulDownShared);
                return newBullet;
            }

            void Weapon1(std::shared_ptr<Entity> entity) {
                int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX();
                int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY();
                std::cout << "time pressed" << entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON)->getTimePressed()<< std::endl;
                if (entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON)->getIsShooting())
                    std::cout << "is shoot" << std::endl;
                else
                    std::cout << "no shoot" << std::endl;
                _manager->createEntity();
                _manager->addEntity(createNewBullet(x, y, 0.002));
            }

            void Weapon2(std::shared_ptr<Entity> entity) {

            }

            void Weapon3(std::shared_ptr<Entity> entity) {

            }



            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}