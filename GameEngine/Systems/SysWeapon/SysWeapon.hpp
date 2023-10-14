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
#include "../../Utils/Timeout.hpp"
#include <chrono>
#include <random>

namespace GameEngine {

    class SysWeapon : public ISystem {
        SysWeapon(std::list<std::shared_ptr<Entity>> &entityList) : _entities(entityList), isRunning(true) {}
        ~SysWeapon() {};

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
            std::shared_ptr<Entity> createNewBullet(int posX, int posY)
            {
                std::cout << "func createNewBullet" << std::endl;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(3000, 10000);
                Entity newBullet(dis(gen), 4);
                std::cout << "entity bullet créer" << std::endl;
                int id_comp = 0;
                Position position = Position(CONFIG::CompType::POSITION, id_comp, posX, posY);
                std::cout << "comp position creer" << std::endl;
                Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp + 1);
                std::cout << "comp sprite creer" << std::endl;
                sf::IntRect spriteRect(0, std::round(0), std::round(16), std::round(12));
                std::cout << "rectangle sprite creer" << std::endl;
                sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/simpleBullet.png", sf::Vector2f(3, 3), spriteRect);
                std::cout << "sprite creer" << std::endl;
                std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
                std::cout << "ptr position creer" << std::endl;
                std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
                std::cout << "ptr sprite creer" << std::endl;
                std::shared_ptr<Entity> newBulletPtr;
                std::cout << "ptr entity bullet creer" << std::endl;
                newBullet.addComponent(positionShared);
                newBullet.addComponent(spriteShared);
                newBulletPtr = std::make_shared<Entity>(newBullet);
                std::cout << "make shared de entity bullet effectuée" << std::endl;
                return newBulletPtr;
            }

            void Weapon1(std::shared_ptr<Entity> entity) {
                std::cout << "func weapon 1"<< std::endl;
                int x = entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX();
                int y = entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY();
                std::cout << "position entitée recuperée" << std::endl;
               _entities.push_back(createNewBullet(x, y));
               std::cout << "nouvelle bullet ajouter aux Entity" << std::endl;
               std::cout << "fin weapon 1"<< std::endl;
            }

            void Weapon2(std::shared_ptr<Entity> entity) {

            }

            void Weapon3(std::shared_ptr<Entity> entity) {

            }



            bool isRunning;
            std::list<std::shared_ptr<Entity>> _entities;
    };
}