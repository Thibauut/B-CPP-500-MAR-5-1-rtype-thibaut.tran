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
#include "../../Components/Cooldown/Cooldown.hpp"
#include "../../Components/HitBoxCircle/HitBoxCircle.hpp"
#include "../../Components/HitBoxSquare/HitBoxSquare.hpp"
#include "../../Components/Damage/Damage.hpp"
#include "../../Components/Direction/Direction.hpp"
#include "../../Components/Team/Team.hpp"
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
                        }
                    }
                }
            };

        private:
            void clearBullet(std::shared_ptr<Entity> &entityPtr)
            {
                if (entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() < 0 ||
                    entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() < 0 ||
                    entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() > 1930 ||
                    entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() > 1090) {
                        entityPtr->setIsDeath(true);
                }
            }
            Entity createNewBullet(int posX, int posY, double couldown_value, int damage_value, int direction_value, double oriantation, std::string img_path, sf::IntRect spriteRect, int team_value)
            {
                Entity newBullet(4);
                newBullet.init();
                int id_comp = 1;
                Position position = Position(CONFIG::CompType::POSITION, id_comp, posX, posY);
                Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp += 1);
                Cooldown couldown = Cooldown(CONFIG::CompType::TIMECOMP, id_comp += 1);
                Cooldown couldownDelete = Cooldown(CONFIG::CompType::TIMECOMP, id_comp += 1);
                HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp += 1, spriteRect);
                Damage damage = Damage(CONFIG::CompType::DAMAGE, id_comp += 1);
                Direction direction = Direction(CONFIG::CompType::DIRECTION, id_comp += 1);
                Team team = Team(CONFIG::CompType::TEAM, id_comp += 1, team_value);
                sprite.setSprite(position.getPositionX(), position.getPositionY(), img_path, sf::Vector2f(3, 3), spriteRect, CONFIG::SpriteType::BULLETSPRITE);
                damage.setDamage(damage_value);
                direction.setDirection(direction_value);
                direction.setOrientation(oriantation);
                couldown.create(couldown_value, "bullet");
                std::shared_ptr<Damage> damageShared = std::make_shared<Damage>(damage);
                std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
                std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
                std::shared_ptr<Cooldown> coulDownShared = std::make_shared<Cooldown>(couldown);
                std::shared_ptr<HitBoxSquare> hitBoxShared = std::make_shared<HitBoxSquare>(hitbox);
                std::shared_ptr<Direction> directionShared = std::make_shared<Direction>(direction);
                std::shared_ptr<Team>teamShared = std::make_shared<Team>(team);
                newBullet.addComponent(positionShared);
                newBullet.addComponent(hitBoxShared);
                newBullet.addComponent(spriteShared);
                newBullet.addComponent(coulDownShared);
                newBullet.addComponent(damageShared);
                newBullet.addComponent(directionShared);
                newBullet.addComponent(teamShared);
                return newBullet;
            }

            void Weapon1(std::shared_ptr<Entity> entity) {
                    auto dir = entity->getComponentByType<Direction>(CONFIG::CompType::DIRECTION);
                    int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() + (((33.2 * 3) * dir->getDirection()));
                    int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() + (5 * 3);
                    int team = entity->getComponentByType<Team>(CONFIG::CompType::TEAM)->getTeam();
                    sf::IntRect spriteRect(0, 0, 16, 12);
                    _manager->createEntity();
                    _manager->addEntity(createNewBullet(x, y, 0.0004, 20 , dir->getDirection(), dir->getOriantation(),"assets/sprites/simpleBullet.png", spriteRect, team));
            }

            void Weapon2(std::shared_ptr<Entity> entity) {
                    auto dir = entity->getComponentByType<Direction>(CONFIG::CompType::DIRECTION);
                    int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() + ((33.2 * 3) * dir->getDirection());
                    int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() + (5 * 3);
                    int team = entity->getComponentByType<Team>(CONFIG::CompType::TEAM)->getTeam();
                    sf::IntRect spriteRect(0, 0, 16, 12);
                    _manager->createEntity();
                    _manager->addEntity(createNewBullet(x, y, 0.0007, 15, dir->getDirection(), dir->getOriantation(), "assets/sprites/simpleBullet.png", spriteRect, team));
                    _manager->addEntity(createNewBullet(x + 20 * 3 , y, 0.0007, 15, dir->getDirection(), dir->getOriantation(), "assets/sprites/simpleBullet.png", spriteRect, team));
            }

            void Weapon3(std::shared_ptr<Entity> entity) {
                    auto dir = entity->getComponentByType<Direction>(CONFIG::CompType::DIRECTION);
                    int x = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX() + ((33.2 * 3) * dir->getDirection());
                    int y = entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY() + (5 * 3);
                    int team = entity->getComponentByType<Team>(CONFIG::CompType::TEAM)->getTeam();
                    sf::IntRect spriteRect(0, 0, 7, 6);
                    _manager->createEntity();
                    _manager->addEntity(createNewBullet(x, y, 0.0005, 8, dir->getDirection(), dir->getOriantation(), "assets/sprites/smallBullet.png", spriteRect, team));
            }



            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}