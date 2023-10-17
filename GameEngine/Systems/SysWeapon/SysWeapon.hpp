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
#include "../../Components/HitBoxCircle/HitBoxCircle.hpp"
#include "../../Components/HitBoxSquare/HitBoxSquare.hpp"
#include "../../Components/Damage/Damage.hpp"
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
                    if (WeaponComponent != nullptr && WeaponComponent->getIsShooting()) {
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
                    if (entityPtr != nullptr) {
                        if (entityPtr.get()->getType() == 4) {
                            clearBullet(entityPtr);
                            return;
                        }
                    }
                }
            };

        private:
            void clearBullet(std::shared_ptr<Entity> &entityPtr)
            {
                if (entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() < 0 ||
                    entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() < 0 ||
                    entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() > 1830 ||
                    entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() > 1090) {
                        _manager->deleteEntity(entityPtr->getId());
                    }

            }
            Entity createNewBullet(int posX, int posY, double couldown_value, int damage_value, std::string img_path, sf::IntRect spriteRect)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(3000, 10000);
                Entity newBullet(dis(gen), 4);
                int id_comp = 1;
                Position position = Position(CONFIG::CompType::POSITION, id_comp, posX, posY);
                Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp += 1);
                TimeComp couldown = TimeComp(CONFIG::CompType::TIMECOMP, id_comp += 1, couldown_value);
                HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp += 1, spriteRect);
                Damage damage = Damage(CONFIG::CompType::DAMAGE, id_comp += 1);
                sprite.setSprite(position.getPositionX(), position.getPositionY(), img_path, sf::Vector2f(3, 3), spriteRect);
                damage.setDamage(damage_value);
                std::shared_ptr<Damage> damageShared = std::make_shared<Damage>(damage);
                std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
                std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
                std::shared_ptr<TimeComp> coulDownShared = std::make_shared<TimeComp>(couldown);
                std::shared_ptr<HitBoxSquare> hitBoxShared = std::make_shared<HitBoxSquare>(hitbox);
                newBullet.addComponent(positionShared);
                newBullet.addComponent(hitBoxShared);
                newBullet.addComponent(spriteShared);
                newBullet.addComponent(coulDownShared);
                newBullet.addComponent(damageShared);
                return newBullet;
            }

            void Weapon1(std::shared_ptr<Entity> entity) {
                    int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() + (33.2 * 3);
                    int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() + (5 * 3);
                    sf::IntRect spriteRect(0, 0, 16, 12);
                    _manager->createEntity();
                    _manager->addEntity(createNewBullet(x, y, 0.001, 20 ,"assets/sprites/simpleBullet.png", spriteRect));
            }

            void Weapon2(std::shared_ptr<Entity> entity) {
                    int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() + (33.2 * 3);
                    int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() + (5 * 3);
                    sf::IntRect spriteRect(0, 0, 16, 12);
                    _manager->createEntity();
                    _manager->addEntity(createNewBullet(x, y, 0.0017, 15, "assets/sprites/simpleBullet.png", spriteRect));
                    _manager->addEntity(createNewBullet(x + 20 * 3 , y, 0.0017, 15,"assets/sprites/simpleBullet.png", spriteRect));
            }

            void Weapon3(std::shared_ptr<Entity> entity) {
                    int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() + (33.2 * 3);
                    int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() + (5 * 3);
                    sf::IntRect spriteRect(0, 0, 7, 6);
                    _manager->createEntity();
                    _manager->addEntity(createNewBullet(x, y, 0.0005, 4, "assets/sprites/smallBullet.png", spriteRect));
            }



            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}