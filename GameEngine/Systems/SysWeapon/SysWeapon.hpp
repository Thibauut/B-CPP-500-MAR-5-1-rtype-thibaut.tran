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
            Entity createNewBullet(int posX, int posY)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(3000, 10000);
                std::cout << "num:: " << dis(gen) << std::endl;
                Entity newBullet(dis(gen), 4);
                int id_comp = 4452;
                Position position = Position(CONFIG::CompType::POSITION, id_comp, posX, posY);
                Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp + 1);
                sf::IntRect spriteRect(0, 0, 16, 12);
                sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/simpleBullet.png", sf::Vector2f(3, 3), spriteRect);
                std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
                std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
                newBullet.addComponent(positionShared);
                newBullet.addComponent(spriteShared);
                return newBullet;
            }

            void Weapon1(std::shared_ptr<Entity> entity) {
                std::cout << "func weapon 1"<< std::endl;
                int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX();
                int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY();
                std::cout << "position entitée recuperée" << std::endl;
                _manager->createEntity();
                _manager->addEntity(createNewBullet(x, y));
                std::cout << "nouvelle bullet ajouter aux Entity" << std::endl;
                std::cout << "fin weapon 1"<< std::endl;
            }

            void Weapon2(std::shared_ptr<Entity> entity) {

            }

            void Weapon3(std::shared_ptr<Entity> entity) {

            }



            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}