/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** SysCameraEditor.hpp
*/

#pragma once

#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Camera/Camera.hpp"
#include "../../Components/HitBoxSquare/HitBoxSquare.hpp"
#include "../../Components/Sprite/Sprite.hpp"

namespace GameEngine {

    class SysCameraEditor : public ISystem {
        public:
        SysCameraEditor(std::shared_ptr<EntityManager> entityList) : _manager(entityList), isRunning(true) {}
        ~SysCameraEditor() {};

        virtual void update() override {
            std::shared_ptr<Entity> cams = _manager->getEntityById(550);
            if (cams == nullptr)
                return;
            std::shared_ptr<Camera> cam = cams->getComponentByType<Camera>(CONFIG::CompType::CAMERA);
            std::shared_ptr<Position> posCam = cams->getComponentByType<Position>(CONFIG::CompType::POSITION);
            std::shared_ptr<HitBoxSquare> hitbox = cams->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
            if (cam == nullptr || posCam == nullptr || hitbox == nullptr)
                return;

            for (Entity entity : cam->getEntities()) {
                std::shared_ptr<Position> pos = entity.getComponentByType<Position>(CONFIG::CompType::POSITION);
                int x = pos->getPositionX();
                if (x > posCam->getPositionX() && x < (posCam->getPositionX() + hitbox->getWidth()) ) {
                    std::shared_ptr<Sprite> sprite = entity.getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
                    if (isInCurrentList(entity)) {
                        sprite->setPositionSprite(sf::Vector2f((x - posCam->getPositionX()), pos->getPositionY()));
                        continue;
                    }
                    sprite->setPositionSprite(sf::Vector2f((x - posCam->getPositionX()), pos->getPositionY()));
                    _manager->addEntity(entity);
                    _currents.push_back(entity);
                    return;
                } else {
                    if (!isInCurrentList(entity))
                        continue;
                    _manager->deleteEntity(entity.getUuid());
                    deleteEntity(entity.getUuid());
                    return;
                }
            }
        };

        void deleteEntity(const std::string uuid) {
            int count = 0;
            for (Entity entity : _currents) {
                if (entity.getUuid() == uuid) {
                    _currents.erase(_currents.begin() + count);
                    return;
                }
                count++;
            }
        }

        bool isInCurrentList(Entity entitity) {
            for (Entity entity : _currents) {
                if (entity.getUuid() == entitity.getUuid())
                    return true;
            }
            return false;
        }

        private:
            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
            std::vector<Entity> _currents;
    };
}