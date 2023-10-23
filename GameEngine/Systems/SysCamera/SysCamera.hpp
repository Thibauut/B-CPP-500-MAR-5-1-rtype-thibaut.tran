/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** SysCamera.hpp
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Camera/Camera.hpp"
#include "../../Components/Cooldown/Cooldown.hpp"

namespace GameEngine {

    class SysCamera : public ISystem {
        public:
        SysCamera(std::shared_ptr<EntityManager> entityList) : _manager(entityList), isRunning(true) {}
        ~SysCamera() {};

        virtual void update() override {
            // std::cout << "0.0" << std::endl;
            std::shared_ptr<Entity> cams = _manager->getEntityByType(5);
            // std::cout << "0.1" << std::endl;
            if (cams == nullptr)
                return;
            std::shared_ptr<Camera> cam = cams->getComponentByType<Camera>(CONFIG::CompType::CAMERA);
            // std::cout << "0.2" << std::endl;
            std::shared_ptr<Position> posCam = cams->getComponentByType<Position>(CONFIG::CompType::POSITION);
            // std::cout << "0.3" << std::endl;
            std::shared_ptr<Cooldown> cooldown = cams->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
            // std::cout << "0.4" << std::endl;
            if (cam == nullptr || posCam == nullptr || cooldown == nullptr)
                return;

            // std::cout << "1" << std::endl;

            cooldown->create(0.1, "camera");
            // std::cout << "2" << std::endl;

            if (cooldown->isFinish("camera")) {
                posCam->setPositionX(posCam->getPositionX() + 1);
                cooldown->reset("camera");
            }
            // std::cout << "3" << std::endl;

            for (Entity entity : cam->getEntities()) {
                int x = entity.getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX();
                // std::cout << "PosCam: " << posCam->getPositionX() << " x: " << x << std::endl;
                if (posCam->getPositionX() >= x) {
                    // std::cout << "4" << std::endl;
                    // _manager->lock();
                    _manager->createEntity();
                    _manager->addEntity(entity);
                    // _manager->unlock();
                    // std::cout << "5" << std::endl;
                    cam->pop();
                    // std::cout << "6" << std::endl;
                    return;
                } else { return; }
            }
        };

        private:
            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}